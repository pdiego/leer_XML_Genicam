#include "ArvGcNode.h"
#include <iostream>

ArvGcNodeWrapper::ArvGcNodeWrapper(ArvGcNode* node) {
    this->node = node;
}

std::string ArvGcNodeWrapper::getName() {
    const char* name = arv_gc_node_get_name(node);
    if (name) {
        return std::string(name);
    }
    return "Unknown";
}
