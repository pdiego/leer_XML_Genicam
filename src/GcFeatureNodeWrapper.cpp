//  ArvGcFeatureNode

#include <arv.h>
#include <iostream>
#include <string>

class GcFeatureNodeWrapper {
public:
    GcFeatureNodeWrapper(ArvGc *gc, const std::string &feature_name) {
        feature_node = ARV_GC_FEATURE_NODE(arv_gc_get_node(gc, feature_name.c_str()));
        if (feature_node == nullptr) {
            std::cerr << "Failed to retrieve feature node: " << feature_name << std::endl;
        }
    }

    // Obtener el tipo de la feature
    std::string getType() {
        if (feature_node) {
            const char *type = arv_gc_feature_node_get_type(feature_node);
            if (type) {
                return std::string(type);
            }
        }
        return "Unknown";
    }

    // Obtener el nombre de la feature
    std::string getName() {
        if (feature_node) {
            const char *name = arv_gc_feature_node_get_name(feature_node);
            if (name) {
                return std::string(name);
            }
        }
        return "Unknown";
    }

    // Verificar si la feature es "implementable"
    bool isImplemented(ArvDevice *device) {
        if (feature_node && device) {
            return arv_gc_feature_node_is_implemented(feature_node, device);
        }
        return false;
    }

    // Verificar si la feature es legible
    bool isReadable(ArvDevice *device) {
        if (feature_node && device) {
            return arv_gc_feature_node_is_readable(feature_node, device);
        }
        return false;
    }

    // Verificar si la feature es escribible
    bool isWritable(ArvDevice *device) {
        if (feature_node && device) {
            return arv_gc_feature_node_is_writable(feature_node, device);
        }
        return false;
    }

private:
    ArvGcFeatureNode *feature_node;
};

int main() {
    // Inicialización de Aravis
    arv_update_device_list();

    // Obtener la primera cámara disponible
    ArvCamera *camera = arv_camera_new(nullptr);
    if (!camera) {
        std::cerr << "No se encontró ninguna cámara compatible." << std::endl;
        return -1;
    }

    // Obtener el Device y el Gc correspondiente
    ArvDevice *device = arv_camera_get_device(camera);
    ArvGc *gc = arv_device_get_gc(device);

    // Crear un objeto de la clase GcFeatureNodeWrapper con un feature específico
    GcFeatureNodeWrapper featureNode(gc, "Gain");

    // Imprimir información sobre el feature
    std::cout << "Nombre: " << featureNode.getName() << std::endl;
    std::cout << "Tipo: " << featureNode.getType() << std::endl;

    if (featureNode.isImplemented(device)) {
        std::cout << "La característica está implementada." << std::endl;
    }

    if (featureNode.isReadable(device)) {
        std::cout << "La característica es legible." << std::endl;
    }

    if (featureNode.isWritable(device)) {
        std::cout << "La característica es escribible." << std::endl;
    }

    // Liberar la memoria
    g_object_unref(camera);

    return 0;
}
