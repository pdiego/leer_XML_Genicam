#ifndef ARV_GC_VALUE_INDEXED_NODE_H
#define ARV_GC_VALUE_INDEXED_NODE_H

#include <arv.h>

/**
 * @class ArvGcValueIndexedNodeWrapper
 * @brief Clase para interactuar con los nodos de valor indexado de ArvGc
 */
class ArvGcValueIndexedNodeWrapper {
public:
    /**
     * @brief Constructor que inicializa un nodo de valor indexado
     * @param node Nodo de valor indexado de ArvGc
     */
    ArvGcValueIndexedNodeWrapper(ArvGcValueIndexedNode* node);

    /**
     * @brief Obtiene el valor indexado del nodo
     * @return Valor indexado del nodo
     */
    int getIndexedValue();

private:
    ArvGcValueIndexedNode* node;
};

#endif // ARV_GC_VALUE_INDEXED_NODE_H
