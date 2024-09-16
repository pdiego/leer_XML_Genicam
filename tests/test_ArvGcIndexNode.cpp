#include "doctest.h"
#include "ArvGcIndexNode.h"

TEST_CASE("Testing ArvGcIndexNodeWrapper") {
    // Simulación o uso real de ArvGcIndexNode
    ArvGcIndexNode* node = nullptr;  // Asumir inicialización
    ArvGcIndexNodeWrapper wrapper(node);

    CHECK(wrapper.getIndex() == 0);  // Prueba inicial ficticia
}
