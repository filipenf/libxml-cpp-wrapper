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

void startDocument(xmlTextWriterPtr writer) {
    xmlTextWriterStartDocument(writer, "1.0", "UTF-8", NULL);
    xmlTextWriterSetIndent(writer, 1);
}

void writeNode(xmlTextWriterPtr writer, XMLNode& node) {
    xmlTextWriterStartElement(writer, BAD_CAST node.name.c_str());
    if ( node.attributes.size() > 0 ) {
        writeAttributes(writer, node.attributes);
    }
    if ( node.children.size() > 0 ) {
        writeChildren(writer, node.children);
    } else if ( node.text.length() > 0 ) {
        xmlTextWriterWriteString(writer, BAD_CAST node.text.c_str());
    }
    xmlTextWriterEndElement(writer);
}

void writeChildren(xmlTextWriterPtr writer, XMLNode::MapType &children) {
    for ( XMLNode::MapType::iterator it = children.begin();
            it != children.end(); it++ ) {
        XMLNode::ListType &list = it->second;
        for ( XMLNode::ListType::iterator it1 = list.begin();
                it1 != list.end(); it1++ ) {
            writeNode(writer, *it1);
        }
    }
}

void writeAttributes(xmlTextWriterPtr writer,
        map<string, string> &attr) {
    for ( map<string, string>::iterator it = attr.begin();
            it != attr.end(); it++ ) {
        xmlTextWriterWriteAttribute(writer,
                BAD_CAST it->first.c_str(),
                BAD_CAST it->second.c_str());
    }
}

