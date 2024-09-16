#include "doctest.h"
#include "ArvGcNode.h"
#include "ArvGc.h"

TEST_CASE("Testing ArvGcNodeWrapper") {
    arv_update_device_list();
    ArvCamera* camera = arv_camera_new(nullptr);
    REQUIRE(camera != nullptr);

    ArvDevice* device = arv_camera_get_device(camera);
    ArvGcWrapper gcWrapper(device);

    ArvGcNode* node = gcWrapper.getNode("Gain");
    REQUIRE(node != nullptr);

    ArvGcNodeWrapper nodeWrapper(node);
    CHECK(nodeWrapper.getName() == "Gain");

    g_object_unref(camera);
}
