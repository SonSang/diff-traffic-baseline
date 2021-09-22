// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: location.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "location.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace routing {

namespace {

const ::google::protobuf::Descriptor* Location_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Location_reflection_ = NULL;
const ::google::protobuf::Descriptor* RoutingQuery_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  RoutingQuery_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_location_2eproto() {
  protobuf_AddDesc_location_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "location.proto");
  GOOGLE_CHECK(file != NULL);
  Location_descriptor_ = file->message_type(0);
  static const int Location_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Location, latitude_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Location, longitude_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Location, direction_),
  };
  Location_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Location_descriptor_,
      Location::default_instance_,
      Location_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Location, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Location, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Location));
  RoutingQuery_descriptor_ = file->message_type(1);
  static const int RoutingQuery_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoutingQuery, current_location_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoutingQuery, destination_location_),
  };
  RoutingQuery_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      RoutingQuery_descriptor_,
      RoutingQuery::default_instance_,
      RoutingQuery_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoutingQuery, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RoutingQuery, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(RoutingQuery));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_location_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Location_descriptor_, &Location::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    RoutingQuery_descriptor_, &RoutingQuery::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_location_2eproto() {
  delete Location::default_instance_;
  delete Location_reflection_;
  delete RoutingQuery::default_instance_;
  delete RoutingQuery_reflection_;
}

void protobuf_AddDesc_location_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\016location.proto\022\007routing\"B\n\010Location\022\020\n"
    "\010latitude\030\001 \002(\002\022\021\n\tlongitude\030\002 \002(\002\022\021\n\tdi"
    "rection\030\003 \001(\002\"l\n\014RoutingQuery\022+\n\020current"
    "_location\030\001 \002(\0132\021.routing.Location\022/\n\024de"
    "stination_location\030\002 \002(\0132\021.routing.Locat"
    "ionB1\n com.gamma.trafficrouting.routingB"
    "\rLocationProto", 254);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "location.proto", &protobuf_RegisterTypes);
  Location::default_instance_ = new Location();
  RoutingQuery::default_instance_ = new RoutingQuery();
  Location::default_instance_->InitAsDefaultInstance();
  RoutingQuery::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_location_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_location_2eproto {
  StaticDescriptorInitializer_location_2eproto() {
    protobuf_AddDesc_location_2eproto();
  }
} static_descriptor_initializer_location_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Location::kLatitudeFieldNumber;
const int Location::kLongitudeFieldNumber;
const int Location::kDirectionFieldNumber;
#endif  // !_MSC_VER

Location::Location()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:routing.Location)
}

void Location::InitAsDefaultInstance() {
}

Location::Location(const Location& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:routing.Location)
}

void Location::SharedCtor() {
  _cached_size_ = 0;
  latitude_ = 0;
  longitude_ = 0;
  direction_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Location::~Location() {
  // @@protoc_insertion_point(destructor:routing.Location)
  SharedDtor();
}

void Location::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Location::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Location::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Location_descriptor_;
}

const Location& Location::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_location_2eproto();
  return *default_instance_;
}

Location* Location::default_instance_ = NULL;

Location* Location::New() const {
  return new Location;
}

void Location::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<Location*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(latitude_, direction_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Location::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:routing.Location)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required float latitude = 1;
      case 1: {
        if (tag == 13) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &latitude_)));
          set_has_latitude();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(21)) goto parse_longitude;
        break;
      }

      // required float longitude = 2;
      case 2: {
        if (tag == 21) {
         parse_longitude:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &longitude_)));
          set_has_longitude();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(29)) goto parse_direction;
        break;
      }

      // optional float direction = 3;
      case 3: {
        if (tag == 29) {
         parse_direction:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &direction_)));
          set_has_direction();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:routing.Location)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:routing.Location)
  return false;
#undef DO_
}

