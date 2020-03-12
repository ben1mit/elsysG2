# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES)
set(COMPONENT_PRIV_REQUIRES bt nvs_flash)

set(COMPONENT_SRCS "spp_client_demo.c")
set(COMPONENT_ADD_INCLUDEDIRS "include")

register_component()
