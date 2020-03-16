# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES)
set(COMPONENT_PRIV_REQUIRES freertos protocol_examples_common nvs_flash esp-tls esp_http_client) 

set(COMPONENT_SRCS "my_http_sender.c")
set(COMPONENT_ADD_INCLUDEDIRS "include")

register_component()
