# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES)
set(COMPONENT_PRIV_REQUIRES bt nvs_flash my_http_sender)

set(COMPONENT_SRCS "ble_spp_server_demo.c")
set(COMPONENT_ADD_INCLUDEDIRS "include")

register_component()
