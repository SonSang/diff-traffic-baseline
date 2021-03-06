// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: road_network.proto

#ifndef PROTOBUF_road_5fnetwork_2eproto__INCLUDED
#define PROTOBUF_road_5fnetwork_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_road_5fnetwork_2eproto();
void protobuf_AssignDesc_road_5fnetwork_2eproto();
void protobuf_ShutdownFile_road_5fnetwork_2eproto();

class PointMessage;
class RoadMessage;
class RoadTupleMessage;
class RoadNetworkMessage;

// ===================================================================

class PointMessage : public ::google::protobuf::Message {
 public:
  PointMessage();
  virtual ~PointMessage();

  PointMessage(const PointMessage& from);

  inline PointMessage& operator=(const PointMessage& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const PointMessage& default_instance();

  void Swap(PointMessage* other);

  // implements Message ----------------------------------------------

  PointMessage* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PointMessage& from);
  void MergeFrom(const PointMessage& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required float x = 1;
  inline bool has_x() const;
  inline void clear_x();
  static const int kXFieldNumber = 1;
  inline float x() const;
  inline void set_x(float value);

  // required float y = 2;
  inline bool has_y() const;
  inline void clear_y();
  static const int kYFieldNumber = 2;
  inline float y() const;
  inline void set_y(float value);

  // @@protoc_insertion_point(class_scope:PointMessage)
 private:
  inline void set_has_x();
  inline void clear_has_x();
  inline void set_has_y();
  inline void clear_has_y();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  float x_;
  float y_;
  friend void  protobuf_AddDesc_road_5fnetwork_2eproto();
  friend void protobuf_AssignDesc_road_5fnetwork_2eproto();
  friend void protobuf_ShutdownFile_road_5fnetwork_2eproto();

  void InitAsDefaultInstance();
  static PointMessage* default_instance_;
};
// -------------------------------------------------------------------

class RoadMessage : public ::google::protobuf::Message {
 public:
  RoadMessage();
  virtual ~RoadMessage();

  RoadMessage(const RoadMessage& from);

  inline RoadMessage& operator=(const RoadMessage& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const RoadMessage& default_instance();

  void Swap(RoadMessage* other);

  // implements Message ----------------------------------------------

  RoadMessage* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RoadMessage& from);
  void MergeFrom(const RoadMessage& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string type = 1;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline const ::std::string& type() const;
  inline void set_type(const ::std::string& value);
  inline void set_type(const char* value);
  inline void set_type(const char* value, size_t size);
  inline ::std::string* mutable_type();
  inline ::std::string* release_type();
  inline void set_allocated_type(::std::string* type);

  // optional int32 lane_count = 2;
  inline bool has_lane_count() const;
  inline void clear_lane_count();
  static const int kLaneCountFieldNumber = 2;
  inline ::google::protobuf::int32 lane_count() const;
  inline void set_lane_count(::google::protobuf::int32 value);

  // optional float length = 3;
  inline bool has_length() const;
  inline void clear_length();
  static const int kLengthFieldNumber = 3;
  inline float length() const;
  inline void set_length(float value);

  // repeated .PointMessage geometry = 4;
  inline int geometry_size() const;
  inline void clear_geometry();
  static const int kGeometryFieldNumber = 4;
  inline const ::PointMessage& geometry(int index) const;
  inline ::PointMessage* mutable_geometry(int index);
  inline ::PointMessage* add_geometry();
  inline const ::google::protobuf::RepeatedPtrField< ::PointMessage >&
      geometry() const;
  inline ::google::protobuf::RepeatedPtrField< ::PointMessage >*
      mutable_geometry();

  // @@protoc_insertion_point(class_scope:RoadMessage)
 private:
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_lane_count();
  inline void clear_has_lane_count();
  inline void set_has_length();
  inline void clear_has_length();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* type_;
  ::google::protobuf::int32 lane_count_;
  float length_;
  ::google::protobuf::RepeatedPtrField< ::PointMessage > geometry_;
  friend void  protobuf_AddDesc_road_5fnetwork_2eproto();
  friend void protobuf_AssignDesc_road_5fnetwork_2eproto();
  friend void protobuf_ShutdownFile_road_5fnetwork_2eproto();

  void InitAsDefaultInstance();
  static RoadMessage* default_instance_;
};
// -------------------------------------------------------------------

class RoadTupleMessage : public ::google::protobuf::Message {
 public:
  RoadTupleMessage();
  virtual ~RoadTupleMessage();

