#include <iostream>
#include <sstream>
#include <vector>
#include <string>

// TODO: finish the implementation of the infix parser, see the description below (and the prefix and postfix parsers for inspiration)

// IMPORTANT: some of the TODOs are marked as done as they were a part of the demonstration for the credit exam,
//   see the extra TODO at line 158

// this is just a simple demonstration for parsing, for more details, see https://www.ksi.mff.cuni.cz/teaching/nswi098-web/

// ----------------------------------------------

/*
    PARSING

    An expression is a sequence of tokens that can be evaluated to a value
    the tokens (terminals) can be numbers, operators, or parentheses
    in the grammar, we will use the following non-terminals: E (expression), T (term), F (factor)

    An expression can be written in different ways:
    1. prefix notation: + * 1 2 3, - + 1 2 3, * 1 + 2 3
    2. postfix notation: 1 2 * 3 +, 1 2 + 3 -, 1 2 3 + *
    3. infix notation: 1 * 2 + 3, 1 + 2 * 3, 1 * (2 + 3)

    The prefix and postfix notations do not need parentheses and they are much simpler to parse, but they are hard to read for humans
*/

// ----------------------------------------------

/*
    PARSER IMPLEMENTATION

    we will implement 3 parsers for expressions:
    1. prefix parser (https://en.wikipedia.org/wiki/Polish_notation)
    2. postfix parser (https://en.wikipedia.org/wiki/Reverse_Polish_notation)
    3. infix parser (https://en.wikipedia.org/wiki/Infix_notation)

    In all of the parsers, we will use the default >> operator for tokenization (i.e. we will use whitespace as a delimiter)
    - in more complex parsers, we would use a tokenizer (https://en.wikipedia.org/wiki/Lexical_analysis#Tokenization),
      see [tokenizer.cpp](tokenizer.cpp) or [regex_tokenizer](regex_tokenizer.cpp) for two examples of tokenizers
*/


// prefix notation grammar:
// E -> "+" E E | "-" E E | "*" E E | "/" E E | NUM

int prefix_parse_expression(std::istream& in) {
    std::string s;

    if (!(in >> s)) {
        throw std::runtime_error("bad input");
    }

    // we are looking at an operator (one of the first 4 cases of the grammar rule)
    if (s == "+" || s == "-" || s == "*" || s == "/") {
        // all of the 4 cases expect 2 expressions after the operator
        int a = prefix_parse_expression(in);
        int b = prefix_parse_expression(in);

        if (s == "+") {
            return a + b;
        } else if (s == "-") {
            return a - b;
        } else if (s == "*") {
            return a * b;
        } else {
            return a / b;
        }
    } else { // we are looking at a number (the last case of the grammar rule)
        return std::stoi(s);
    }
}

// postfix notation grammar:
// E -> E E "+" | E E "-" | E E "*" | E E "/" | NUM

int postfix_parse(std::istream& in, std::vector<int>& stack) {
    std::string s;

    while (in >> s) {
        // we are looking at an operator (one of the first 4 cases of the grammar rule)
        if (s == "+" || s == "-" || s == "*" || s == "/") {
            // in all of the 4 cases, we had to parse 2 expressions before the operator
            int b = stack.back(); // note that we are popping the stack in reverse order
            stack.pop_back();
            int a = stack.back();
            stack.pop_back();

            // we make the operation and push the result back to the stack
            if (s == "+") {
                stack.push_back(a + b);
            } else if (s == "-") {
                stack.push_back(a - b);
            } else if (s == "*") {
                stack.push_back(a * b);
            } else {
                stack.push_back(a / b);
            }
        } else { // we are looking at a number (the last case of the grammar rule)
            // we push the number to the stack
            stack.push_back(std::stoi(s));
        }
    }

    // we return the result of the expression
    if (stack.size() != 1) {
        throw std::runtime_error("bad input");
    }

    return stack.back();
}

// infix notation grammar: (the problem is that the operator is in the middle of the expression, so we have to do something clever)
// E -> T | E "+" T | E "-" T
// T -> F | T "*" F | T "/" F
// F -> NUM

// we will use recursive descent parsing (https://en.wikipedia.org/wiki/Recursive_descent_parser) that is similar to the prefix parser

