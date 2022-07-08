// Copyright 2022 byteihq

#ifndef ASTRATESTING_PRESETS_H
#define ASTRATESTING_PRESETS_H

#ifdef BUFSIZ
#undef BUFSIZ
#endif
#define BUFSIZ 1024

struct USERParams {
    std::string UserName = "u";
};

struct PINGParams {
    int PacketSize = 1400;
    int PacketsNumber = 10;
    float Interval = 0.1;
    std::string IP = "192.168.0.2";
};

struct IPERFParams {
    std::string IP = "192.168.0.2";
    int ThreadsNumber = 50;
    int ConnectionTime = 300;
};

#define LSHW_INSTALL "sudo apt-get install lshw -y"
#define LSHW_INSTALL_OUT "lshw_install_info.txt"
#define LSHW_TEST "sudo lshw -html -sanitize -numeric"
#define LSHW_OUT "lshw_info.html"

#define LSPCI_TEST "lspci -k | grep -i -EA2 net"
#define LSPCI_OUT "lspci_info.txt"

#define PING_TEST "sudo ping -c %i -s %i -i %.3g %s"
#define PING_OUT "ping_info.txt"

#define IPERF_INSTALL "sudo apt-get install iperf -y"
#define IPERF_INSTALL_OUT "iperf_install_info.txt"
#define IPERF_TEST "script -c 'iperf -c %s -P %i -r -t %i'"
#define IPERF_OUT "ip_info.txt"

#define AUDIO_TEST_INFO "aplay -l"
#define AUDIO_TEST_INFO_OUT "audio_info.txt"
#define AUDIO_TEST "audacity"

#define LSPCI_VIDEO_TEST "lspci -v | grep -i VGA"
#define LSPCI_VIDEO_TEST_3D "lspci -k | grep -EA2 'VGA|3D'"
#define LSPCI_VIDEO_TEST_VIDEO_DRIVER "sudo lshw -c video | grep driver"
#define LSPCI_VIDEO_OUT "vga_adapt-geter.txt"

#define CPU_INFO_TEST "cat /proc/cpuinfo"
#define CPU_INFO_OUT "base_cpu.txt"
#define LSCPU_TEST "lscpu"
#define LSCPU_OUT "info_lscpu.txt"
#define CPU_FREQ_INSTALL "sudo apt-get install cpufrequtils -y"
#define CPU_FREQ_INSTALL_OUT "cpu_install_info.txt"
#define CPU_FREQ_TEST "сpufreq-info"
#define CPU_FREQ_OUT "cpu_freq.txt"

#define LM_SENSORS_INSTALL "sudo apt-get install lm-sensors -y"
#define LM_SENSORS_INSTALL_OUT "lm_sensors_install.txt"
#define LM_SENSORS_TEST "sensors"
#define LM_SENSORS_OUT "sensors_info.txt"

#define VIDEO_STRESS_TEST_INSTALL "sudo apt-get install mesa-utils -y"
#define VIDE_STRESS_TEST_INSTALL_OUT "mesa_utils_install.txt"
#define VIDEO_STRESS_TEST_INFO "glxgears -info"
#define VIDEO_STRESS_TEST_INFO_OUT "glxgears_info.txt"
#define VIDEO_STRESS_TEST_RENDER "glxinfo | grep -i renderer"
#define VIDEO_STRESS_TEST_RENDER_OUT "info_renderer.txt"
#define VIDEO_STRESS_TEST "glxinfo -B"
#define VIDEO_STRESS_TEST_OUT "glxinfo.txt"

#endif //ASTRATESTING_PRESETS_H
