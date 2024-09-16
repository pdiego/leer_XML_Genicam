#include "ArvGcValueIndexedNode.h"

ArvGcValueIndexedNodeWrapper::ArvGcValueIndexedNodeWrapper(ArvGcValueIndexedNode* node) {
    this->node = node;
}

int ArvGcValueIndexedNodeWrapper::getIndexedValue() {
    return arv_gc_value_indexed_node_get_value(node);
}
