#ifndef ARV_GC_H
#define ARV_GC_H

#include <arv.h>
#include <string>

/**
 * @class ArvGcWrapper
 * @brief Clase para interactuar con el objeto ArvGc en Aravis
 */
class ArvGcWrapper {
public:
    /**
     * @brief Constructor que inicializa ArvGc a partir de un dispositivo
     * @param device Dispositivo ArvDevice
     */
    ArvGcWrapper(ArvDevice* device);

    /**
     * @brief Obtiene el nodo de ArvGc dado su nombre
     * @param name Nombre del nodo
     * @return Nodo ArvGc correspondiente al nombre dado
     */
    ArvGcNode* getNode(const std::string& name);

private:
    ArvGc* gc;
};

#endif // ARV_GC_H
