// Copyright 2022 byteihq

#include "BaseTest.h"
#include "Config.h"
#include "Logger.h"
#include "Terminal.h"
#include <sstream>

BaseTest::BaseTest(const std::string &TestName, const nlohmann::json &config) {
    std::stringstream ss;
    try {
        Params NewParams{
                TestName,
                config.at("Install").get<bool>(),
                config.at("InstallExecute").get<std::string>(),
                config.at("InstallOut").get<std::string>(),
                config.at("Test").get<bool>(),
                config.at("TestExecute").get<std::string>(),
                config.at("TestOut").get<std::string>()
        };

        currentParams = NewParams;
    } catch (const nlohmann::json::exception& ex) {
        Logger::GetInstance()->Log(std::string("Failed to unparse presets settings, error:\n") + std::string(ex.what()), true);
    }
    ss << TestName << " ready:"
       << "\nInstall: " << std::boolalpha << currentParams.Install
       << "\nInstallExecute: " << currentParams.InstallExecute
       << "\nInstallOut: " << currentParams.InstallOut
       << "\nTest: " << std::boolalpha << currentParams.Test
       << "\nTestExecute: " << currentParams.TestExecute
       << "\nTestOut: " << currentParams.TestOut;
    Logger::GetInstance()->Log(ss.str(), true);
}

void BaseTest::Run() const {
    if (currentParams.Install) {
        Test(currentParams.TestName, currentParams.InstallExecute, currentParams.InstallOut);
    }
    if (currentParams.Test) {
        Test(currentParams.TestName, currentParams.TestExecute, currentParams.TestOut);
    }
}

void BaseTest::Test(const std::string &TestName, const std::string &ExecCommand,
                    const std::string &FileName) {
    Logger::GetInstance()->Log(TestName);
    Logger::GetInstance()->Log(TestName + "_COMMAND: " + ExecCommand);
    auto res = Terminal::Exec(ExecCommand);
    if (!res.first) {
        Logger::GetInstance()->Log(TestName + " Failed");
    }
    if (FileName.empty()) {
        return;
    }
    Logger::GetInstance()->Log(TestName + "_OUTPUT:\n" + res.second);
    Logger::GetInstance()->WriteOutput(Config::GetInstance()->GetPresets().OutputPath + "/" + FileName, res.second, Config::GetInstance()->GetPresets().RewriteExistFiles);
    Logger::GetInstance()->Log(TestName + "_FILE: " + Config::GetInstance()->GetPresets().OutputPath + "/" + FileName);
}
