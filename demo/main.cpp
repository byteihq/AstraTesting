// Copyright 2022 byteihq

#include "Logger.h"
#include "Terminal.h"
#include "Presets.h"
#include "Utils.h"
#include <boost/program_options.hpp>
#include <stdarg.h>

static std::string UserName = Utils::GetUserName();

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
    Logger::Log(TestName + "_TEST");
    Logger::Log(TestName + "_COMMAND: " + ExecCommand);
    auto res = Terminal::Exec(ExecCommand);
    if (!res.first) {
        Logger::Log(TestName + "_TEST Failed");
    }
    if (FileName.empty()) {
        return;
    }
    std::string Path = "/home/" + UserName + "/" + FileName;
    Logger::Log(TestName + "_OUTPUT:\n" + res.second);
    Logger::WriteOutput(Path, res.second);
    Logger::Log(TestName + "_FILE: " + Path);
}

namespace po = boost::program_options;

int main(int argc, char **argv) {
    po::options_description desc("Options");
    PINGParams pingParams;
    IPERFParams iperfParams;
    desc.add_options()
            ("ping_ip", po::value(&pingParams.IP), "IP to ping")
            ("ping_i", po::value(&pingParams.Interval), "Ping interval")
            ("ping_s", po::value(&pingParams.PacketSize), "Ping packet's size")
            ("ping_n", po::value(&pingParams.PacketsNumber), "Number of packets sent")
            ("iperf_c", po::value(&iperfParams.IP), "IPERF server's IP")
            ("iperf_p", po::value(&iperfParams.ThreadsNumber), "IPERF threads number")
            ("iperf_t", po::value(&iperfParams.ConnectionTime), "IPERF connection time");
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
    po::notify(vm);

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
