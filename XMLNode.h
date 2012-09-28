#include <string>
#include <map>
#include <list>

using namespace std;

class XMLNode {
public:
    static XMLNode NULL_NODE;
    static const XMLNode END_NODE;

//    typedef vector<XMLNode>::iterator iterator;
    typedef list<XMLNode> ListType;
    typedef map<string, ListType> MapType;

    string name; // tag name
    string text; // tag value ( if is a text tag )
    map<string, string> attributes;
    MapType children;

    XMLNode& operator[](const std::string &name);
    ListType::iterator firstChild(const std::string &name);
    ListType::iterator lastChild(const std::string &name);
    bool hasChild(const std::string &name);
};


