#pragma once

#include <string>
#include <vector>

using std::string, std::vector;

namespace Utils {
    class String {
    public:
        static vector<string> split(string haystack, string needle);
    };
}