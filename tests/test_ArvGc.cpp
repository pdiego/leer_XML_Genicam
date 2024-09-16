#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "ArvGc.h"

TEST_CASE("Testing ArvGcWrapper") {
    arv_update_device_list();
    ArvCamera* camera = arv_camera_new(nullptr);
    REQUIRE(camera != nullptr);

    ArvDevice* device = arv_camera_get_device(camera);
    ArvGcWrapper gcWrapper(device);

    ArvGcNode* node = gcWrapper.getNode("Gain");
    CHECK(node != nullptr);

    g_object_unref(camera);
}
