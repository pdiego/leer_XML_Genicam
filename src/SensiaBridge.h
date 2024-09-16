#ifndef SENSIA_BRIDGE_H
#define SENSIA_BRIDGE_H

#include <arv.h>
#include <glib.h>
#include <map>
#include <string>
#include <cstdlib>
#include <iostream>


typedef struct {
    char *name;
    ArvDevice *device;
    ArvGc *genicam;

    gboolean has_serial_number;

    gboolean has_gain;
    gboolean gain_raw_as_float;
    gboolean gain_abs_as_float;

    gboolean has_brightness;
    gboolean has_black_level_raw;
    gboolean has_black_level;

    gboolean has_exposure_time;
    gboolean has_acquisition_frame_rate;
    gboolean has_acquisition_frame_rate_auto;
    gboolean has_acquisition_frame_rate_enabled;

    gboolean has_region_offset;

    GError *init_error;
} ArvCameraPrivate;

// me da error de compilacion y no he visto el porque...
        


namespace proyectoSensiaBridge {

    class SensiaBridge {
    public:
        void doSomething(const std::map<std::string, std::string>& arguments);
    };
    void open_device(ArvCameraPrivate *camera_priv, const char *objetivoDeviceId);
    void getFeature(ArvGc *genicam, ArvDevice *device, const char* nameFeature);
    GRegex *arv_regex_new_from_glob_pattern (const char *glob, gboolean caseless);
    void list_features (ArvGc *genicam, const char *feature, int list_mode, GRegex *regex, int level);
}

#endif // SENSIA_BRIDGE_H