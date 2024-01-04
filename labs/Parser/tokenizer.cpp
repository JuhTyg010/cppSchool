#include <iostream>
#include <string>
#include <variant>

// This is a simple tokenizer that can be used to tokenize the last ReCoDex assignment.

class Tokenizer {
public:
    enum class Token { EQ, HASH, NUM, NAME, LINE_END, END };

    explicit Tokenizer(std::istream& in) : in_(in) {
        next_ = in_.get();
    }

    const std::string& get_name() const {
        return std::get<std::string>(value_);
    }

    int get_num() const {
        return std::get<int>(value_);
    }

    Token get_next() {
        for (;;) {
            if (in_.eof()) {
                return Token::END;
            }

            if (next_ == '\n') {
                next_ = in_.get();
                return Token::LINE_END;
            }

            if (std::isspace(next_)) {
                next_ = in_.get();
                continue;
            }

            if (next_ == '=') {
                next_ = in_.get();
                return Token::EQ;
            }

            if (next_ == '#') {
                next_ = in_.get();
                return Token::HASH;
            }

            if (std::isdigit(next_)) {
                int value = 0;

                do {
                    value = value * 10 + (next_ - '0');
                } while (in_.get(next_) && std::isdigit(next_));

                value_ = value;
                return Token::NUM;
            }

            if (std::isalpha(next_)) {
                std::string value;

                do {
                    value = value + next_;
                } while (in_.get(next_) && std::isalnum(next_));

                value_ = value;
                return Token::NAME;
            }
        }
    }

private:
    char next_;
    std::variant<int, std::string> value_;

    std::istream& in_;
};

int main() {
    Tokenizer parser(std::cin);
    std::string line;

    for (;;)
        switch (parser.get_next()) {
            case Tokenizer::Token::EQ:
                std::cout << "EQ" << ' ';
                break;
            case Tokenizer::Token::HASH:
                std::cout << "HASH" << ' ';
                break;
            case Tokenizer::Token::NUM:
                std::cout << "NUM(" << parser.get_num() << ')' << ' ';
                break;
            case Tokenizer::Token::NAME:
                std::cout << "NAME(" << parser.get_name() << ')' << ' ';
                break;
            case Tokenizer::Token::LINE_END:
                std::cout << "LINE_END" << std::endl;
                break;
            case Tokenizer::Token::END:
                std::cout << "END" << std::endl;
                return 0;
        }
}
