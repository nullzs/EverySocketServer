aux_source_directory(tcp SOCKET_TCP_SRC)
aux_source_directory(udp SOCKET_UDP_SRC)

add_library(socket_lib ${SOCKET_TCP_SRC} ${SOCKET_UDP_SRC})