  RoadTupleMessage(const RoadTupleMessage& from);

  inline RoadTupleMessage& operator=(const RoadTupleMessage& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const RoadTupleMessage& default_instance();

  void Swap(RoadTupleMessage* other);

  // implements Message ----------------------------------------------

  RoadTupleMessage* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RoadTupleMessage& from);
  void MergeFrom(const RoadTupleMessage& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 road_index = 1;
  inline bool has_road_index() const;
  inline void clear_road_index();
  static const int kRoadIndexFieldNumber = 1;
  inline ::google::protobuf::int32 road_index() const;
  inline void set_road_index(::google::protobuf::int32 value);

  // required .RoadMessage road = 2;
  inline bool has_road() const;
  inline void clear_road();
  static const int kRoadFieldNumber = 2;
  inline const ::RoadMessage& road() const;
  inline ::RoadMessage* mutable_road();
  inline ::RoadMessage* release_road();
  inline void set_allocated_road(::RoadMessage* road);

  // @@protoc_insertion_point(class_scope:RoadTupleMessage)
 private:
  inline void set_has_road_index();
  inline void clear_has_road_index();
  inline void set_has_road();
  inline void clear_has_road();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::RoadMessage* road_;
  ::google::protobuf::int32 road_index_;
  friend void  protobuf_AddDesc_road_5fnetwork_2eproto();
  friend void protobuf_AssignDesc_road_5fnetwork_2eproto();
  friend void protobuf_ShutdownFile_road_5fnetwork_2eproto();

  void InitAsDefaultInstance();
  static RoadTupleMessage* default_instance_;
};
// -------------------------------------------------------------------

class RoadNetworkMessage : public ::google::protobuf::Message {
 public:
  RoadNetworkMessage();
  virtual ~RoadNetworkMessage();

  RoadNetworkMessage(const RoadNetworkMessage& from);

