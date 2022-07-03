// Copyright 2022 byteihq

#include "Utils.h"
#include <unistd.h>
#include <pwd.h>

std::string Utils::GetUserName() {
    passwd *pw = getpwuid(geteuid());
    if (pw) {
        return {pw->pw_name};
    }
    return {"u"};
}
