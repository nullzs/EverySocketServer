aux_source_directory(. PULL_SRC)
aux_source_directory(pull_pool PULL_POOL_SRC)
aux_source_directory(pull_server_udp PULL_UDP_SRC)

add_library(pull_lib ${PULL_SRC} ${PULL_POOL_SRC} ${PULL_UDP_SRC})