#ifndef XML_READER_H_
#define XML_READER_H_

/*
 * @brief The XMLReader class is responsible for dealing with libxml's api
 *      and constructing the XMLNode's objects representing the xml's nodes
 *
 * @author Filipe N. Felisbino
 *
 * */
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <libxml/parser.h>
#include <libxml/tree.h>

using std::runtime_error;
using std::string;
using std::map;
using std::vector;

class XMLReaderException : public runtime_error {
public:
    XMLReaderException(const string &x) :
        runtime_error(x) {};

};

struct XMLNode {
    typedef vector<XMLNode>::iterator iterator;
    string name; // tag name
    string text;
    map<string, string> attributes;
    map<string, vector<XMLNode> > children;

    XMLNode& operator[](const std::string &name);
};

class XMLReader {
public:
    XMLReader(const string &o);
    ~XMLReader();

    void parse();
    bool findNode(const string&);
    vector<XMLNode>& getNodes() { return nodes; };
private:
    xmlDoc *doc_;

    vector<XMLNode> nodes;
    
    void getAttributes(xmlNode *node, map<string,string>&data);
    void getChildren(xmlNode *node, XMLNode &result);
    void populateNode(xmlNode* node, XMLNode &result);
};

#endif // XML_READER_H_

