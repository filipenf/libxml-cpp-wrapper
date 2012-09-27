#include "XMLReader.h"
#ifdef DEBUG
#include <iostream>
#define LOG_DEBUG(x) std::cout << x << std::endl;
#else
#define LOG_DEBUG(x)
#endif

/**
 * Begin of XMLNode's implementation
 * */
    
XMLNode XMLNode::NULL_NODE;
XMLNode const XMLNode::END_NODE;

XMLNode& XMLNode::operator[](const string &name) {
    XMLNode::MapType::iterator it = children.find(name); 
    if ( it != children.end() ) {
        return *it->second.begin();
    } else {
        return NULL_NODE;
    }
}

XMLNode::ListType::iterator XMLNode::FirstChild(const std::string &name) {
    return children[name].begin();
 }

XMLNode::ListType::iterator XMLNode::LastChild(const std::string &name) {
    return children[name].end();
}

/**
 * Begin of XMLReader's implementation
 * */
XMLReader::XMLReader(const std::string &xml) : doc_(NULL) {
	doc_ = xmlParseMemory(xml.c_str(), xml.size());
}

XMLReader::~XMLReader() {
    if ( doc_ != NULL ) {
        xmlFreeDoc(doc_);
    }
}

void XMLReader::populateNode(xmlNode* node, XMLNode &result) {
    result.name = string((const char*)node->name);
    LOG_DEBUG("XMLReader::populateNode "<<result.name)
    if ( node->xmlChildrenNode != NULL &&
            node->xmlChildrenNode->type == XML_TEXT_NODE ) {
        result.text = string((char*)
                xmlNodeGetContent(node->xmlChildrenNode));
        LOG_DEBUG(">>Found XML_TEXT_NODE value = "<<result.text)
    }
    getAttributes(node, result.attributes);
    getChildren(node, result);
}

void XMLReader::parse(list<XMLNode> &nodes) {
    LOG_DEBUG("XMLReader::parse")
    xmlNode *current = xmlDocGetRootElement(doc_);
    while ( current != NULL ) {
        LOG_DEBUG("creating node for " << (char*) current->name);
        XMLNode result;
        populateNode(current, result);
        nodes.push_back(result);
        current = current->next;
    }
}

void XMLReader::getChildren(xmlNode* node, XMLNode &result) {
    LOG_DEBUG("XMLReader::getChildren " << node->name)
    if ( node->type != XML_ELEMENT_NODE ) return;
    node = node->children;
    while ( node != NULL ) {
        XMLNode child;
        populateNode(node, child);
        result.children[child.name].push_back(child);
        node = node->next;
    }
}

void XMLReader::getAttributes(xmlNode *node, map<string,string> &data) {
    LOG_DEBUG("XMLReader::getAttributes")
    for(xmlAttrPtr attr = node->properties;
            attr != NULL; attr = attr->next) {
        LOG_DEBUG("Attribute: "<<attr->name<<" = "<<
                xmlNodeGetContent(attr->children));
        data.insert(std::make_pair(string((const char*)attr->name),
                    (const char*)xmlNodeGetContent(attr->children)));
    }
}

