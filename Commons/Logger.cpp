// Copyright 2022 byteihq

#include "Logger.h"
#include "Presets.h"

#ifdef CONSOLE_OUTPUT
#include <iostream>
#endif

#include <fstream>

void Logger::Log(const std::string &Msg) {
#if defined(CONSOLE_OUTPUT) || defined(FILE_OUTPUT)
    time_t rawtime = 0;
    tm *timeinfo = nullptr;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char buf[BUFSIZ];
    sprintf(buf, "%02d:%02d:%02d: ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
#endif
#ifdef CONSOLE_OUTPUT
    std::cout << buf << Msg << std::endl;
#endif
#ifdef FILE_OUTPUT
    std::ofstream out("./log", std::ios::app);
    out << buf << Msg << std::endl;
    out.close();
#endif
}

void Logger::WriteOutput(const std::string &Path, const std::string &Buffer) {
    std::ofstream out(Path, std::ios::app);
    out << Buffer;
    out.close();
}
