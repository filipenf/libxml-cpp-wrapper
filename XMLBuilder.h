#ifndef XML_WRAPPER_WRITER_H_
#define XML_WRAPPER_WRITER_H_

#include "XMLNode.h"

#include <string>
#include <libxml/encoding.h> 
#include <libxml/xmlwriter.h> 
#include <libxml/parser.h> 
#include <libxml/tree.h> 

class XMLMemoryWriter {
public:
    XMLMemoryWriter();
    ~XMLMemoryWriter();
    
    xmlTextWriterPtr getWriter();
    std::string getContent();
private:
    xmlBufferPtr buffer_; 
    xmlTextWriterPtr writer_;
};

struct DTDInfo {
    std::string name;
    std::string id;
    std::string url;
};

class XMLDocument {
public:
    XMLDocument(xmlTextWriterPtr writer);
    XMLDocument(xmlTextWriterPtr writer, const DTDInfo &info);
    ~XMLDocument();

    void init();
    void writeNode(XMLNode& node);
    void writeChildren(XMLNode::MapType &children);
    void writeAttributes(map<std::string, std::string> &attr);

private:
    xmlTextWriterPtr writer_;
    DTDInfo dtdInfo_;
};

template <class Writer>
class XMLBuilder {
public:
    XMLBuilder(Writer &m) : writer_(m) {
    }
    
    ~XMLBuilder();

    void addNode(const XMLNode &n) {
        nodeList.push_back(n);
    }

    void write() {
        XMLDocument doc(writer_.getWriter());
        for ( XMLNode::ListType::iterator it = nodeList.begin();
                it != nodeList.end(); it++ ) {
            doc.writeNode(*it);
        }
    }

private:
    XMLDocument doc_;
    Writer &writer_;
    XMLNode::ListType nodeList;
};

#endif  /// XML_WRAPPER_WRITER_H_
