#ifndef XML_WRAPPER_WRITER_H_
#define XML_WRAPPER_WRITER_H_
#include <libxml/encoding.h> 
#include <libxml/xmlwriter.h> 
#include <libxml/parser.h> 
#include <libxml/tree.h> 

#include "XMLNode.h"
 
class MemoryWriter {
public:
    MemoryWriter();
    ~MemoryWriter();
    
    xmlTextWriterPtr getWriter();
private:
    xmlBufferPtr buffer_; 
    xmlTextWriterPtr writer_;
};

class XMLDocument {
public:
    XMLDocument(xmlTextWriterPtr writer);
    ~XMLDocument();

    void writeNode(XMLNode& node);
    void writeChildren(XMLNode::MapType &children);
    void writeAttributes(map<string, string> &attr);

private:
    xmlTextWriterPtr writer_;
};

template <class Medium>
class XMLWriter {
public:
    XMLWriter() {
    }
    
    ~XMLWriter();

    void addNode(const XMLNode &n) {
        nodeList.push_back(n);
    }

    void write() {
        XMLDocument doc(medium_.getWriter());
        for ( XMLNode::ListType::iterator it = nodeList.begin();
                it != nodeList.end(); it++ ) {
            doc.writeNode(*it);
        }
    }

private:
    XMLDocument doc_;
    Medium medium_;
    XMLNode::ListType nodeList;
};

#endif  /// XML_WRAPPER_WRITER_H_
