
    int emitirVideo(int argc, char **argv, ArvCameraPrivate *cam)
    {
        ArvCamera *camera;
        ArvStream *stream;
        GError *error = nullptr;
        gst_init(&argc, &argv);

        arv_update_device_list();

        camera = arv_camera_new_with_device (cam, &error);
        if (camera == NULL) {
            g_error("No se pudo abrir la cámara\n");
            return -1;
        }

        stream = arv_camera_create_stream (camera, NULL, NULL, &error);
        if (stream == NULL) {
            g_error("No se pudo crear el stream\n");
            g_object_unref(camera);
            return -1;
        }

        // Configuración de GStreamer para emitir el video
        gchar *pipeline_desc = g_strdup_printf(
            "appsrc name=src is-live=true ! videoconvert ! "
            "x264enc tune=zerolatency ! rtph264pay config-interval=1 pt=96 ! "
            "udpsink host=127.0.0.1 port=5000");

        GstElement *pipeline = gst_parse_launch(pipeline_desc, NULL);
        GstElement *appsrc = gst_bin_get_by_name(GST_BIN(pipeline), "src");

        g_free(pipeline_desc);

        arv_camera_start_acquisition (camera, &error);

        // Main loop to push buffers to GStreamer pipeline
        while (TRUE) {
            ArvBuffer *buffer = arv_stream_timeout_pop_buffer (stream, 2000000);
            if (buffer != NULL) {
                if (arv_buffer_get_status (buffer) == ARV_BUFFER_STATUS_SUCCESS) {
                    guint8 *data;
                    size_t size;
                    GstBuffer *gst_buffer;
                    GstMapInfo map;

                    data = (guint8 *) arv_buffer_get_data (buffer, &size);
                    gst_buffer = gst_buffer_new_allocate(NULL, size, NULL);
                    gst_buffer_map(gst_buffer, &map, GST_MAP_WRITE);
                    memcpy(map.data, data, size);
                    gst_buffer_unmap(gst_buffer, &map);

                    g_signal_emit_by_name(appsrc, "push-buffer", gst_buffer, NULL);
                    gst_buffer_unref(gst_buffer);
                }
                arv_stream_push_buffer (stream, buffer);
            }
        }

        arv_camera_stop_acquisition (camera);

        g_object_unref(stream);
        g_object_unref(camera);

        return 0;
    }