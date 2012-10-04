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
    LOG_DEBUG("XMLDocument::~");
    if ( init_ ) {
        end();
    }
}

void XMLDocument::init() {
    LOG_DEBUG("XMLDocument::init");
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
        if (xmlTextWriterEndDTD(writer_) < 0 )
            throw XMLError("Error setting DTD information");
    }
}

void XMLDocument::end() {
    if ( xmlTextWriterEndDocument(writer_) < 0 )
        throw XMLError("Error trying to close the document");
}

void XMLDocument::writeNode(XMLNode& node) {
        LOG_DEBUG("XMLDocument::writeNode - node="+node.name);
    if (xmlTextWriterStartElement(writer_, BAD_CAST node.name.c_str()) < 0)
        throw XMLError("Error starting element " + node.name);
    if ( node.attributes.size() > 0 ) {
        writeAttributes(node.attributes);
    }
    if ( node.children.size() > 0 ) {
        writeChildren(node.children);
    } else if ( node.text.length() > 0 ) {
        LOG_DEBUG("Writing node's text " + node.text);
        if (xmlTextWriterWriteString(writer_, BAD_CAST node.text.c_str()) < 0)
            throw XMLError("Error seting node's value "+node.text);

    }
    if (xmlTextWriterEndElement(writer_) < 0)
        throw XMLError("Error closing element "+node.name);
}

void XMLDocument::writeChildren(XMLNode::MapType &children) {
    LOG_DEBUG("XMLDocument::writeChildren");
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
    LOG_DEBUG("XMLDocument::writeAttributes");
    for ( map<string, string>::iterator it = attr.begin();
            it != attr.end(); it++ ) {
        if ( xmlTextWriterWriteAttribute(writer_,
                BAD_CAST it->first.c_str(),
                BAD_CAST it->second.c_str()) < 0)
            throw XMLError("Error adding attribute: " + it->first);
    }
}



