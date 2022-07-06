// Copyright 2022 byteihq

#include "Logger.h"
#include "Terminal.h"
#include "Presets.h"
#include <stdarg.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

static std::string Path = "/home/";

std::string InsertParams(const char *ExecCommand, ...) {
    char res[BUFSIZ];
    std::memset(res, 0, BUFSIZ);
    va_list vaArgList{};
    va_start(vaArgList, ExecCommand);
    vsnprintf(res, BUFSIZ - 1, ExecCommand, vaArgList);
    va_end(vaArgList);
    return res;
}

void Test(const std::string &TestName, const std::string &ExecCommand, const std::string &FileName = "") {
    Logger::GetInstance()->Log(TestName + "_TEST");
    Logger::GetInstance()->Log(TestName + "_COMMAND: " + ExecCommand);
    auto res = Terminal::Exec(ExecCommand);
    if (!res.first) {
        Logger::GetInstance()->Log(TestName + "_TEST Failed");
    }
    if (FileName.empty()) {
        return;
    }
    Logger::GetInstance()->Log(TestName + "_OUTPUT:\n" + res.second);
    Logger::GetInstance()->WriteOutput(Path + "/" + FileName, res.second);
    Logger::GetInstance()->Log(TestName + "_FILE: " + Path + "/" + FileName);
}

int main(int argc, char *argv[]) {
    if (getuid()) {
        std::cout << "You should run this program as super-user";
        return -1;
    }

    PINGParams pingParams;
    IPERFParams iperfParams;
    USERParams userParams;
    for (size_t i = 0; i < argc; ++i) {
        if (i == 0) {
            continue;
        }
        std::string arg(argv[i]);
        if (!(arg.size() > 2 && arg[0] == '-' && arg[1] == '-')) {
            continue;
        }
        int pos = arg.find('=');
        if (pos == std::string::npos) {
            continue;
        }
        std::string param(arg.begin() + 2, arg.begin() + pos);
        std::string value(arg.begin() + pos + 1, arg.end());
        if (param == "user") {
            userParams.UserName = std::move(value);
        } else if (param == "ping_ip") {
            pingParams.IP = value;
        } else if (param == "ping_i") {
            try {
                pingParams.Interval = std::stof(value);
            } catch (...) {}
        } else if (param == "ping_s") {
            try {
                pingParams.PacketSize = std::stoi(value);
            } catch (...) {}
        } else if (param == "ping_n") {
            try {
                pingParams.PacketsNumber = std::stoi(value);
            } catch (...) {}
        } else if (param == "iperf_c") {
            iperfParams.IP = std::move(value);
        } else if (param == "iperf_p") {
            try {
                iperfParams.ThreadsNumber = std::stoi(value);
            } catch (...) {}
        } else if (param == "iperf_t") {
            try {
                iperfParams.ConnectionTime = std::stoi(value);
            } catch (...) {}
        }
    }

    Path += userParams.UserName;
//  LSHW_TEST
    Test("LSHW", LSHW_TEST, LSHW_OUT);

//  LSPCI
    Test("LSPCI", LSPCI_TEST, LSPCI_OUT);

//  PING
    Test("PING", InsertParams(PING_TEST, pingParams.PacketsNumber, pingParams.PacketSize, pingParams.Interval,
                              pingParams.IP.c_str()), PING_OUT);

// IPERF
    Test("IPERF_INSTALL", IPERF_INSTALL, IPERF_INSTALL_OUT);
    Test("IPERF",
         InsertParams(IPERF_TEST, iperfParams.IP.c_str(), iperfParams.ThreadsNumber, iperfParams.ConnectionTime),
         IPERF_OUT);

//  AUDIO
    Test("AUDIO_INFO", AUDIO_TEST_INFO, AUDIO_TEST_INFO_OUT);
    Test("AUDIO", AUDIO_TEST);

// LSPCI VIDEO
    Test("LSPCI_VIDEO", LSPCI_VIDEO_TEST, LSPCI_VIDEO_OUT);
    Test("LSPCI_VIDEO_3D", LSPCI_VIDEO_TEST_3D, LSPCI_VIDEO_OUT);
    Test("LSPCI_VIDEO_VIDEO_DRIVER", LSPCI_VIDEO_TEST_VIDEO_DRIVER, LSPCI_VIDEO_OUT);

// CPU TEST
    Test("CPU_INFO", CPU_INFO_TEST, CPU_INFO_OUT);
    Test("LSCPU", LSCPU_TEST, LSCPU_OUT);
    Test("CPU_FREQ_INSTALL", CPU_FREQ_INSTALL, CPU_FREQ_INSTALL_OUT);
    Test("CPU", CPU_FREQ_TEST, CPU_FREQ_OUT);

// LM_SENSORS
    Test("LM_SENSORS_INSTALL", LM_SENSORS_INSTALL, LM_SENSORS_INSTALL_OUT);
    Test("LM_SENSORS", LM_SENSORS_TEST, LM_SENSORS_OUT);

//  VIDEO_STRESS_TEST
    Test("VIDEO_STRESS_TEST_INSTALL", VIDEO_STRESS_TEST_INSTALL, VIDE_STRESS_TEST_INSTALL_OUT);
    Test("VIDEO_STRESS_TEST_INFO", VIDEO_STRESS_TEST_INFO, VIDEO_STRESS_TEST_INFO_OUT);
    Test("VIDEO_STRESS_TEST_RENDER", VIDEO_STRESS_TEST_RENDER, VIDEO_STRESS_TEST_RENDER_OUT);
    Test("VIDEO_STRESS_TEST", VIDEO_STRESS_TEST, VIDEO_STRESS_TEST_OUT);
    return 0;
}
