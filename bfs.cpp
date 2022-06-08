#include <string>
#include <set>
#include <vector>
#include <memory>
#include <iostream>
#include <functional>
#include <map>
#include <queue>
#include <cassert>

using namespace std;

class Airports {
    public:
        Airports() {};
        ~Airports() {};

        void addAirport(const string& node) {
            airports.insert(make_pair(
                node, 
                set<string>()
            ));
        }

        void addEdge(const string& origin, const string& dest) {
            airports.at(origin).insert(dest);
            airports.at(dest).insert(origin);
        }

        set<string> bfs(const string& start, const string& search) {
            auto q = queue<string>();
            auto visited = set<string>();
            q.push(start);

            while(q.size() > 0) {
                auto curr = q.front();
                q.pop();

                auto dests = airports.at(curr);

                for(auto it = dests.begin(); it != dests.end(); it++) {
                    auto dest = *it;

                    if(dest == search) {
                        return visited;
                    }

                    if(visited.find(dest) == visited.end()) {
                        visited.insert(dest);
                        q.push(dest);
                    }
                }

            }

            return set<string>();
        }

    private:
        map<string, set<string>> airports;
};

int main(int argc, char const *argv[]) {

    vector<string> airports = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k" };
    map<string, string> relations = {
        {"a", "b"},
        {"b", "c"},
        {"c", "d"},
        {"d", "e"}
    };

    Airports a;

    for(const auto& item: airports) {
        a.addAirport(item);
    }

    for(const auto& item: relations) {
        a.addEdge(item.first, item.second);
    }

    assert((a.bfs("a", "e") == set<string>{"a","b","c","d"}));

    return 0;
}
