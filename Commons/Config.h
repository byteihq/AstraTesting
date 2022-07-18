#ifndef ASTRATESTING_CONFIG_H
#define ASTRATESTING_CONFIG_H

#include <nlohmann/json.hpp>
#include <string>

class Config {
private:
    struct Presets {
        std::string OutputPath = "/home/u/output/";
        bool RewriteExistFiles = true;
        bool LogToConsole = true;
        bool LogToFile = true;
        bool RequiresRoot = true;

        Presets() = default;

        explicit Presets(const std::string &OP, bool RF, bool LTC, bool LTF, bool RR) : OutputPath(OP),
                                                                                        RewriteExistFiles(RF),
                                                                                        LogToConsole(LTC),
                                                                                        LogToFile(LTF),
                                                                                        RequiresRoot(RR) {}
    };

    Presets presets;
    nlohmann::json config;

    Config() = default;

private:
    void UnParsePresets();

public:
    Config(const Config &) = delete;

    Config &operator=(const Config &) = delete;

    int Init();

    const nlohmann::json &GetConfig() const;

    const Presets &GetPresets() const;

    static Config *GetInstance();
};


#endif //ASTRATESTING_CONFIG_H
