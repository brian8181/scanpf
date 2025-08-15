#include "regex_ext.hpp"

class RegexExt {
public:
    static std::string replaceAll(const std::string& text, const std::string& pattern, const std::string& replacement) {
        return std::regex_replace(text, std::regex(pattern), replacement);
    }

private:
    std::string pattern;
    std::regex expr;
};
