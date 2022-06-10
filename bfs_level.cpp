#include <string>
#include <set>
#include <vector>
#include <memory>
#include <iostream>
#include <functional>
#include <map>
#include <queue>
#include <cassert>
#include <list>

using namespace std;

//https://fit-wiki.cz/%C5%A1kola/p%C5%99edm%C4%9Bty/bi-pa2/pa2_test_2016-05-23_09-00

class PCPB {
    public:
        PCPB() {}
        ~PCPB() {}

        bool Add(const string& x, const string& y) {
            pcpbs[x].insert(y);
            pcpbs[y].insert(x);

            return true;
        }

        list<string> Short(const string& from, const string& to) {
            map<string, bool> visited;
            map<string, string> parent;
            map<string, int> level;

            queue<string> q;
            q.push(from);
            visited[from] = true;
            parent[from] = "";
            level[from] = 0;

            while(!q.empty()) {

                auto curr = q.front(); q.pop();

                if(curr == to) {
                    auto res = list<string>();

                    res.push_front(curr);
                    while(curr != from) {
                        curr = parent[curr];
                        res.push_front(curr);
                    }

                    return res;
                }

                for(const auto& item: pcpbs[curr]) {
                    if(visited.find(item) == visited.end()) {
                        visited[item] = true;
                        parent[item] = curr;
                        level[item] = level[curr] + 1;

                        q.push(item);
                    }
                }

            }

            return list<string>();
        }
        
    private:    
        map<string, set<string>> pcpbs;
};

int main(int argc, char const *argv[]) {

    PCPB p;

    p.Add("a", "b");
    p.Add("a", "d");
    p.Add("b", "c");
    p.Add("c", "d");
    p.Add("d", "e");

    auto res = p.Short("a", "e");
    
    for(const auto& a : res) {
        cout << a << endl;
    }

    //assert((res == set<string>{"a","b","e","f"}));
    return 0;
}