  inline RoadNetworkMessage& operator=(const RoadNetworkMessage& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const RoadNetworkMessage& default_instance();

  void Swap(RoadNetworkMessage* other);

  // implements Message ----------------------------------------------

  RoadNetworkMessage* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RoadNetworkMessage& from);
  void MergeFrom(const RoadNetworkMessage& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .RoadTupleMessage id_and_road = 1;
  inline int id_and_road_size() const;
  inline void clear_id_and_road();
  static const int kIdAndRoadFieldNumber = 1;
  inline const ::RoadTupleMessage& id_and_road(int index) const;
  inline ::RoadTupleMessage* mutable_id_and_road(int index);
  inline ::RoadTupleMessage* add_id_and_road();
  inline const ::google::protobuf::RepeatedPtrField< ::RoadTupleMessage >&
      id_and_road() const;
  inline ::google::protobuf::RepeatedPtrField< ::RoadTupleMessage >*
      mutable_id_and_road();

  // @@protoc_insertion_point(class_scope:RoadNetworkMessage)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::RoadTupleMessage > id_and_road_;
  friend void  protobuf_AddDesc_road_5fnetwork_2eproto();
  friend void protobuf_AssignDesc_road_5fnetwork_2eproto();
  friend void protobuf_ShutdownFile_road_5fnetwork_2eproto();

  void InitAsDefaultInstance();
  static RoadNetworkMessage* default_instance_;
};
// ===================================================================


// ===================================================================

// PointMessage

// required float x = 1;
inline bool PointMessage::has_x() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PointMessage::set_has_x() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PointMessage::clear_has_x() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PointMessage::clear_x() {
  x_ = 0;
  clear_has_x();
}
inline float PointMessage::x() const {
  // @@protoc_insertion_point(field_get:PointMessage.x)
  return x_;
}
inline void PointMessage::set_x(float value) {
  set_has_x();
  x_ = value;
  // @@protoc_insertion_point(field_set:PointMessage.x)
}

// required float y = 2;
inline bool PointMessage::has_y() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void PointMessage::set_has_y() {
  _has_bits_[0] |= 0x00000002u;
}
inline void PointMessage::clear_has_y() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void PointMessage::clear_y() {
  y_ = 0;
  clear_has_y();
}
inline float PointMessage::y() const {
  // @@protoc_insertion_point(field_get:PointMessage.y)
  return y_;
}
inline void PointMessage::set_y(float value) {
  set_has_y();
  y_ = value;
  // @@protoc_insertion_point(field_set:PointMessage.y)
}

// -------------------------------------------------------------------

// RoadMessage

// required string type = 1;
inline bool RoadMessage::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RoadMessage::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RoadMessage::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RoadMessage::clear_type() {
  if (type_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    type_->clear();
  }
  clear_has_type();
}
inline const ::std::string& RoadMessage::type() const {
  // @@protoc_insertion_point(field_get:RoadMessage.type)
  return *type_;
}
inline void RoadMessage::set_type(const ::std::string& value) {
  set_has_type();
  if (type_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    type_ = new ::std::string;
  }
  type_->assign(value);
  // @@protoc_insertion_point(field_set:RoadMessage.type)
}
inline void RoadMessage::set_type(const char* value) {
  set_has_type();
  if (type_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    type_ = new ::std::string;
  }
  type_->assign(value);
  // @@protoc_insertion_point(field_set_char:RoadMessage.type)
}
inline void RoadMessage::set_type(const char* value, size_t size) {
  set_has_type();
  if (type_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    type_ = new ::std::string;
  }
  type_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:RoadMessage.type)
}
inline ::std::string* RoadMessage::mutable_type() {
  set_has_type();
  if (type_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    type_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:RoadMessage.type)
  return type_;
}
inline ::std::string* RoadMessage::release_type() {
  clear_has_type();
  if (type_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = type_;
    type_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void RoadMessage::set_allocated_type(::std::string* type) {
  if (type_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete type_;
  }
  if (type) {
    set_has_type();
    type_ = type;
  } else {
    clear_has_type();
    type_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:RoadMessage.type)
}

// optional int32 lane_count = 2;
inline bool RoadMessage::has_lane_count() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RoadMessage::set_has_lane_count() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RoadMessage::clear_has_lane_count() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void RoadMessage::clear_lane_count() {
  lane_count_ = 0;
  clear_has_lane_count();
}
inline ::google::protobuf::int32 RoadMessage::lane_count() const {
  // @@protoc_insertion_point(field_get:RoadMessage.lane_count)
  return lane_count_;
}
inline void RoadMessage::set_lane_count(::google::protobuf::int32 value) {
  set_has_lane_count();
  lane_count_ = value;
  // @@protoc_insertion_point(field_set:RoadMessage.lane_count)
}

// optional float length = 3;
inline bool RoadMessage::has_length() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void RoadMessage::set_has_length() {
  _has_bits_[0] |= 0x00000004u;
}
inline void RoadMessage::clear_has_length() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void RoadMessage::clear_length() {
  length_ = 0;
  clear_has_length();
}
inline float RoadMessage::length() const {
  // @@protoc_insertion_point(field_get:RoadMessage.length)
  return length_;
}
inline void RoadMessage::set_length(float value) {
  set_has_length();
  length_ = value;
  // @@protoc_insertion_point(field_set:RoadMessage.length)
}

// repeated .PointMessage geometry = 4;
inline int RoadMessage::geometry_size() const {
  return geometry_.size();
}
inline void RoadMessage::clear_geometry() {
  geometry_.Clear();
}
inline const ::PointMessage& RoadMessage::geometry(int index) const {
  // @@protoc_insertion_point(field_get:RoadMessage.geometry)
  return geometry_.Get(index);
}
inline ::PointMessage* RoadMessage::mutable_geometry(int index) {
  // @@protoc_insertion_point(field_mutable:RoadMessage.geometry)
  return geometry_.Mutable(index);
}
inline ::PointMessage* RoadMessage::add_geometry() {
  // @@protoc_insertion_point(field_add:RoadMessage.geometry)
  return geometry_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::PointMessage >&
RoadMessage::geometry() const {
  // @@protoc_insertion_point(field_list:RoadMessage.geometry)
  return geometry_;
}
inline ::google::protobuf::RepeatedPtrField< ::PointMessage >*
RoadMessage::mutable_geometry() {
  // @@protoc_insertion_point(field_mutable_list:RoadMessage.geometry)
  return &geometry_;
}

// -------------------------------------------------------------------

// RoadTupleMessage

// required int32 road_index = 1;
inline bool RoadTupleMessage::has_road_index() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RoadTupleMessage::set_has_road_index() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RoadTupleMessage::clear_has_road_index() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RoadTupleMessage::clear_road_index() {
  road_index_ = 0;
  clear_has_road_index();
}
inline ::google::protobuf::int32 RoadTupleMessage::road_index() const {
  // @@protoc_insertion_point(field_get:RoadTupleMessage.road_index)
  return road_index_;
}
inline void RoadTupleMessage::set_road_index(::google::protobuf::int32 value) {
  set_has_road_index();
  road_index_ = value;
  // @@protoc_insertion_point(field_set:RoadTupleMessage.road_index)
}

// required .RoadMessage road = 2;
inline bool RoadTupleMessage::has_road() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RoadTupleMessage::set_has_road() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RoadTupleMessage::clear_has_road() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void RoadTupleMessage::clear_road() {
  if (road_ != NULL) road_->::RoadMessage::Clear();
  clear_has_road();
}
inline const ::RoadMessage& RoadTupleMessage::road() const {
  // @@protoc_insertion_point(field_get:RoadTupleMessage.road)
  return road_ != NULL ? *road_ : *default_instance_->road_;
}
inline ::RoadMessage* RoadTupleMessage::mutable_road() {
  set_has_road();
  if (road_ == NULL) road_ = new ::RoadMessage;
  // @@protoc_insertion_point(field_mutable:RoadTupleMessage.road)
  return road_;
}
inline ::RoadMessage* RoadTupleMessage::release_road() {
  clear_has_road();
  ::RoadMessage* temp = road_;
  road_ = NULL;
  return temp;
}
inline void RoadTupleMessage::set_allocated_road(::RoadMessage* road) {
  delete road_;
  road_ = road;
  if (road) {
    set_has_road();
  } else {
    clear_has_road();
  }
  // @@protoc_insertion_point(field_set_allocated:RoadTupleMessage.road)
}

// -------------------------------------------------------------------

// RoadNetworkMessage

// repeated .RoadTupleMessage id_and_road = 1;
inline int RoadNetworkMessage::id_and_road_size() const {
  return id_and_road_.size();
}
inline void RoadNetworkMessage::clear_id_and_road() {
  id_and_road_.Clear();
}
inline const ::RoadTupleMessage& RoadNetworkMessage::id_and_road(int index) const {
  // @@protoc_insertion_point(field_get:RoadNetworkMessage.id_and_road)
  return id_and_road_.Get(index);
}
inline ::RoadTupleMessage* RoadNetworkMessage::mutable_id_and_road(int index) {
  // @@protoc_insertion_point(field_mutable:RoadNetworkMessage.id_and_road)
  return id_and_road_.Mutable(index);
}
inline ::RoadTupleMessage* RoadNetworkMessage::add_id_and_road() {
  // @@protoc_insertion_point(field_add:RoadNetworkMessage.id_and_road)
  return id_and_road_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::RoadTupleMessage >&
RoadNetworkMessage::id_and_road() const {
  // @@protoc_insertion_point(field_list:RoadNetworkMessage.id_and_road)
  return id_and_road_;
}
inline ::google::protobuf::RepeatedPtrField< ::RoadTupleMessage >*
RoadNetworkMessage::mutable_id_and_road() {
  // @@protoc_insertion_point(field_mutable_list:RoadNetworkMessage.id_and_road)
  return &id_and_road_;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_road_5fnetwork_2eproto__INCLUDED
