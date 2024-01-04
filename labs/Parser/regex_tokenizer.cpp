#include <cctype>
#include <iostream>
#include <regex>
#include <string>

// This is a simple tokenizer that can be used to tokenize the last ReCoDex assignment.
// - this one is using regular expressions to tokenize the input
// - it is much shorter than the original one (tokenizer.cpp) and it is also easier to extend, but it can be slower

int main() {
    // "[0-9a-zA-Z]+|." is a regular expression that matches alphanumeric sequences and single characters
    const std::regex token(R"([0-9a-zA-Z]+|.)"); // R"()" is a raw string literal
    std::string line;
    
    while (std::getline(std::cin, line)) {
        std::sregex_iterator start(line.begin(), line.end(), token);
        const std::sregex_iterator end;

        for (auto i = start; i != end; ++i) {
            std::string token = i->str();

            if (token == "=") {
                std::cout << "EQ" << ' ';
            } else if (token == "#") {
                std::cout << "HASH" << ' ';
            } else if (std::isdigit(token[0])) {
                std::cout << "NUM(" << token << ')' << ' ';
            } else if (std::isalpha(token[0])) {
                std::cout << "NAME(" << token << ')' << ' ';
            } else if (std::isspace(token[0])) {
                continue;
            } else {
                std::cout << "UNKNOWN(" << token << ')' << ' ';
            }
        }

        std::cout << "LINE_END" << '\n';
    }

    std::cout << "END" << std::endl;
}
