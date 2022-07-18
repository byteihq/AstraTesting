// Copyright 2022 byteihq

#include "Logger.h"
#include "Config.h"
#include "BaseTest.h"
#include <unistd.h>
#include <vector>
#include <iostream>

int main(int argc, char *argv[]) {
    if (Config::GetInstance()->Init()) {
        return -1;
    }

    if (Config::GetInstance()->GetPresets().RequiresRoot && getuid()) {
        Logger::GetInstance()->Log("You should run this program as root", true);
        return -1;
    }

    std::vector<BaseTest> BaseTests;
    auto &Tests = Config::GetInstance()->GetConfig()["Tests"];
    for (auto test = Tests.begin(); test != Tests.end(); ++test) {
        BaseTests.emplace_back(test.key(), *test);
    }

    Logger::GetInstance()->Log("Do you want to continue with these params? [y/n]", true);
    char ans;
    std::cin >> ans;
    if (!(ans == 'y' || ans == 'Y')) {
        return 0;
    }

    Logger::GetInstance()->SetLogToConsole(Config::GetInstance()->GetPresets().LogToConsole);
    Logger::GetInstance()->SetLogToFile(Config::GetInstance()->GetPresets().LogToFile);
    if (Config::GetInstance()->GetPresets().RewriteExistFiles) {
        Logger::GetInstance()->ClearLog();
    }

    for (const auto& test : BaseTests) {
        test.Run();
    }
    return 0;
}
