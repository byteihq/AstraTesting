// Copyright 2022 byteihq

#include "BaseTest.h"
#include "Config.h"
#include "Logger.h"
#include "Terminal.h"
#include <sstream>

void BaseTest::Init(const std::string &TestName, const nlohmann::json &config) {
    std::stringstream ss;
    try {
        Params NewParams{
                TestName,
                config.at("InstallEnabled").get<bool>(),
                config.at("InstallExecute").get<std::string>(),
                config.at("InstallOut").get<std::string>(),
                config.at("TestEnabled").get<bool>(),
                config.at("TestExecute").get<std::string>(),
                config.at("TestOut").get<std::string>(),
                config.at("RemoveAfterEnabled").get<bool>(),
                config.at("RemoveAfterExecute").get<std::string>()
        };

        currentParams = NewParams;
    } catch (const nlohmann::json::exception &ex) {
        Logger::GetInstance()->Log(std::string("Failed to unparse presets settings, error:\n") + std::string(ex.what()),
                                   true);
    }
    ss << TestName << " ready:"
       << "\n\tInstallEnabled: " << std::boolalpha << currentParams.InstallEnabled
       << "\n\tInstallExecute: " << currentParams.InstallExecute
       << "\n\tInstallOut: " << currentParams.InstallOut
       << "\n\tTestEnabled: " << std::boolalpha << currentParams.TestEnabled
       << "\n\tTestExecute: " << currentParams.TestExecute
       << "\n\tTestOut: " << currentParams.TestOut
       << "\n\tRemoveAfterEnabled: " << std::boolalpha << currentParams.RemoveAfterEnabled
       << "\n\tRemoveAfterExecute: " << currentParams.RemoveAfterExecute;
    Logger::GetInstance()->Log(ss.str(), true);
}

void BaseTest::Run() const {
    if (currentParams.InstallEnabled) {
        Test(currentParams.TestName, currentParams.InstallExecute, currentParams.InstallOut);
    }
    if (currentParams.TestEnabled) {
        Test(currentParams.TestName, currentParams.TestExecute, currentParams.TestOut);
    }
    if (currentParams.RemoveAfterEnabled) {
        Test(currentParams.TestName, currentParams.RemoveAfterExecute);
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
    Logger::GetInstance()->Log(TestName + "_OUTPUT:\n" + res.second);

    if (FileName.empty()) {
        return;
    }
    Logger::GetInstance()->WriteOutput(Config::GetInstance()->GetPresets().OutputPath + "/" + FileName, res.second,
                                       Config::GetInstance()->GetPresets().RewriteExistFiles);
    Logger::GetInstance()->Log(TestName + "_FILE: " + Config::GetInstance()->GetPresets().OutputPath + "/" + FileName);
}
