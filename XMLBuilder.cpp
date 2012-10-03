#include "XMLBuilder.h"

using std::string;

XMLMemoryWriter::XMLMemoryWriter() {
    buffer_ = xmlBufferCreate();
    writer_ = xmlNewTextWriterMemory(buffer_, 0);
}

XMLMemoryWriter::~XMLMemoryWriter() {
    xmlBufferFree(buffer_);
    xmlFreeTextWriter(writer_);
}

xmlTextWriterPtr XMLMemoryWriter::getWriter() {
    return writer_;
}

string XMLMemoryWriter::getContent() {
    return string((const char*)buffer_->content);
}

/*************************************************************
 * Begin of XMLDocument's implementation                     * 
 *                                                           * 
 ************************************************************/

XMLDocument::XMLDocument(xmlTextWriterPtr writer) :
    writer_(writer) {
}

XMLDocument::XMLDocument(xmlTextWriterPtr writer, const DTDInfo &info) :
    writer_(writer),
    dtdInfo_(info) {
}

XMLDocument::~XMLDocument() {
    xmlTextWriterEndDocument(writer_);
}

void XMLDocument::init() {
    xmlTextWriterStartDocument(writer_, "1.0", "UTF-8", NULL);
    xmlTextWriterSetIndent(writer_, 1);
    if ( dtdInfo_.name != "" ) {
        xmlTextWriterStartDTD(writer_, 
                BAD_CAST dtdInfo_.name.c_str(),
                BAD_CAST dtdInfo_.id.c_str(), 
                BAD_CAST dtdInfo_.url.c_str());
        xmlTextWriterEndDTD(writer_);
    }
}

void XMLDocument::writeNode(XMLNode& node) {
    xmlTextWriterStartElement(writer_, BAD_CAST node.name.c_str());
    if ( node.attributes.size() > 0 ) {
        writeAttributes(node.attributes);
    }
    if ( node.children.size() > 0 ) {
        writeChildren(node.children);
    } else if ( node.text.length() > 0 ) {
        xmlTextWriterWriteString(writer_, BAD_CAST node.text.c_str());
    }
    xmlTextWriterEndElement(writer_);
}

void XMLDocument::writeChildren(XMLNode::MapType &children) {
    for ( XMLNode::MapType::iterator it = children.begin();
            it != children.end(); it++ ) {
        XMLNode::ListType &list = it->second;
        for ( XMLNode::ListType::iterator it1 = list.begin();
                it1 != list.end(); it1++ ) {
            writeNode(*it1);
        }
    }
}

void XMLDocument::writeAttributes(map<string, string> &attr) {
    for ( map<string, string>::iterator it = attr.begin();
            it != attr.end(); it++ ) {
        xmlTextWriterWriteAttribute(writer_,
                BAD_CAST it->first.c_str(),
                BAD_CAST it->second.c_str());
    }
}



