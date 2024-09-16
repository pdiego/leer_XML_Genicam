#include "SensiaBridge.h"



void proyectoSensiaBridge::open_device(ArvCameraPrivate *camera_priv, const char *objetivoDeviceId) {
    // Inicializar el error a nulo
    GError *error = nullptr;

    // Intentar abrir el dispositivo
    camera_priv->device = arv_open_device(objetivoDeviceId, &error);

    // Verificar si ocurrió un error
    if (error != nullptr) {
        // Limpiar cualquier error previo
        if (camera_priv->init_error != nullptr) {
            g_clear_error(&camera_priv->init_error);
        }
        // Almacenar el nuevo error en la estructura
        camera_priv->init_error = error;
    }
}

namespace proyectoSensiaBridge {

    const std::string SENSIA_NAME_U3V = "SENSIA-U3V";
    const std::string SENSIA_VENDOR = "5353";
    const std::string SENSIA_NAME_DEVICE = "SENSIA-U3V";
    const std::string GAIN_REGISTER_KEY = "GainRegister";
    const std::string GENICAM_XML = "genicamSensia.xml";
    const std::string SENSIA_LOG_FILE = "Sensia_Log.file";
    const std::string TEST_NAME_FILE = "SoyEl.xml";

    void SensiaBridge::doSomething(const std::map<std::string, std::string>& arguments) {

        std::string strU3v = SENSIA_NAME_U3V;
        std::string strnameDispositivo = SENSIA_NAME_DEVICE;
        const char *objetivoDeviceId = nullptr;
        ArvBuffer *buffer = NULL;
        GError *errorStream = nullptr;
        const char *test_name = TEST_NAME_FILE.c_str();
        const char* GenICamXML = GENICAM_XML.c_str();
        const char* SENSIA_Log = SENSIA_LOG_FILE.c_str();

        FILE *file = fopen(GenICamXML, "w");
        FILE *logFile = fopen(SENSIA_Log, "w");
        FILE *filexml2 = fopen(test_name, "w");


        // Inicializar la estructura dinámica
        ArvCameraPrivate *priv = g_new0(ArvCameraPrivate, 1);
        std::cout << "inicio aplicacion SensiaBridge." << std::endl;
        arv_update_device_list();

        // Obtener el número de dispositivos disponibles
        int num_devices = arv_get_n_devices();

        if (num_devices == 0) {
            std::cout << "No se encontraron dispositivos." << std::endl;
        } else {
            std::cout << "Número de dispositivos encontrados: " << num_devices << std::endl;
            for (int i = 0; i < num_devices; i++) {
                // Obtener y mostrar la información de cada dispositivo
                const char *device_id = arv_get_device_id(i);
                const char *device_model = arv_get_device_model(i);
                const char *device_serial = arv_get_device_serial_nbr(i);
                const char *device_vendor = arv_get_device_vendor(i);
                const char *device_manufacturer = arv_get_device_manufacturer_info(i);

                std::cout << "Dispositivo " << i + 1 << ": " << device_id << " modelo: " << device_model << std::endl;
                std::cout << "Marca " << device_vendor << " Serial NO: " << device_serial << " manufacturer: " << device_manufacturer << std::endl;
                std::string str(device_model);

                if (str == strU3v) {
                    std::cout << "ERES MI OBJETIVO!!!!! " << std::endl;
                    objetivoDeviceId = device_id;
                    std::string str2(device_serial);
                    strnameDispositivo = str2;
                }
            }
            try {
                std::cout << "PREVIO A OPEN DEVICE... " << std::endl;

                proyectoSensiaBridge::open_device(priv, objetivoDeviceId);

                if (priv->init_error != nullptr) {
                    std::cout << "Error (Gerror): " << priv->init_error->message << std::endl;
                    g_clear_error(&priv->init_error);
                } else {
                    std::cout << "Device opened successfully" << std::endl;
                    const char *genicam;
                    size_t size;
                    try{
                        genicam = arv_device_get_genicam_xml (priv->device, &size);
                        ArvGc *pepe =  arv_device_get_genicam (priv->device);
                        if (genicam != NULL) {
                            fprintf(file, "%*s\n", (int)size, genicam);
                            fclose(file);
                            printf("El contenido XML se ha guardado en %s\n",  GenICamXML);
                        }

                        getFeature(pepe, priv->device, "Root");

                    } catch (...) {
                        std::cout << "Error al obtener el xml! Catch de genicam = arv_device_get_genicam_xml (priv->device, &size)" << std::endl;
                    }
                }

            } catch (...) {
                std::cout << "Estamos en el catch de proyectoSensiaBridge::open_device(priv, objetivoDeviceId) " << std::endl;
            }

        }

        fclose(logFile);
        // Liberar la estructura dinámica
        g_free(priv);
    }

