// Copyright 2022 byteihq

#ifndef ASTRATESTING_BASETEST_H
#define ASTRATESTING_BASETEST_H

#include <string>
#include <nlohmann/json.hpp>

struct Params {
    std::string TestName;
    bool InstallEnabled = false;
    std::string InstallExecute;
    std::string InstallOut;
    bool TestEnabled = false;
    std::string TestExecute;
    std::string TestOut;
    bool RemoveAfterEnabled = false;
    std::string RemoveAfterExecute;

    Params() = default;

    explicit Params(const std::string &TN, bool I, const std::string &IE, const std::string &IO, bool T,
                    const std::string &TE, const std::string &TO, bool RAE, const std::string &RAEx) :
            TestName(TN),
            InstallEnabled(I),
            InstallExecute(IE),
            InstallOut(IO),
            TestEnabled(T),
            TestExecute(TE),
            TestOut(TO),
            RemoveAfterEnabled(RAE),
            RemoveAfterExecute(RAEx) {}
};

class BaseTest {
private:
    Params currentParams;

    static void Test(const std::string &TestName, const std::string &ExecCommand, const std::string &FileName = "");

public:
    BaseTest() = default;

    virtual ~BaseTest() = default;

    virtual void Run() const;

    virtual void Init(const std::string &TestName, const nlohmann::json &config);
};


#endif //ASTRATESTING_BASETEST_H
