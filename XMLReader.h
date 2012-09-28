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
#include <list>
#include <map>
#include <stdexcept>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "XMLNode.h"

using std::runtime_error;
using std::string;
using std::map;
using std::list;

class XMLReaderException : public runtime_error {
public:
    XMLReaderException(const string &x) :
        runtime_error(x) {};

};

struct XMLFileParser {
    xmlDocPtr parse(const std::string &);
};

struct XMLMemoryParser {
    xmlDocPtr parse(const std::string &);
};

void getAttributes(xmlNode *node, map<string,string>&data);
void getChildren(xmlNode *node, XMLNode &result);
void populateNode(xmlNode* node, XMLNode &result);

template<class Parser>
class XMLReader {
public:
    XMLReader(const string &o) : parser_(), doc_(NULL) {
        doc_ = parser_.parse(o);

    };
    ~XMLReader() {
        if ( doc_ != NULL ) {
            xmlFreeDoc(doc_);
        }
    };

    void parse(list<XMLNode> &nodes) {
        xmlNode *current = xmlDocGetRootElement(doc_);
        while ( current != NULL ) {
            XMLNode result;
            populateNode(current, result);
            nodes.push_back(result);
            current = current->next;
        }
    };

    bool findNode(const string&);
private:
    Parser parser_;
    xmlDocPtr doc_;

};

#endif // XML_READER_H_

