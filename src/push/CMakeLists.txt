aux_source_directory(. PUSH_SRC)
aux_source_directory(push_pool PUSH_POOL_SRC)

add_library(push_lib ${PUSH_SRC} ${PUSH_POOL_SRC} )