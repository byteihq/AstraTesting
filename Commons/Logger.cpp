// Copyright 2022 byteihq

#include "Logger.h"
#include <iostream>

class Config;

Logger::Logger() : Out("./log.txt", std::ios::app) {}

void Logger::Log(const std::string &Msg, bool SkipParams) {
    if (!SkipParams && !currentParams.LogToConsole && !currentParams.LogToFile) {
        return;
    }

    time_t rawtime = 0;
    time(&rawtime);
    tm *timeinfo = localtime(&rawtime);
    char buf[BUFSIZ];
    sprintf(buf, "%02d:%02d:%02d: ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    if (SkipParams || currentParams.LogToConsole) {
        std::cout << buf << Msg << std::endl;
    }

    if (currentParams.LogToFile) {
        Out << buf << Msg << std::endl;
    }
}

void Logger::WriteOutput(const std::string &Path, const std::string &Buffer, bool OverWrite) {
    std::ofstream out;
    if (OverWrite) {
        out.open(Path, std::ios::trunc);
    } else {
        out.open(Path, std::ios::app);
    }
    if (!out.is_open()) {
        Log("Failed to open " + Path);
        return;
    }
    out << Buffer;
    out.close();
}

Logger::~Logger() {
    Out.close();
}

Logger *Logger::GetInstance() {
    static Logger logger;
    return &logger;
}

void Logger::SetLogToConsole(bool LogToConsole) {
    currentParams.LogToConsole = LogToConsole;
}

void Logger::SetLogToFile(bool LogToFile) {
    currentParams.LogToFile = LogToFile;
}

void Logger::ClearLog() {
    Out.close();
    Out.open("./log.txt", std::ofstream::out | std::ofstream::trunc);
}
