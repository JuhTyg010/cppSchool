#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>


#ifdef EXPRESSIONS1
# include "expressions_any.hpp"
#elif defined(EXPRESSIONS2)
# include "expressions_variant.hpp"
#else
# error "Please define EXPRESSIONS1 or EXPRESSIONS2"
# include "expressions_variant.hpp" // to prevent further compile errors
#endif

using namespace expressions;

Expression::ptr parse_token(std::string&& token, std::ostream& err) { // `&&` means that we consume the argument (it's potentially moved)
    if (std::isdigit(token[0]) || token[0] == '.') {
        try {
                if (std::all_of(token.begin(), token.end(), [](char c) { return std::isdigit(c); }))
                    return std::make_shared<Constant>(Value(std::stoi(token)));
                else
                    return std::make_shared<Constant>(Value(std::stod(token)));
        } catch (const std::invalid_argument&) {
            err << "Invalid number: " << token << std::endl;
            return nullptr;
        } catch (const std::out_of_range&) {
            err << "Number out of range: " << token << std::endl;
            return nullptr;
        }
    } else {
        return std::make_shared<VariableExpression>(std::move(token));
    }
}

Expression::ptr parse_expression(std::istream& in, std::ostream& err) {
    std::string token;

    if (!(in >> token) || token == "=" || (token == "+" && !(in >> token))) {
        err << "Expected expression" << std::endl;
        return nullptr;
    }

    Expression::ptr expr = parse_token(std::move(token), err);


    while (in >> token) {
        if (token == "+") {
            if (!(in >> token)) {
                err << "Expected expression" << std::endl;
                return nullptr;
            }

            Expression::ptr rhs = parse_token(std::move(token), err);

            if (!rhs) {
                err << "Failed to parse expression" << std::endl;
                return nullptr;
            }

            expr = std::make_shared<AddExpression>(std::move(expr), std::move(rhs));
        } else {
            err << "Expected '+'" << std::endl;
            return nullptr;
        }
    }

    return expr;
}

void program_loop(std::istream& in = std::cin, std::ostream& out = std::cout, std::ostream& err = std::cerr) {
    Expression::context ctx;
    std::string line;
    std::string variable;

    while (std::getline(in, line)) {
        if (line.empty()) {
            continue;
        }

        if (line == "quit") {
            break;
        }

        std::istringstream line_stream(line);


        if (!(line_stream >> variable))
            continue;

        if (variable == "=") {
            Expression::ptr expr = parse_expression(line_stream, err);

            if (!expr) {
                err << "Failed to parse expression" << std::endl;
                continue;
            }

            expr->evaluate(ctx).print(out) << std::endl;
        } else {
            line_stream >> std::ws;
            char eq;

            if (!(line_stream >> eq) || eq != '=') {
                err << "Expected '=' after variable name" << std::endl;
                continue;
            }

            if (ctx.contains(variable)) {
                err << "Variable '" << variable << "' already exists" << std::endl;
                continue;
            }

            Expression::ptr expr = parse_expression(line_stream, err);

            if (!expr) {
                err << "Failed to parse expression" << std::endl;
                continue;
            }

            ctx.try_emplace(variable, expr);
        }
    }
}

int main() {
    program_loop();
}