/*
    DESCRIPTION OF THE ALGORITHM:

    we remember a "next" token that will be used to decide what to do next (in parser theory, this is called the lookahead token)

    for each non-terminal symbol, we create a function according to the right-hand side of its grammar rule,
    - for each non-terminal symbol in the right-hand side, we call the corresponding function
    - for each terminal symbol in the right-hand side, we check if the "next" token matches the terminal symbol
      - if it does, we consume the "next" token and continue (we request a new "next" token)
      - if it does not, we try a different case of the grammar rule (if there is one); or we throw an error

    for the grammar above, we would get the following functions: parse_expr, parse_term, parse_factor
*/

// There are 2 problems with the grammar above:
// 1. it is left-recursive (https://en.wikipedia.org/wiki/Left_recursion), so each function would call itself infinitely
// 2. it is ambiguous, so we would have to use backtracking (https://en.wikipedia.org/wiki/Backtracking) to try all possible cases

/*
    Thankfully, we can solve both problems at once by transforming the grammar into an unambiguous right-recursive grammar:

    transformed grammar: (on how to remove left recursion, see https://en.wikipedia.org/wiki/Left_recursion)
    E -> T E'                    // expression always starts with a term...; E' is the rest of the expression
    E' -> "+" T E' | "-" T E' | eps  // ... and then it can be followed by + or - (and then the rest of the expression) or it can end

    T -> F T'                    // term always starts with a factor...; T' is the rest of the term
    T' -> "*" F T' | "/" F T' | eps  // ... and then it can be followed by * or / (and then the rest of the term) or it can end

    F -> NUM                     // factor is a number
*/


// TODO (done): implement the infix parser just like the prefix and postfix parsers
//       you can use the same approach as in the prefix parser
//       NOTE: we can use a while loop instead of recursion to parse right-recursive grammars
//             so we can implement the E' and T' rules as while loops inside the E and T rules

    // grammar with while loops (each iteration of the while loop has to begin with an operator):
    // E -> T ( "+" T | "-" T )*
    // T -> F ( "*" F | "/" F )*

// TODO: change F -> NUM to F -> NUM | "(" E ")"

// EXTA-TODO: implement exponentiation with the ^ operator or ** operator

// EXTRA-EXTRA-TODO: implement the infix parser using the shunting-yard algorithm (https://en.wikipedia.org/wiki/Shunting-yard_algorithm)
// - the shunting-yard algorithm is more similar to the postfix parser

class Parser {
public:
    explicit Parser(std::istream& in) : in_(in) {
        next();
    }

    int parse_expr() {
        // TODO: implement the E -> T ( + T | - T )* rule
        int result = parse_term();
        while(true) {
            if (next_ == "+") {
                next();
                result += parse_term();
            } else if (next_ == "-") {
                next();
                result -= parse_term();
            } else {
                break;
            }
        }
        return result;
    }
    int parse_term() {
        // TODO: implement the T -> F ( * F | / F )* rule
        int result = parse_power();

        while(true) {
            if (next_ == "*") {
                next();
                result *= parse_power();
            } else if (next_ == "/") {
                next();
                result /= parse_power();
            } else {
                break;
            }
        }
        return result;
    }
    int parse_power() {

        int result = parse_factor();

        while(true) {
            if(next_ == "^" || next_ == "**") {
                next();
                result = count_power(result, parse_power());
            } else {
                break;
            }
        }
        return result;
    }

    int parse_factor() {
        // parse a number
        if (next_ == "(") {
            next();
            int result = parse_expr();
            if (next_ != ")") {
                throw std::runtime_error("expected )");
            }
            next();
            return result;
        } else {
            int result = std::stoi(next_);
            next();
            return result;
        }
    }

    int count_power(int base, int power) {
        int result = 1;
        for (int i = 0; i < power; i++) {
            result *= base;
        }
        return result;
    }

private:
    void next() {
        in_ >> next_;
    }

    std::istream& in_; // here, we could use an arbitrary tokenizer
    std::string next_; // next token (in parser theory, this is called the lookahead token)
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " <parser>" << std::endl;
        std::cerr << "parsers: prefix, postfix, infix" << std::endl;
        return 1;
    }

    std::string line;
    const std::string parser = argv[1];

    while (std::getline(std::cin, line)) {
        std::istringstream in(line);

        if (parser == "infix") {
            Parser parser(in);

            std::cout << parser.parse_expr() << '\n';
        } else if (parser == "prefix") {
            std::cout << prefix_parse_expression(in) << '\n';
        } else if (parser == "postfix") {
            std::vector<int> stack;

            std::cout << postfix_parse(in, stack) << '\n';
        } else {
            std::cerr << "unknown parser: " << parser << std::endl;
            return 1;
        }
    }
}