void Location::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:routing.Location)
  // required float latitude = 1;
  if (has_latitude()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(1, this->latitude(), output);
  }

  // required float longitude = 2;
  if (has_longitude()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(2, this->longitude(), output);
  }

  // optional float direction = 3;
  if (has_direction()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(3, this->direction(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:routing.Location)
}

::google::protobuf::uint8* Location::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:routing.Location)
  // required float latitude = 1;
  if (has_latitude()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(1, this->latitude(), target);
  }

  // required float longitude = 2;
  if (has_longitude()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(2, this->longitude(), target);
  }

  // optional float direction = 3;
  if (has_direction()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(3, this->direction(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:routing.Location)
  return target;
}

int Location::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required float latitude = 1;
    if (has_latitude()) {
      total_size += 1 + 4;
    }

    // required float longitude = 2;
    if (has_longitude()) {
      total_size += 1 + 4;
    }

    // optional float direction = 3;
    if (has_direction()) {
      total_size += 1 + 4;
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Location::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Location* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Location*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Location::MergeFrom(const Location& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_latitude()) {
      set_latitude(from.latitude());
    }
    if (from.has_longitude()) {
      set_longitude(from.longitude());
    }
    if (from.has_direction()) {
      set_direction(from.direction());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Location::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Location::CopyFrom(const Location& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Location::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void Location::Swap(Location* other) {
  if (other != this) {
    std::swap(latitude_, other->latitude_);
    std::swap(longitude_, other->longitude_);
    std::swap(direction_, other->direction_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Location::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Location_descriptor_;
  metadata.reflection = Location_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int RoutingQuery::kCurrentLocationFieldNumber;
const int RoutingQuery::kDestinationLocationFieldNumber;
#endif  // !_MSC_VER

RoutingQuery::RoutingQuery()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:routing.RoutingQuery)
}

void RoutingQuery::InitAsDefaultInstance() {
  current_location_ = const_cast< ::routing::Location*>(&::routing::Location::default_instance());
  destination_location_ = const_cast< ::routing::Location*>(&::routing::Location::default_instance());
}

RoutingQuery::RoutingQuery(const RoutingQuery& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:routing.RoutingQuery)
}

void RoutingQuery::SharedCtor() {
  _cached_size_ = 0;
  current_location_ = NULL;
  destination_location_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

RoutingQuery::~RoutingQuery() {
  // @@protoc_insertion_point(destructor:routing.RoutingQuery)
  SharedDtor();
}

void RoutingQuery::SharedDtor() {
  if (this != default_instance_) {
    delete current_location_;
    delete destination_location_;
  }
}

void RoutingQuery::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* RoutingQuery::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return RoutingQuery_descriptor_;
}

const RoutingQuery& RoutingQuery::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_location_2eproto();
  return *default_instance_;
}

RoutingQuery* RoutingQuery::default_instance_ = NULL;

RoutingQuery* RoutingQuery::New() const {
  return new RoutingQuery;
}

void RoutingQuery::Clear() {
  if (_has_bits_[0 / 32] & 3) {
    if (has_current_location()) {
      if (current_location_ != NULL) current_location_->::routing::Location::Clear();
    }
    if (has_destination_location()) {
      if (destination_location_ != NULL) destination_location_->::routing::Location::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool RoutingQuery::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:routing.RoutingQuery)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .routing.Location current_location = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_current_location()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_destination_location;
        break;
      }

      // required .routing.Location destination_location = 2;
      case 2: {
        if (tag == 18) {
         parse_destination_location:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_destination_location()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:routing.RoutingQuery)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:routing.RoutingQuery)
  return false;
#undef DO_
}

void RoutingQuery::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:routing.RoutingQuery)
  // required .routing.Location current_location = 1;
  if (has_current_location()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->current_location(), output);
  }

  // required .routing.Location destination_location = 2;
  if (has_destination_location()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->destination_location(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:routing.RoutingQuery)
}

::google::protobuf::uint8* RoutingQuery::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:routing.RoutingQuery)
  // required .routing.Location current_location = 1;
  if (has_current_location()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->current_location(), target);
  }

  // required .routing.Location destination_location = 2;
  if (has_destination_location()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->destination_location(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:routing.RoutingQuery)
  return target;
}

int RoutingQuery::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .routing.Location current_location = 1;
    if (has_current_location()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->current_location());
    }

    // required .routing.Location destination_location = 2;
    if (has_destination_location()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->destination_location());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void RoutingQuery::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const RoutingQuery* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const RoutingQuery*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void RoutingQuery::MergeFrom(const RoutingQuery& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_current_location()) {
      mutable_current_location()->::routing::Location::MergeFrom(from.current_location());
    }
    if (from.has_destination_location()) {
      mutable_destination_location()->::routing::Location::MergeFrom(from.destination_location());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void RoutingQuery::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void RoutingQuery::CopyFrom(const RoutingQuery& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RoutingQuery::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  if (has_current_location()) {
    if (!this->current_location().IsInitialized()) return false;
  }
  if (has_destination_location()) {
    if (!this->destination_location().IsInitialized()) return false;
  }
  return true;
}

void RoutingQuery::Swap(RoutingQuery* other) {
  if (other != this) {
    std::swap(current_location_, other->current_location_);
    std::swap(destination_location_, other->destination_location_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata RoutingQuery::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = RoutingQuery_descriptor_;
  metadata.reflection = RoutingQuery_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace routing

// @@protoc_insertion_point(global_scope)
