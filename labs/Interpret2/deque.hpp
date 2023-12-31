#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <memory>
#include <vector>

template<typename T>
class Deque {
public:
	class iterator;

	Deque(std::size_t chunk_size = 100) : chunk_size_(chunk_size), size_(0) {}
	
	// TODO: implement operator[], begin(), end(), push_back()
    const T& operator[](size_t i) const{
        std::size_t chunk_index = i / chunk_size_;
        std::size_t item_index = i % chunk_size_;
        return  chunks_[chunk_index][item_index];
    }
    T& operator[](size_t i){
        std::size_t chunk_index = i / chunk_size_;
        std::size_t item_index = i % chunk_size_;
        return  chunks_[chunk_index][item_index];
    }
    iterator begin(){
        return iterator(*this,0);
    }
    iterator end(){
        return iterator(*this,size_);
    }
    void push_back(const T& value) {
        std::size_t chunk_index = size_ / chunk_size_;
        std::size_t item_index = size_ % chunk_size_;

        ++size_;
        if (chunk_index >= chunks_.size()) {
            chunks_.push_back(std::make_unique<T[]>(chunk_size_));
        }

        chunks_[chunk_index][item_index] = value;
    }


private:
	std::size_t chunk_size_;
	std::size_t size_;
	std::vector<std::unique_ptr<T[]>> chunks_;
};

template <typename T>
class Deque<T>::iterator {
public:
	iterator(Deque<T>& deque, std::size_t i) : deque_(deque), i_(i) {}

	// TODO: methods of a typical iterator (operator*, operator++, operator==, operator!=)
    T& operator*() const {
        return deque_[i_];
    }
    bool operator==(const iterator& other) const {
        return i_ == other.i_;
    }

    auto operator<=>(const iterator& other) const {
        return i_ <=> other.i_;
    }
    iterator& operator++() {        // pre-increment
        ++i_;
        return *this;
    }
    iterator operator++(int) { // post-increment (int is a dummy parameter)
        iterator tmp = *this;
        operator++();
        return tmp;
    }

private:
	Deque<T>& deque_;
	std::size_t i_;
};

#endif // DEQUE_HPP
