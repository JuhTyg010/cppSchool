#include "multiples.hpp"


Multiples::Multiples(int initial_from, int initial_to)
        : from_{initial_from}, to_(initial_to) {}

void Multiples::print_multiples(int base) const {
    // print base * from_, base * (from_ + 1), ..., base * to_
    for (size_t i = from_; i <= to_; ++i) {
        std::cout << std::format("{0} * {1} = {2}", base, i, base * i) << std::endl;
    }

    // format it as such (line after line): {i} * {base} = {i * base}
    //  ({...} as in string interpolation)
}

std::size_t Multiples::set_options(const std::vector<std::string>& args) {
    // returns the number of arguments that are just program options (not numbers)
    // - we use the fact that program options are guaranteed to come first
    std::size_t counter = 0;
    for (auto it = args.begin(); it < args.end(); ++it)
    {
        if ( it->starts_with('-')) {
            if (it->size() > 2)
            {
                std::cerr << "wrong argument" << std::endl;
            }
            if ((*it)[1] == 'f') {
                from_ = std::stoi(*(it + 1));
            }
            else if ((*it)[1] == 't') {
                to_ = std::stoi(*(it + 1));
            }
            else
            {
                std::cerr << "wrong argument" << std::endl;
            }
            counter += 2;
        }
    }
    return counter;
}

void Multiples::print_table(std::span<const std::string> args) const {
    // calls print_multiples for each arg (std::stoi from <string> might come useful)
    for(auto&& arg : args)
    {
        print_multiples(std::stoi(arg));
    }
}