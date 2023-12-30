#include <map>
#include <set>
#include <array>
#include <iostream>
#include <utility>

/*
    - TODO: define a struct `Person` with the following members:
        - `name` of type `std::string`
        - `surname` of type `std::string`
        - `age` of type `int`
        - `height` of type `double`
        - `weight` of type `double`
    
    - TODO: define a friend class `operator<<` for `Person` that prints the person's data in a json-like format (see the example below)
        its signature should be `std::ostream& operator<<(std::ostream&, const Person&)`

        ```json
        {
            "name": "John",
            "surname": "Doe",
            "age": 42,
            "height": 1.8,
            "weight": 80.0
        }
        ```

    - TODO: define a "golden pages" comparator `GoldenPagesCompare` for `Person` that compares the persons by their surname, then by their name
        its signature should be `struct GoldenPagesCompare{ bool operator()(const Person&, const Person&) const; };` - it is a functor
    
    - TODO: finish the implementation of `GoldenPages` class

    - TODO: define a "school register" comparator `SchoolRegisterCompare` for `Person` that compares the persons by their age, then their surname and then by their name
        its signature should be `struct SchoolRegisterCompare { bool operator()(const Person&, const Person&) const; };` - it is a functor

    - TODO: finish the implementation of `SchoolRegister` class

*/

struct Person {
    Person() = default;
    Person(std::string name, std::string surname) : name(std::move(name)), surname(std::move(surname)) {}  // TODO
    Person(std::string name, std::string surname, int age) : name(std::move(name)), surname(std::move(surname)), age(age) {} // TODO
    Person(std::string name, std::string surname, int age, double height, double weight) :
    name(std::move(name)), surname(std::move(surname)), age(age), height(height), weight(weight) {} // TODO
    // TODO
    std::string  name;
    std::string surname;
    int age;
    double height;
    double weight;

    // declare the operator<< as a friend (just write `friend <signature>;`)
    friend std::ostream& operator<<(std::ostream&, const Person&) ;
};

std::ostream& operator<<(std::ostream& out, const Person& person) {
    // TODO
    out << "Person: {" << std::endl;
    out << "    name: " << person.name << std::endl;
    out << "    surname: " << person.surname << std::endl;
    out << "    age: " << person.age << std::endl;
    out << "    height: " << person.height << std::endl;
    out << "    weight: " << person.weight << std::endl;
    out << "}" << std::endl;


    return out;
}

struct GoldenPagesCompare {
    bool operator()(const Person& a, const Person& b) const {
        // TODO  TODO: define a "golden pages" comparator `GoldenPagesCompare` for `Person` that compares the persons by their surname, then by their name
        //        its signature should be `struct GoldenPagesCompare{ bool operator()(const Person&, const Person&) const; };` - it is a functor

        if(a.surname < b.surname) {
            return true;
        } else if(a.surname == b.surname) {
            return a.name < b.name;
        } else {
            return false;
        }
    }
};

class GoldenPages {
public:
    // constructor defined by the compiler, we could write it as:
    GoldenPages() = default;

    // We receive the strings by value
    //  (it is simpler and not that much less efficient than creating 4 overloads of the function for
    //    each combination of lvalue/rvalue for name and surname)
    // - if we receive the strings by value, the data are copied into the parameters and then moved into the new Person
    // - if we receive the strings using std::move, the data are moved into the parameters and then moved again into the new Person
    // ^ this is basically almost the same as implementing the 4 different overloads of the function
    void add( std::string name, std::string surname, int age, double height, double weight) {
        // TODO: add a person to the golden pages
        //   how do we avoid copying the strings?

        persons_.emplace(std::move(name), std::move(surname), age, height, weight);
    }

    void print() const {
        // TODO: print the persons in the golden pages (using the operator<<)
        for(auto&& person : persons_) {
            std::cout << person << std::endl;
        }
    }

