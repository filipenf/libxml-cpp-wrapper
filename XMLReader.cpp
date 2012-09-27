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

bool XMLNode::hasChild(const string &name) {
    XMLNode::MapType::iterator it = children.find(name); 
    return it != children.end();
}

XMLNode::ListType::iterator XMLNode::firstChild(const std::string &name) {
    return children[name].begin();
 }

XMLNode::ListType::iterator XMLNode::lastChild(const std::string &name) {
    return children[name].end();
}

/**
 * Begin of XMLMemoryParser's implementation
 * */
xmlDocPtr XMLMemoryParser::parse(const std::string &xml) {
    return xmlParseMemory(xml.c_str(), xml.size());
}

/**
 * Begin of XMLFileParser's implementation
 * */
xmlDocPtr XMLFileParser::parse(const std::string &file) {
    return xmlParseFile(file.c_str());
}

/**
 * Begin of XMLReader's implementation
 * */
void populateNode(xmlNode* node, XMLNode &result) {
    result.name = string((const char*)node->name);
    if ( node->xmlChildrenNode != NULL &&
            node->xmlChildrenNode->type == XML_TEXT_NODE ) {
        result.text = string((char*)
                xmlNodeGetContent(node->xmlChildrenNode));
    }
    getAttributes(node, result.attributes);
    getChildren(node, result);
}

void getChildren(xmlNode* node, XMLNode &result) {
    if ( node->type != XML_ELEMENT_NODE ) return;
    node = node->children;
    while ( node != NULL ) {
        XMLNode child;
        populateNode(node, child);
        result.children[child.name].push_back(child);
        node = node->next;
    }
}

void getAttributes(xmlNode *node, map<string,string> &data) {
    for(xmlAttrPtr attr = node->properties;
            attr != NULL; attr = attr->next) {
        data.insert(std::make_pair(string((const char*)attr->name),
                    (const char*)xmlNodeGetContent(attr->children)));
    }
}

