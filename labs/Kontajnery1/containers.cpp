#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

// this is a simple demonstration of basic container usage

int main() {
    // TODO: define a map with key type std::string and value type int
    //  containing some fruits and their corresponding counts
    //  - use the initializer list syntax: { {key1, value1}, {key2, value2}, ... }

    std::map<std::string, int> fruits = {{"apple", 5}, {"banana", 3}, {"orange", 2}, {"pear", 1}};

    // TODO: print the map using a range-based for loop and structured bindings
    for(auto&& it = fruits.begin(); it != fruits.end(); it++){
        std::cout << it->first << ": " << it->second << std::endl;
    }

    // TODO: define a vector of numbers from 1 to 11, prepare the vector with 11 elements (std::vector<int>(11))
    // and use std::iota(beg_it, end_it, init) to fill the vector with numbers, it automatically increments the init value
    std::vector<int> numbers(11);
    std::iota(numbers.begin(), numbers.end(), 1);

    // TODO: print every second number in the vector, use const_iterators
    for(auto it = numbers.cbegin(); it != numbers.cend(); ++it){    //it +=2 skips cend() and print unwanted memory
        if((numbers.cbegin()-it) % 2 == 0) std::cout << *it << ' ';
    }
    std::cout << std::endl;


    // TODO: fill the vector with partial sums of the vector's suffixes, use reverse iterators and a temporary value
    //        note that semantically, the rend() is still a result of multiple increments of `auto it = rbegin()` just like with begin() and end()
    int suffix = 0;
    for(auto&& it = numbers.rbegin(); it != numbers.rend(); ++it ){
        suffix += numbers[rend(numbers) - it - 1];
        numbers[rend(numbers)-it - 1] = suffix;
    }


    // TODO: print the contents of the vector using a range-based for loop
   for(auto&& it = numbers.begin(); it != numbers.end(); ++it){
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
}
