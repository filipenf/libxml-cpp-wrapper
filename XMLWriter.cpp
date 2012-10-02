#include "XMLWriter.h"

MemoryWriter::MemoryWriter() {
    buffer_ = xmlBufferCreate();
    writer_ = xmlNewTextWriterMemory(buffer_, 0);
}

MemoryWriter::~MemoryWriter() {
    xmlBufferFree(buffer_);
}

xmlTextWriterPtr MemoryWriter::getWriter() {
    return writer_;
}

XMLDocument::XMLDocument(xmlTextWriterPtr writer) :
    writer_(writer) {
    xmlTextWriterStartDocument(writer_, "1.0", "UTF-8", NULL);
    xmlTextWriterSetIndent(writer_, 1);
}

XMLDocument::~XMLDocument() {
    xmlTextWriterEndDocument(writer_);
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

