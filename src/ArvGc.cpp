#include "ArvGc.h"
#include <iostream>

ArvGcWrapper::ArvGcWrapper(ArvDevice* device) {
    gc = arv_device_get_gc(device);
    if (gc == nullptr) {
        std::cerr << "Error al obtener el GenICam (Gc) del dispositivo." << std::endl;
    }
}

ArvGcNode* ArvGcWrapper::getNode(const std::string& name) {
    return arv_gc_get_node(gc, name.c_str());
}
