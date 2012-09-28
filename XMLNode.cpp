#include "XMLNode.h"

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


