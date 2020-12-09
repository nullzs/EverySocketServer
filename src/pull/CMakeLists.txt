aux_source_directory(. PULL_SRC)
aux_source_directory(pull_pool PULL_POOL_SRC)

add_library(pull_lib ${PULL_SRC} ${PULL_POOL_SRC})