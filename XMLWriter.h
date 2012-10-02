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

void startDocument(xmlTextWriterPtr writer);
void writeNode(xmlTextWriterPtr writer, XMLNode& node);
void writeChildren(xmlTextWriterPtr writer, XMLNode::MapType &children);
void writeAttributes(xmlTextWriterPtr writer, map<string, string> &attr);

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
        startDocument(medium_.getWriter());
        for ( XMLNode::ListType::iterator it = nodeList.begin();
                it != nodeList.end(); it++ ) {
            writeNode(medium_.getWriter(), *it);
        }
    }

private:
    Medium medium_;
    XMLNode::ListType nodeList;
};

#endif  /// XML_WRAPPER_WRITER_H_
