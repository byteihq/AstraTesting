// Copyright 2022 byteihq

#include "InternetTest.h"
#include "Logger.h"
#include "Config.h"
#include <sstream>
#include <curl/curl.h>
#include <chrono>

static std::vector<std::chrono::high_resolution_clock::time_point> times;
static size_t downloadedSize = 0;
#define BUFFER_SIZE 1024

void InternetTest::Init(const std::string &TestName, const nlohmann::json &config) {
    std::stringstream ss;
    try {
        InternetParams NewParams{
                TestName,
                config.at("TestEnabled").get<bool>(),
                config.at("Urls").get<std::vector<std::string>>(),
                config.at("TestOut").get<std::string>()
        };

        currentParams = NewParams;
    } catch (const nlohmann::json::exception &ex) {
        Logger::GetInstance()->Log(std::string("Failed to unparse presets settings, error:\n") + std::string(ex.what()),
                                   true);
    }
    ss << TestName << " ready:"
       << "\n\tTestEnabled: " << std::boolalpha << currentParams.TestEnabled
       << "\n\tUrls: ";
    for (const auto &Url: currentParams.Urls) {
        ss << Url << " ";
    }
    ss << "\n\tTestOut: " << currentParams.TestOut;
    Logger::GetInstance()->Log(ss.str(), true);
}

size_t InternetTest::curl_write(char *ptr, size_t size, size_t nmemb, void *userdata) {
    times.push_back(std::chrono::high_resolution_clock::now());
    downloadedSize += size * nmemb;
    return size * nmemb;
}

void InternetTest::Run() const {
    if (!currentParams.TestEnabled) {
        return;
    }
    std::string output = currentParams.TestName + '\n';

    CURL *curl = curl_easy_init();
    CURLcode result;
    char errorBuf[BUFFER_SIZE];
    char contents[BUFFER_SIZE];

    if (!curl) {
        Logger::GetInstance()->Log("Failed to initialize curl");
        return;
    }
    float avgSpeed = 0;
    size_t sUrls = 0;
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuf);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, InternetTest::curl_write);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, contents);
    for (const auto &Url: currentParams.Urls) {
        times.clear();
        downloadedSize = 0;
        curl_easy_setopt(curl, CURLOPT_URL, Url.c_str());
        result = curl_easy_perform(curl);
        if (result != CURLE_OK) {
            output += "Failed to connect to " + Url + '\n';
            continue;
        }
        if (times.size() <= 1) {
            output += "Failed to collect info about " + Url + '\n';
            continue;
        }
        uint32_t time = 0;
        for (size_t i = 0; i < times.size() - 1; ++i) {
            time += std::chrono::duration_cast<std::chrono::microseconds>(times[i + 1] - times[i]).count();
        }
        float speed = downloadedSize / 1024.f / 1024.f / time * 1000000.f;
        avgSpeed += speed;
        output += Url + " speed: " + std::to_string(speed) + " MBs\n";
        ++sUrls;
    }
    avgSpeed /= sUrls;
    output += "Avg speed: " + std::to_string(avgSpeed) + " MBs";
    Logger::GetInstance()->Log(output);
    Logger::GetInstance()->WriteOutput(Config::GetInstance()->GetPresets().OutputPath + "/" + currentParams.TestOut,
                                       output,
                                       Config::GetInstance()->GetPresets().RewriteExistFiles);
    Logger::GetInstance()->Log(
            currentParams.TestName + "_FILE: " + Config::GetInstance()->GetPresets().OutputPath + "/" +
            currentParams.TestOut);
    curl_easy_cleanup(curl);
}
