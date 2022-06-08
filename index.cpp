#include <string>
#include <set>
#include <vector>
#include <memory>

using namespace std;

template <typename T>
class Map {
    public:
        Map() {}
        ~Map() {}

        Map& operator=(const Map& map) {
            this->entries = map.entries;
            this->keys = map.keys;
            this->values = map.values;

            return *this;
        }

        bool operator==(const Map& other) {

        }

        T operator[](const string& key) const {

        }

        T& operator[](const string& key) {

        }

        bool in(const string& key) {
            return keys.find(key) != keys.end();
        }

        bool isEmpty() {
            return entries.empty();
        }

        class Iterator {
            public:
                using iter_cat = forward_iterator_tag;
                using diff = ptrdiff_t;
                using value_type = T;
                using pointer = T*;
                using reference = T&;

                Iterator(pointer ptr): ptr(ptr) {};
                ~Iterator() {};

                reference operator*() const { 
                    return *ptr; 
                }

                pointer operator->() { 
                    return ptr; 
                }

                Iterator& operator++() {
                    ptr++;
                    return *this;
                } 

                Iterator operator++(int) {
                    Iterator tmp = ptr;
                    ++(*this);
                    return tmp;
                }

                Iterator operator--() {
                    ptr--;
                    return *this;
                }

                Iterator operator--(int) {
                    Iterator tmp = ptr;
                    --(*this);
                    return tmp;
                }

                friend bool operator==(const Iterator& a, const Iterator& b) {
                    return a.ptr == b.ptr;
                }

                friend bool operator!=(const Iterator& a, const Iterator& b) {
                    return a.ptr != b.ptr;
                }

            private:
                pointer ptr;
        };  

        Iterator begin() {
            return Iterator(&entries[0]);
        }

        Iterator end() {
            return Iterator(&entries[entries.size()]);
        }

    protected:
        set<pair<string, T>> entries;
        set<string> keys;
        vector<T> values;

};

int main(int argc, char const *argv[]) {
    
    return 0;
}
