#ifndef XML_WRAPPER_WRITER_H_
#define XML_WRAPPER_WRITER_H_

#include "XMLNode.h"

#include <string>
#include <libxml/encoding.h> 
#include <libxml/xmlwriter.h> 
#include <libxml/parser.h> 
#include <libxml/tree.h> 

#ifndef LOG_DEBUG
#include <iostream>
#define LOG_DEBUG(X) std::cout << X << std::endl;
#endif

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
    void end();
    void writeNode(XMLNode& node);
    void writeChildren(XMLNode::MapType &children);
    void writeAttributes(map<std::string, std::string> &attr);

private:
    xmlTextWriterPtr writer_;
    DTDInfo dtdInfo_;
    bool init_;
};

template <class Writer>
class XMLBuilder {
public:
    XMLBuilder(Writer &m) : writer_(m) {
    }
    
    XMLBuilder(Writer &m, DTDInfo& dtdInfo) :
        writer_(m),
        dtdInfo_(dtdInfo) {
    }
    
    ~XMLBuilder() {};

    void addNode(const XMLNode &n) {
        nodeList.push_back(n);
    }

    XMLNode& addNode(const std::string &name) {
        nodeList.push_back(XMLNode());
        XMLNode &back = nodeList.back();
        back.name = name;
        return back;
    }

    void write() {
        LOG_DEBUG("XMLBuilder::write");
        XMLDocument doc(writer_.getWriter(), dtdInfo_);
        doc.init();
        for ( XMLNode::ListType::iterator it = nodeList.begin();
                it != nodeList.end(); it++ ) {
            doc.writeNode(*it);
        }
        doc.end();
    }

private:
    Writer &writer_;
    DTDInfo dtdInfo_;
    XMLNode::ListType nodeList;
};

#endif  /// XML_WRAPPER_WRITER_H_