    void lookup(const std::string& surname, const std::string& name) const {
        // TODO: print the persons with the given surname and name
        //   there can be multiple persons with the same name and surname
        //   hint: use .equal_range with a fictional Person with the given name and surname
        auto [beg, end] = persons_.equal_range({name, surname});
        for(auto it = beg; it != end; ++it) {
            std::cout << *it << std::endl;
        }
    }

private:
    std::multiset<Person, GoldenPagesCompare> persons_;
};

struct SchoolRegisterCompare {
    bool operator()(const Person& a, const Person& b) const {
        // TODO
        if(a.age < b.age) {
            return true;
        } else if(a.age == b.age) {
            if(a.surname < b.surname) {
                return true;
            } else if(a.surname == b.surname) {
                return a.name < b.name;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
};

// explicit values for the enum class so that we can use them as indices in an array
enum class Subject {
    MATH = 0,
    ENGLISH = 1,
    HISTORY = 2,
    SCIENCE = 3,
    ART = 4,
    MUSIC = 5
};

class SchoolRegister {
    constexpr static std::array subject_names = {
        "MATH",
        "ENGLISH",
        "HISTORY",
        "SCIENCE",
        "ART",
        "MUSIC"
    };
public:
    // `using` creates an alias for a type
    using Grades = std::multimap<Subject, int>;

    void add(std::string name, std::string surname, int age, double height, double weight) {
        // TODO: add a person to the school register
        persons_.emplace(Person{std::move(name), std::move(surname), age, height, weight}, Grades{});
    }

    void print() const {
        // TODO: print the persons in the school register (using the operator<<)
        for(auto&& person : persons_) {
            std::cout << person.first << std::endl;
        }
    }
    
    void lookup(const std::string& surname, const std::string& name, int age) const {
        /*
            TODO: print the person with the given surname, name and age (if there is any)
                and then their grades indented by 4 spaces like this:

                ```
                "Person": {
                    "name": "John",
                    "surname": "Doe",
                    "age": 42,
                    "height": 1.8,
                    "weight": 80.0
                }
                "Grades": {
                    "MATH": 1,
                    "ENGLISH": 2,
                    "HISTORY": 3,
                    "SCIENCE": 4,
                    "ART": 5,
                    "MUSIC": 6
                }
        */



        // this syntax allows us to create an variable that is only visible in the if statement (in both branches)
        if (auto it = persons_.find({name, surname, age}); it != persons_.end()) {
            // TODO: print the person and their grades
            std::cout << it->first << std::endl;
            std::cout << "Grades: {" << std::endl;
            for(auto&& grade : it->second) {
                std::cout << "    " << subject_names[static_cast<int>(grade.first)] << ": " << grade.second << std::endl;
            }
            std::cout << "}" << std::endl;
        } else {
            std::cout << "No such person" << std::endl;
        }

    }

    void add_grade(const std::string& surname, const std::string& name, int age, Subject subject, int grade) {
        // TODO: add a grade to the person with the given surname, name and age
        persons_.find({name, surname, age})->second.emplace(subject, grade);
    }

private:
    std::map<Person, Grades, SchoolRegisterCompare> persons_;
};

void test_golden_pages() {
    GoldenPages gp;

    gp.add("John", "Doe", 42, 1.8, 80.0);
    gp.add("Jane", "Doe", 42, 1.6, 60.0);
    gp.add("John", "Smith", 42, 1.8, 80.0);
    gp.add("Jane", "Smith", 42, 1.6, 60.0);
    gp.add("John", "Doe", 18, 1.7, 70.0);

    gp.print();

    std::cout << "Looking up John Smith" << std::endl;
    gp.lookup("Smith", "John");

    std::cout << "Looking up John Doe" << std::endl;
    gp.lookup("Doe", "John");
}

void test_school_register() {
    SchoolRegister sr;

    sr.add("John", "Doe", 42, 1.8, 80.0);
    sr.add("Jane", "Doe", 42, 1.6, 60.0);
    sr.add("John", "Smith", 42, 1.8, 80.0);
    sr.add("Jane", "Smith", 42, 1.6, 60.0);
    sr.add("John", "Doe", 18, 1.7, 70.0);
    sr.add("Bob", "The Builder", 18, 1.7, 70.0);
    sr.add("Jack", "The Ripper", 18, 1.7, 70.0);
    sr.add("User", "Name", 18, 1.7, 70.0);
    sr.add("Fatal", "Error", 18, 1.7, 70.0);
    sr.add("Robert'); DROP TABLE Students;--", "Smith", 0x12, 0x1.b333P0, 0x1.18P6);

    // let's ignore all the string copying for now (in each call, the compiler creates a std::string)

    sr.add_grade("Doe", "John", 42, Subject::MATH, 1);
    sr.add_grade("Doe", "John", 42, Subject::ENGLISH, 2);
    sr.add_grade("Doe", "John", 42, Subject::HISTORY, 3);

    sr.add_grade("Doe", "Jane", 42, Subject::MATH, 5);
    sr.add_grade("Doe", "Jane", 42, Subject::ENGLISH, 6);
    sr.add_grade("Doe", "Jane", 42, Subject::HISTORY, 7);
    sr.add_grade("Doe", "Jane", 42, Subject::SCIENCE, 8);
    sr.add_grade("Doe", "Jane", 42, Subject::SCIENCE, 8);

    sr.add_grade("Smith", "John", 42, Subject::MATH, 9);
    sr.add_grade("Smith", "John", 42, Subject::ENGLISH, 10);
    sr.add_grade("Smith", "John", 42, Subject::HISTORY, 11);
    sr.add_grade("Smith", "John", 42, Subject::SCIENCE, 12);

    sr.add_grade("Smith", "Jane", 42, Subject::MATH, 13);
    sr.add_grade("Smith", "Jane", 42, Subject::MATH, 31);
    sr.add_grade("Smith", "Jane", 42, Subject::ENGLISH, 14);
    sr.add_grade("Smith", "Jane", 42, Subject::HISTORY, 15);
    sr.add_grade("Smith", "Jane", 42, Subject::SCIENCE, 16);

    sr.add_grade("Doe", "John", 18, Subject::MATH, 17);
    sr.add_grade("Doe", "John", 18, Subject::ENGLISH, 18);
    sr.add_grade("Doe", "John", 18, Subject::ENGLISH, 81);
    sr.add_grade("Doe", "John", 18, Subject::HISTORY, 19);
    sr.add_grade("Doe", "John", 18, Subject::SCIENCE, 20);

    sr.add_grade("The Builder", "Bob", 18, Subject::MATH, 21);
    sr.add_grade("The Builder", "Bob", 18, Subject::ENGLISH, 22);
    sr.add_grade("The Builder", "Bob", 18, Subject::HISTORY, 23);
    sr.add_grade("The Builder", "Bob", 18, Subject::SCIENCE, 24);
    
    sr.add_grade("The Ripper", "Jack", 18, Subject::MATH, 25);
    sr.add_grade("The Ripper", "Jack", 18, Subject::ENGLISH, 26);
    sr.add_grade("The Ripper", "Jack", 18, Subject::HISTORY, 27);

    sr.add_grade("Name", "User", 18, Subject::MATH, 28);
    sr.add_grade("Name", "User", 18, Subject::ENGLISH, 29);
    sr.add_grade("Name", "User", 18, Subject::HISTORY, 30);

    sr.add_grade("Error", "Fatal", 18, Subject::MATH, 31);
    sr.add_grade("Error", "Fatal", 18, Subject::ENGLISH, 32);
    sr.add_grade("Error", "Fatal", 18, Subject::HISTORY, 33);

    sr.print();

    std::cout << "Looking up John Smith" << std::endl;
    sr.lookup("Smith", "John", 42);

    std::cout << "Looking up John Doe" << std::endl;
    sr.lookup("Doe", "John", 18);
}

int main(int argc, char** argv) {
    if (argc > 1) {
        std::cerr << "Usage: " << argv[0] << std::endl;
        return 1;
    }

    test_golden_pages();
    test_school_register();
}
