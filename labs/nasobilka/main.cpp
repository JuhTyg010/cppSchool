#include <iostream>
#include <vector>
#include <format>

/* (EXTRA TODOs are for those who want to do some extra work)

TODO: implement the function bodies for `print_multiples` and `print_table`
  - use: for (std::size_t i = 0; i < args.size(); ++i) { ... args[i] ... }
     - this is a C-style loop
  - change it to: for (auto it = args.begin(); it != args.end(); ++it) { ... *it ... }
    - args.begin() is an iterator that points to the first element;
      args.end() points to args[args.size()]
    - this is a C-style loop with iterators (more general, slightly safer)
    - *it accesses the iterated value, ++it increments the iterator
  - change that to: for (auto&& arg : args) { ... arg ... }
    - this is range-based for; more modern, shorter, even safer and easier to read
    - auto&& is an idiom for "create an appropriate reference"
    - similar to C# `foreach` or Python `for arg in args`

TODO: make `print_multiples` function private (it is never called from outside)

TODO: change print_table(const std::vector<std::string> &args)
      to print_table(std::span<const std::string> args)
                                                  ^ notice that there is no "&", as std::span already represents a reference
      this will require an extra #include
       (consult https://en.cppreference.com/w/cpp/container/span)

TODO: implement set_options and then store its result in *skipped*
      then pass {args.begin() + skipped, args.end()} to print_table (instead of args)

      what does it mean? if at home, you can consult:
      - https://en.cppreference.com/w/cpp/container/vector/begin
        - there is a nice picture and examples
      - https://en.cppreference.com/w/cpp/container/span/span (3) <- called by the {...}

TODO: move function implementations outside of the class
  - for example:

    ```cpp
    class Multiples { ... void print_multiples(int base) const; ... };

    void Multiples::print_multiples(int base) const { ... }
    ```

  we are left with class definition and then separate method definitions

TODO: move the class definition to multiples.hpp and method definitions to multiples.cpp
  - now, if we change main, we compile only a part of the program
  - remember to use #include "multiples.hpp" in both cpp files
  - add a header-guard to the .hpp file:

    ```cpp
    #ifndef MULTIPLES_HPP_
    #define MULTIPLES_HPP_
    // contents of the file are here
    #endif
    ```

EXTRA TODO: let's say the options are not guaranteed to come first;
            reimplement set_options such that it takes `std::vector<std::string> &args`
            and it efficiently erases the options from it (and then, it returns void).

    hint: two iterators (see the first TODO), one reads input and the other writes the actual numeric arguments back to the vector
      - the two pointers operate on the same vector
      - write to an iterated value: *it = new_value
      - after it is done, we `resize` the vector
*/

class Multiples {
public: /* starts the public section */
    // constructor that *initializes* from_ and to_
    //  (we showcase two different styles of initializers,
    //   their difference will be relevant in containers)
    Multiples(int initial_from, int initial_to)
            : from_{initial_from}, to_(initial_to) {}

    // *const* after method declarator (and before body
    //  signifies that it doesn't modify the state
    //  (the const applies to the hidden Multiples argument):
    void print_multiples(int base) const {
        // print base * from_, base * (from_ + 1), ..., base * to_
        for (int i = from_; i <= to_; ++i) {
            std::cout << std::format("{0} * {1} = {2}", base, i, base * i) << std::endl;
        }

        // format it as such (line after line): {i} * {base} = {i * base}
        //  ({...} as in string interpolation)
        // if you love python, you can try: for (int i : std::ranges::views::iota(first, end))
    }

    // we take a readonly reference to the vector of args
    void print_table(const std::vector<std::string>& args) const {
        // calls print_multiples for each arg (std::stoi from <string> might come useful)
        for(std::size_t i = 0; i < args.size(); ++i)
        {
            print_multiples(std::stoi(args[i]));
        }
    }

    // notice that this method can change the state (there is no *const* before the body)
    std::size_t set_options(const std::vector<std::string>& args) {
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


        return counter; // this means "return default"
    }

private: /* starts the private section */
    int from_, to_;
};

int main(int argc, char *argv[]) {
    // copy cmd arguments (c-strings) to a c++ container with c++ string:
    std::vector<std::string> args(argv + 1 /* beginning of args, we skip the program name */,
                                  argv + argc /* end of args */); // pointer arithmetic

    // create the multiples object on the stack
    Multiples multiples(1, 10); // DO NOT USE *new*, this is not C#/Java

    int count = multiples.set_options(args); // does nothing for first few iterations of the assignment
    multiples.print_table({args.begin()+count, args.end()});
}