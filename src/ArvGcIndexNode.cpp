#include "ArvGcIndexNode.h"

ArvGcIndexNodeWrapper::ArvGcIndexNodeWrapper(ArvGcIndexNode* node) {
    this->node = node;
}

int ArvGcIndexNodeWrapper::getIndex() {
    return arv_gc_index_node_get_index(node);
}
