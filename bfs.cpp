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

class Bfs {
    public:
        Bfs() {};
        ~Bfs() {};

        void addNode(const string& node) {
            /** create new node in map (graph) with set of relations with other nodes */
            graph[node] = set<string>();
        }

        void addEdge(const string& a, const string& b) {
            /** edge from a -> b and b -> a */
            graph[a].insert(b);
            graph[b].insert(a);

            /** if you want edge only from a -> b */
            //graph[a].insert(b);
        }

        list<string> bfs(const string& from, const string& to) {
            map<string, bool> visited; // if node was already visited
            map<string, string> parent; // store child node parent - for find the shortest path between two nodes
            map<string, int> level; // for distance between from and any other node in the graph

            queue<string> q; // bfs uses queue for every node to be processed
            // naopak dfs pouziva stack, ktery ovsem netvori programator, ale rekurze

            q.push(from); // do fronty posleme na zpracovani nas startovaci node

            // nastavime zakladni veci pro startovaci uzel
            visited[from] = true;
            parent[from] = ""; // toto je nepovinne
            level[from] = 0;

            while(!q.empty()) { // dokud jsou ve fronte nejake nody (na zacatku je tam pouze start uzel)

                auto curr = q.front(); q.pop(); // node, ktery v tuhle chvily zpracovavame

                if(curr == to) { // pokud je tento node roven cily, nasli jsme ho a koncime
                    auto res = list<string>(); 

                    // jedeme pozpatku!
                    res.push_front(curr); // do listu pushujeme zepredu (pozpatku), protoze jdeme pomoci parentu vzdy o level vis
                    while(curr != from) { // dokud nejsem opet zpet na startu, vracime
                        curr = parent[curr]; // dostaneme parenta a pushneme ho do listu
                        res.push_front(curr);
                    }

                    return res; // list res tvori list nodu, ktery reprezentuji nejkratsi cestu mezi bodem from a bodem to
                }

                // pokud jsme jeste nedosli do cile
                for(const auto& item: graph[curr]) {

                    // pokud jsme node jeste nenavstivily, pokud ano, preskocime ho, uz je zpracovany
                    if(visited.find(item) == visited.end()) {
                        visited[item] = true;
                        parent[item] = curr; // parent vsech nodu, ktere jsou spojeny s curr nodem, je samozrejme curr node -> jdeme ze shora dolu
                        level[item] = level[curr] + 1; // level je vzdy o 1 vetsi nez co byl

                        q.push(item); // posleme node na zpracovani (jeste preci nebyl zpracovan, zpracovan byl pouze jeho parent)
                    }
                }

            }

            return list<string>(); // pokud jsme nenasli cil vratime prazdny list
        }

    private:
        /** whole graph representation */
        map<string, set<string>> graph;
};

int main(int argc, char const *argv[]) {
    // testy

    Bfs bfs;
    bfs.addNode("a");
    bfs.addNode("b");
    bfs.addNode("c");
    bfs.addNode("d");
    bfs.addNode("e");

    bfs.addEdge("a", "b");
    bfs.addEdge("a", "d");
    bfs.addEdge("b", "c");
    bfs.addEdge("c", "d");
    bfs.addEdge("d", "e");

    assert(!(bfs.bfs("a", "e") == list<string>{"a","b","c","d","e"})); // neni nejkratsi
    assert((bfs.bfs("a", "e") == list<string>{"a","d","e"})); // je nejkratsi
    assert((bfs.bfs("a", "f") == list<string>())); // f neni v grafu

    bfs.addNode("f");

    bfs.addEdge("b", "d");
    bfs.addEdge("c", "f");
    bfs.addEdge("a", "f");

    assert((bfs.bfs("b", "f") == list<string>{"b","a","f"})); // nejkratsi cesta

    return 0;
}
