#include "doctest.h"
#include "ArvGcValueIndexedNode.h"

TEST_CASE("Testing ArvGcValueIndexedNodeWrapper") {
    // Simulación o uso real de ArvGcValueIndexedNode
    ArvGcValueIndexedNode* node = nullptr;  // Asumir inicialización
    ArvGcValueIndexedNodeWrapper wrapper(node);

    CHECK(wrapper.getIndexedValue() == 0);  // Prueba inicial ficticia
}
