#include "XMLBuilder.h"

using std::string;

XMLMemoryWriter::XMLMemoryWriter() {
    buffer_ = xmlBufferCreate();
    writer_ = xmlNewTextWriterMemory(buffer_, 0);
}

XMLMemoryWriter::~XMLMemoryWriter() {
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
    writer_(writer),
    init_(false) {
}

XMLDocument::XMLDocument(xmlTextWriterPtr writer, const DTDInfo &info) :
    writer_(writer),
    dtdInfo_(info),
    init_(false) {
}

XMLDocument::~XMLDocument() {
    if ( init_ ) {
        end();
    }
}

void XMLDocument::init() {
    init_ = true;
    if ( xmlTextWriterStartDocument(writer_, "1.0", "UTF-8", NULL) < 0 )
        throw XMLError("Error starting the document.");
    if (xmlTextWriterSetIndent(writer_, 2) < 0 )
        throw XMLError("Error set document indentation");
    if ( dtdInfo_.name != "" ) {
        if (xmlTextWriterStartDTD(writer_, 
                    BAD_CAST dtdInfo_.name.c_str(),
                    BAD_CAST dtdInfo_.id.c_str(), 
                    BAD_CAST dtdInfo_.url.c_str()) < 0)
            throw XMLError("Error setting DTD information");
        xmlTextWriterEndDTD(writer_);
    }
}

void XMLDocument::end() {
    xmlTextWriterEndDocument(writer_);
}

void XMLDocument::writeNode(XMLNode& node) {
    if (xmlTextWriterStartElement(writer_, BAD_CAST node.name.c_str()) < 0)
        throw XMLError("Error starting element " + node.name);
    if ( node.attributes.size() > 0 ) {
        writeAttributes(node.attributes);
    }
    if ( node.children.size() > 0 ) {
        writeChildren(node.children);
    } else if ( node.text.length() > 0 ) {
        if (xmlTextWriterWriteString(writer_, BAD_CAST node.text.c_str()) < 0)
            throw XMLError("Error seting node's value "+node.text);

    }
    if (xmlTextWriterEndElement(writer_) < 0)
        throw XMLError("Error closing element "+node.name);
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



