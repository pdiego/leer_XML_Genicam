#ifndef ARV_GC_INDEX_NODE_H
#define ARV_GC_INDEX_NODE_H

#include <arv.h>

/**
 * @class ArvGcIndexNodeWrapper
 * @brief Clase para interactuar con los nodos indexados de ArvGc
 */
class ArvGcIndexNodeWrapper {
public:
    /**
     * @brief Constructor que inicializa un nodo indexado
     * @param node Nodo indexado de ArvGc
     */
    ArvGcIndexNodeWrapper(ArvGcIndexNode* node);

    /**
     * @brief Obtiene el índice del nodo
     * @return Índice del nodo
     */
    int getIndex();

private:
    ArvGcIndexNode* node;
};

#endif // ARV_GC_INDEX_NODE_H
