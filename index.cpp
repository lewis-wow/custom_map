#include <string>
#include <set>
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

template <class T>
class Map_m {
    public:
        Map_m<T>() {}
        ~Map_m() {}

        T insert(const string& key, const T& item) {
            if(!keys.insert(key).second) {
                throw runtime_error("Already exists.");  
            }
            keys.insert(key);
            entries.push_back(make_pair(key, item));

            return item;
        }

        void erase(const string& key) {
            if(keys.find(key)) {
                keys.erase(key);
                
                for(auto it = entries.begin(); it != entries.end(); it++) {
                    if(it->first == key) {
                        entries.erase(it);
                        break;
                    }
                }
            }
        }

        class Iterator {
            public:
                using value_type = pair<string, T>;
                using pointer = pair<string, T>*;
                using reference = pair<string, T>&;

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
        set<string> keys;
        vector<pair<string, T>> entries;

};

int main(int argc, char const *argv[]) {

    Map_m<int> mymap;

    mymap.insert("key", 1);
    mymap.insert("another-key", 2);

    auto it = mymap.begin();
    while(it != mymap.end()) {
        cout << it->first << ":" << it->second << endl;
        it++;
    }


    return 0;
}
