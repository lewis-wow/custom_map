#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <cassert>
using namespace std;
 
class CFlightList {
public:
    CFlightList() {};
    CFlightList(const CFlightList & src) {}
    ~CFlightList() {};
    bool Add (const string & a, const string & b) {
        if(a == b) return false;

        CAirport* it = m_List;
        CAirport* last = m_List;

        while(it != NULL) {
            if(it->m_Name == a) {
                for(int i = 0; i < it->m_Nr; i++) {
                    if(it->m_Dest[i]->m_Name == b) return false;
                }
                auto created = new CAirport(b);
                it->m_Dest[it->m_Nr++] = created;
                created->m_Dest[created->m_Nr++] = it;
                return true;
            }

            if(it->m_Name == b) {
                for(int i = 0; i < it->m_Nr; i++) {
                    if(it->m_Dest[i]->m_Name == a) return false;
                }
                auto created = new CAirport(a);
                it->m_Dest[it->m_Nr++] = created;
                created->m_Dest[created->m_Nr++] = it;
                return true;
            }

            it = it->m_Next;
            last = it;
        }

        CAirport* newAirport = new CAirport(a);
        auto created = new CAirport(b);
        newAirport->m_Dest[newAirport->m_Nr++] = created;
        created->m_Dest[created->m_Nr++] = newAirport;

        if(!m_List) m_List = newAirport;    
        else last->m_Next = newAirport;    

        return true;
        
    }
    friend ostream & operator << (ostream & os, const CFlightList & src);
private:
    struct CAirport {
        static const int MAXSIZE = 100;
        CAirport(string Nm_Name) : m_Next(NULL), m_Name(Nm_Name), m_Nr(0) {};
        CAirport * m_Next;
        string m_Name;
        int m_Nr;
        CAirport * m_Dest [MAXSIZE];
    };
    friend class CTester;
    CAirport * m_List = NULL;
};
 
ostream & operator << (ostream & os, const CFlightList & src) {
    for (CFlightList::CAirport * tmp = src.m_List; tmp; tmp = tmp->m_Next) {
        os << tmp->m_Name << "[" << tmp->m_Nr << "]:";
        for (int i=0; i!=tmp->m_Nr; i++) {
            os << tmp->m_Dest[i]->m_Name << "[" << tmp->m_Dest[i]->m_Nr << "]";
            os << ", ";
        }
        os << endl;
    }
    return os;
}

int main(int argc, char const *argv[])
{
    
    CFlightList f0;
 
    assert(f0.Add("Prague", "Berlin") == true);
    assert(f0.Add("Prague", "Berlin") == false);
    assert(f0.Add("Prague", "London") == true);
    assert(f0.Add("London", "Berlin") == true);
    assert(f0.Add("Berlin", "London") == false);
    assert(f0.Add("Berlin", "Berlin") == false);
    assert(f0.Add("New York", "Oslo") == true);
 
    cout << f0 << endl;
    /*
    Prague[2]:Berlin[2], London[2], 
    Berlin[2]:Prague[2], London[2], 
    London[2]:Prague[2], Berlin[2], 
    New York[1]:Oslo[1], 
    Oslo[1]:New York[1],
    */
 
    CFlightList f1 (f0);
 
    assert(f1.Add("Paris", "Wien") == true);
 
    cout << f0 << endl;
    /*
    Prague[2]:Berlin[2], London[2], 
    Berlin[2]:Prague[2], London[2], 
    London[2]:Prague[2], Berlin[2], 
    New York[1]:Oslo[1], 
    Oslo[1]:New York[1],
    */
    cout << f1 << endl;
    /*
    Prague[2]:Berlin[2], London[2], 
    Berlin[2]:Prague[2], London[2], 
    London[2]:Prague[2], Berlin[2], 
    New York[1]:Oslo[1], 
    Oslo[1]:New York[1], 
    Paris[1]:Wien[1], 
    Wien[1]:Paris[1], 
    */
    return 0;
}
