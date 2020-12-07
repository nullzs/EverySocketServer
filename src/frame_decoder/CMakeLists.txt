aux_source_directory(. FRAME_DECODER_SRC)
aux_source_directory(decoder DECODER_SRC)

add_library(frame_decoder_lib ${FRAME_DECODER_SRC} ${DECODER_SRC})