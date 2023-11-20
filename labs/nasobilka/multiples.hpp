
#ifndef MULTIPLES_HPP_
#define MULTIPLES_HPP_

#include <iostream>
#include <vector>
#include <format>
#include <span>


class Multiples {
public: /* starts the public section */
    // constructor that *initializes* from_ and to_
    //  (we showcase two different styles of initializers,
    //   their difference will be relevant in containers)
    Multiples(int initial_from, int initial_to);
    // *const* after method declarator (and before body
    //  signifies that it doesn't modify the state
    //  (the const applies to the hidden Multiples argument):
    // we take a readonly reference to the vector of args
    void print_table(std::span<const std::string> args) const;

    // notice that this method can change the state (there is no *const* before the body)
    std::size_t set_options(const std::vector<std::string>& args);

private: /* starts the private section */
    int from_, to_;
    void print_multiples(int base) const;
};

#endif