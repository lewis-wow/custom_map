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
            map<string, int> level;
            map<string, string> parent;
            queue<string> q;

            q.push(from);
            visited.emplace(from, true);

            while(!q.empty()) {
                auto curr = q.front(); q.pop();

                if(curr == to) {
                    list<string> res;
                    res.push_front(curr);

                    while(curr != from) {
                        curr = parent[curr];
                        res.push_front(curr);
                    }

                    return res;
                }

                for(const auto& pcpb: pcpbs[curr]) {
                    if(visited.find(pcpb) == visited.end()) {
                        level[pcpb] = level[curr] + 1;
                        parent[pcpb] = curr;
                        visited[pcpb] = true;
                        q.push(pcpb);
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
    p.Add("b", "c");
    p.Add("b", "d");
    p.Add("b", "e");
    p.Add("e", "f");

    auto res = p.Short("a", "f");
    
    for(const auto& a : res) {
        cout << a << endl;
    }

    //assert((res == set<string>{"a","b","e","f"}));
    return 0;
}
