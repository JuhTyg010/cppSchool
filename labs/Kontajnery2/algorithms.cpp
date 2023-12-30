#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <map>
#include <ranges>

// this is a demonstration of the algorithms from the standard library

int main() {
    // TODO: read a sequence of integers from stdin and store them in a vector
    //   there is a twist: use std::copy, std::istream_iterator and std::back_inserter
    std::vector<int> numbers;
    std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::back_inserter(numbers));

    // TODO: print the numbers in the vector using std::copy, std::ostream_iterator and std::cout; separate the numbers with a newline
    std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, "\n"));
    // TODO: sort the vector using std::sort; compare the numbers using std::greater<int>
    std::sort(numbers.begin(), numbers.end(), std::greater<int>());
    // TODO: print the squares of the numbers in the vector using std::transform, std::ostream_iterator and std::cout; separate the numbers with a newline
    //   use a lambda expression to square the numbers
    std::transform(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, "\n"), [](int x) {return x*x;});
    // TODO: remove all the numbers that are divisible by 3 using std::remove_if and a subsequent std::vector::erase
    //   you can write both algorithms as a single statement
    numbers.erase(std::remove_if(numbers.begin(), numbers.end(), [](int x) {return x % 3 == 0;}), numbers.end());
    // TODO: insert the numbers into a set using std::copy and std::inserter, you have to pass some iterator to the inserter (begin or end) as well
    std::set<int> numbers_set;
    std::copy(numbers.begin(), numbers.end(), std::inserter(numbers_set, numbers_set.begin()));
    // TODO: create a map that maps the numbers to their order in the set using std::transform, std::views::iota (creates a pseudo-container with a range of numbers), std::inserter and std::make_pair<const int&, const int&>
    std::map<int, int> numbers_map;
    auto order = std::views::iota(1); // contains 1, 2, ...; use order.begin()
    std::transform(numbers_set.begin(), numbers_set.end(), order.begin(), std::inserter(numbers_map, numbers_map.begin()), std::make_pair<const int&, const int&>);

    // TODO: print the pairs in the map using std::for_each and a lambda expression (it can take an `auto` parameter; use .first and .second to access the members)
    std::for_each(numbers_map.begin(), numbers_map.end(), [](auto pair) {std::cout << pair.first << ": " << pair.second << std::endl;});
}
