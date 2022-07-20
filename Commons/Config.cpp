// Copyright 2022 byteihq

#include "Config.h"
#include "Logger.h"
#include <sstream>
#include <fstream>

Config *Config::GetInstance() {
    static Config config;
    return &config;
}

int Config::Init() {
    int iErrorLevel = 0;
    std::ifstream cfg("./config.json");
    if (!cfg.is_open()) {
        ++iErrorLevel;
    }

    if (!iErrorLevel) {
        std::stringstream scfg;
        scfg << cfg.rdbuf();
        try {
            config = nlohmann::json::parse(scfg.str());
        } catch (const nlohmann::json::exception& ex) {
            Logger::GetInstance()->Log(ex.what());
            ++iErrorLevel;
        }
    }

    if (!iErrorLevel) {
        UnParsePresets();
    }
    return iErrorLevel;
}

const nlohmann::json &Config::GetConfig() const {
    return config;
}

const Config::Presets &Config::GetPresets() const {
    return presets;
}

void Config::UnParsePresets() {
    std::stringstream ss;
    try {
        Presets NewPresets {
          config.at("Presets").at("OutputPath").get<std::string>(),
          config.at("Presets").at("RewriteExistFiles").get<bool>(),
          config.at("Presets").at("LogToConsole").get<bool>(),
          config.at("Presets").at("LogToFile").get<bool>(),
          config.at("Presets").at("RequiresRoot").get<bool>(),
        };

        presets = NewPresets;
    } catch (const std::exception &e) {
        Logger::GetInstance()->Log(std::string("Failed to unparse presets settings, error:\n") + std::string(e.what()), true);
    }
    ss << "Presets ready:"
       << "\n\tOutputPath: " << presets.OutputPath
       << "\n\tRewriteExistFiles: " << std::boolalpha << presets.RewriteExistFiles
       << "\n\tLogToConsole: " << std::boolalpha << presets.LogToConsole
       << "\n\tLogToFile: " << std::boolalpha << presets.LogToFile
       << "\n\tRequiresRoot: " << std::boolalpha << presets.RequiresRoot;
    Logger::GetInstance()->Log(ss.str(), true);
}
