// Copyright 2022 byteihq

#ifndef ASTRATESTING_BASETEST_H
#define ASTRATESTING_BASETEST_H

#include <string>
#include <nlohmann/json.hpp>

class BaseTest {
private:
    struct Params {
        std::string TestName;
        bool Install = false;
        std::string InstallExecute;
        std::string InstallOut;
        bool Test = false;
        std::string TestExecute;
        std::string TestOut;

        Params() = default;

        explicit Params(const std::string &TN, bool I, const std::string &IE, const std::string &IO, bool T,
                        const std::string &TE, const std::string &TO) :
                TestName(TN),
                Install(I),
                InstallExecute(IE),
                InstallOut(IO),
                Test(T),
                TestExecute(TE),
                TestOut(TO) {}
    } currentParams;

private:
    static void Test(const std::string &TestName, const std::string &ExecCommand, const std::string &FileName = "");

public:
    BaseTest() = delete;

    void Run() const;

    explicit BaseTest(const std::string &TestName, const nlohmann::json &config);
};


#endif //ASTRATESTING_BASETEST_H
