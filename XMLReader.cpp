#include "XMLReader.h"

/**
 * Utility methods
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

