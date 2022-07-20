// Copyright 2022 byteihq

#ifndef ASTRATESTING_INTERNETTEST_H
#define ASTRATESTING_INTERNETTEST_H

#include "BaseTest.h"
#include <string>
#include <vector>

class InternetTest : public BaseTest {
public:
    void Init(const std::string &TestName, const nlohmann::json &config) override;

    void Run() const override;

private:
    struct InternetParams {
        std::string TestName;
        bool TestEnabled = false;
        std::vector<std::string> Urls;
        std::string TestOut;

        InternetParams() = default;

        explicit InternetParams(const std::string &TN, bool TE, const std::vector<std::string> &U,
                                const std::string &TO) : TestName(TN), TestEnabled(TE), Urls(U), TestOut(TO) {}
    } currentParams;

    static size_t curl_write(char *ptr, size_t size, size_t nmemb, void *userdata);
};


#endif //ASTRATESTING_INTERNETTEST_H
