// Copyright 2022 byteihq

#ifndef ASTRATESTING_LOGGER_H
#define ASTRATESTING_LOGGER_H

#include <string>
#include <fstream>

class Config;

class Logger {
private:
    friend class Config;
    std::ofstream Out;
    Logger();

private:
    struct Params {
        bool LogToConsole = false;
        bool LogToFile = false;
    } currentParams;


public:
    Logger(const Logger&) = delete;

    Logger& operator=(const Logger&) = delete;

    static Logger *GetInstance();

    void Log(const std::string& Msg, bool SkipParams = false);

    void WriteOutput(const std::string& Path, const std::string& Buffer, bool OverWrite);

    void SetLogToConsole(bool LogToConsole);

    void SetLogToFile(bool LogToFile);

    void ClearLog();

    ~Logger();
};


#endif //ASTRATESTING_LOGGER_H