    void getFeature(ArvGc *genicam, ArvDevice *device, const char* nameFeature) {
        GRegex *regex;

        std::cout << "Entramos en getFeature: " << nameFeature << std::endl;
        regex = arv_regex_new_from_glob_pattern (nameFeature, TRUE);
        list_features (genicam, nameFeature, 1,  regex, 0);
        g_regex_unref (regex);
    }

    /*
    void getFeature(ArvDevice *device, const char* nameFeature) {

        int level = 1;

        if (device == NULL)
            std::cout << "Estoy viendo el dispositivo a vacio.\n";

        // Obtener el nodo de Sensor del dispositivo
        ArvGcNode *node = arv_device_get_feature(device, nameFeature);

        // Verificar si el nodo de sensor fue encontrado
        if (node != NULL && ARV_IS_GC_FEATURE_NODE (node)) 
        {
            std::cout << "tengo features....\n";
            if (ARV_IS_GC_CATEGORY (node)) {
                printf ("%*s%-12s: '%s'\n", 4 * level, "", arv_dom_node_get_node_name (ARV_DOM_NODE (node)), arv_gc_feature_node_get_name ( ARV_GC_FEATURE_NODE(node)));
            } else {
                std::cout << "Pues va a ser que no...\n";
            }

        } 
        else
        {
            std::cout << "No se encontro el nodo de sensor.\n";
            return;
        }

    }*/


void list_features (ArvGc *genicam, const char *feature, int list_mode, GRegex *regex, int level)
{
    ArvGcNode *node;

    node = arv_gc_get_node (genicam, feature);
    if (ARV_IS_GC_FEATURE_NODE (node) &&
        arv_gc_feature_node_is_implemented (ARV_GC_FEATURE_NODE (node), NULL)) {
                gboolean match;

                match = regex == NULL || g_regex_match (regex,
                                                        arv_gc_feature_node_get_name (ARV_GC_FEATURE_NODE (node)),
                                                        G_REGEX_MATCH_DEFAULT, NULL);

        if (ARV_IS_GC_CATEGORY (node)) 
        {
            const GSList *features;
            const GSList *iter;

            features = arv_gc_category_get_features (ARV_GC_CATEGORY (node));

            for (iter = features; iter != NULL; iter = iter->next)
                    std::cout << "list_features: " << (const char *) iter->data << std::endl;
                    list_features (genicam, (const char *) iter->data, list_mode, match ? NULL : regex, level + 1);
        }
    }
}

GRegex *arv_regex_new_from_glob_pattern (const char *glob, gboolean caseless)
{
        GRegex *regex;
    GString *regex_pattern;
    const char *iter;
    char **globs;
    gunichar character;
    unsigned int i;

    g_return_val_if_fail (g_utf8_validate (glob, -1, NULL), NULL);

    regex_pattern = g_string_new ("");

    globs = g_strsplit (glob, "|", -1);

    for (i = 0; globs[i] != NULL; i++) {
        /* Ignore empty strings */
        if (globs[i][0] == '\0')
            continue;

        if (i > 0)
            g_string_append (regex_pattern, "|^");
        else
            g_string_append (regex_pattern, "^");

        iter = g_strstrip (globs[i]);
        while (iter != NULL && *iter != '\0') {
            character = g_utf8_get_char (iter);
            switch (character) {
                case '\\':
                    g_string_append (regex_pattern, "\\\\");
                    break;
                case '^':
                    g_string_append (regex_pattern, "\\^");
                    break;
                case '$':
                    g_string_append (regex_pattern, "\\$");
                    break;
                case '.':
                    g_string_append (regex_pattern, "\\.");
                    break;
                case '[':
                    g_string_append (regex_pattern, "\\[");
                    break;
                case '|':
                    g_string_append (regex_pattern, "\\|");
                    break;
                case '(':
                    g_string_append (regex_pattern, "\\(");
                    break;
                case ')':
                    g_string_append (regex_pattern, "\\)");
                    break;
                case '?':
                    g_string_append (regex_pattern, ".");
                    break;
                case '*':
                    g_string_append (regex_pattern, ".*");
                    break;
                case '+':
                    g_string_append (regex_pattern, "\\+");
                    break;
                case '{':
                    g_string_append (regex_pattern, "\\{");
                    break;
                default:
                    g_string_append_unichar (regex_pattern, character);
                    break;
            }
            iter = g_utf8_find_next_char (iter, NULL);
        }

        g_string_append (regex_pattern, "$");
    }

    g_strfreev (globs);

    regex = g_regex_new (regex_pattern->str, G_REGEX_OPTIMIZE, G_REGEX_MATCH_DEFAULT, NULL);
    g_string_free (regex_pattern, TRUE);

    return regex;
}


}