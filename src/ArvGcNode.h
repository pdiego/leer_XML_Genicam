#ifndef ARV_GC_NODE_H
#define ARV_GC_NODE_H

#include <arv.h>
#include <string>

/**
 * @class ArvGcNodeWrapper
 * @brief Clase para interactuar con los nodos de ArvGc
 */
class ArvGcNodeWrapper {
public:
    /**
     * @brief Constructor que inicializa un nodo de ArvGc
     * @param node Nodo de ArvGc
     */
    ArvGcNodeWrapper(ArvGcNode* node);

    /**
     * @brief Obtiene el nombre del nodo
     * @return Nombre del nodo como string
     */
    std::string getName();

private:
    ArvGcNode* node;
};

#endif // ARV_GC_NODE_H
