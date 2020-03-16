//
// Created by vell on 19-5-10.
//
#include "StringUtils.h"

std::string strFmt(const std::string &fmt_str, ...) {
    int final_n, n =
            ((int) fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
    std::unique_ptr<char[]> formatted;
    va_list ap;
    while (1) {
        formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
        strcpy(&formatted[0], fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
            n += abs(final_n - n + 1);
        else
            break;
    }
    return std::string(formatted.get());
}

int str2Int(const std::string &s) {
    // Convert from a string to a T
    // Type T must support >> operator
    int t;
    std::istringstream ist(s);
    ist >> t;
    return t;
}

int buffer2Int(const std::string &s) {
    int t;
    memcpy(&t, s.c_str(), sizeof(t));
    return t;
}

std::string double2Str(double d) {
    std::ostringstream ost;
    ost << d;
    return ost.str();
}

double str2Double(const std::string &s) {
    double t;
    std::istringstream ist(s);
    ist >> t;
    return t;
}

bool regMatch(const std::string &pattern, const std::string &text) {
    std::regex r(pattern);
    std::smatch result;
    return regex_search(text, result, r);
}

std::string randStr(int len) {
    srand(time(nullptr));
    char str[len + 1];
    str[len] = '\0';
    for (int i = 0; i < len; ++i) {
        switch ((rand() % 3)) {
            case 1:
                str[i] = 'A' + rand() % 26;
                break;
            case 2:
                str[i] = 'a' + rand() % 26;
                break;
            default:
                str[i] = '0' + rand() % 10;
                break;
        }
    }
    return str;
}

