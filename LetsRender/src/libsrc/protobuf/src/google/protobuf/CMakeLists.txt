set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -fPIC -Wfatal-errors" )

include_directories(../../../src)

set(SRC
  descriptor.cc
  descriptor_database.cc
  reflection_ops.cc
  descriptor.pb.cc
  repeated_field.cc
  dynamic_message.cc
  service.cc
  extension_set.cc
  extension_set_heavy.cc
  text_format.cc
  generated_message_reflection.cc
  unknown_field_set.cc
  generated_message_util.cc
  wire_format.cc
  message.cc
  wire_format_lite.cc
  message_lite.cc)

set(SRC_STUBS
  stubs/structurally_valid.cc
  stubs/common.cc
  stubs/strutil.cc
  stubs/once.cc
  stubs/substitute.cc)

set(SRC_IO
  io/coded_stream.cc
  io/printer.cc
  io/zero_copy_stream_impl_lite.cc
  io/zero_copy_stream.cc
  io/gzip_stream.cc
  io/tokenizer.cc
  io/zero_copy_stream_impl.cc)

add_library(protobuf ${SRC} ${SRC_STUBS} ${SRC_IO})
