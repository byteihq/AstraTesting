// Copyright 2022 byteihq

#ifndef ASTRATESTING_LOGGER_H
#define ASTRATESTING_LOGGER_H

#include <string>

class Logger {
public:
    static void Log(const std::string& Msg);

    static void WriteOutput(const std::string& Path, const std::string& Buffer);
};


#endif //ASTRATESTING_LOGGER_H
