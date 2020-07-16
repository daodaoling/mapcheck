// Generated by gencpp from file gps_starneto/GPFPD.msg
// DO NOT EDIT!


#ifndef GPS_STARNETO_MESSAGE_GPFPD_H
#define GPS_STARNETO_MESSAGE_GPFPD_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace gps_starneto
{
template <class ContainerAllocator>
struct GPFPD_
{
  typedef GPFPD_<ContainerAllocator> Type;

  GPFPD_()
    : header()
    , GPSWeek(0)
    , GPSTime(0.0)
    , Heading(0.0)
    , Pitch(0.0)
    , Roll(0.0)
    , Lattitude(0.0)
    , Longitude(0.0)
    , Altitude(0.0)
    , Ve(0.0)
    , Vn(0.0)
    , Vu(0.0)
    , Baseline(0.0)
    , NSV1(0)
    , NSV2(0)
    , Status(0)
    , Cs(0)
    , utm_x(0.0)
    , utm_y(0.0)  {
    }
  GPFPD_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , GPSWeek(0)
    , GPSTime(0.0)
    , Heading(0.0)
    , Pitch(0.0)
    , Roll(0.0)
    , Lattitude(0.0)
    , Longitude(0.0)
    , Altitude(0.0)
    , Ve(0.0)
    , Vn(0.0)
    , Vu(0.0)
    , Baseline(0.0)
    , NSV1(0)
    , NSV2(0)
    , Status(0)
    , Cs(0)
    , utm_x(0.0)
    , utm_y(0.0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef int32_t _GPSWeek_type;
  _GPSWeek_type GPSWeek;

   typedef double _GPSTime_type;
  _GPSTime_type GPSTime;

   typedef double _Heading_type;
  _Heading_type Heading;

   typedef double _Pitch_type;
  _Pitch_type Pitch;

   typedef double _Roll_type;
  _Roll_type Roll;

   typedef double _Lattitude_type;
  _Lattitude_type Lattitude;

   typedef double _Longitude_type;
  _Longitude_type Longitude;

   typedef double _Altitude_type;
  _Altitude_type Altitude;

   typedef double _Ve_type;
  _Ve_type Ve;

   typedef double _Vn_type;
  _Vn_type Vn;

   typedef double _Vu_type;
  _Vu_type Vu;

   typedef double _Baseline_type;
  _Baseline_type Baseline;

   typedef int32_t _NSV1_type;
  _NSV1_type NSV1;

   typedef int32_t _NSV2_type;
  _NSV2_type NSV2;

   typedef int32_t _Status_type;
  _Status_type Status;

   typedef int32_t _Cs_type;
  _Cs_type Cs;

   typedef double _utm_x_type;
  _utm_x_type utm_x;

   typedef double _utm_y_type;
  _utm_y_type utm_y;





  typedef boost::shared_ptr< ::gps_starneto::GPFPD_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::gps_starneto::GPFPD_<ContainerAllocator> const> ConstPtr;

}; // struct GPFPD_

typedef ::gps_starneto::GPFPD_<std::allocator<void> > GPFPD;

typedef boost::shared_ptr< ::gps_starneto::GPFPD > GPFPDPtr;
typedef boost::shared_ptr< ::gps_starneto::GPFPD const> GPFPDConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::gps_starneto::GPFPD_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::gps_starneto::GPFPD_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace gps_starneto

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'gps_starneto': ['/home/dxx/av-system/catkin_ws/src/sensors/gps_starneto/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::gps_starneto::GPFPD_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::gps_starneto::GPFPD_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::gps_starneto::GPFPD_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::gps_starneto::GPFPD_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::gps_starneto::GPFPD_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::gps_starneto::GPFPD_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::gps_starneto::GPFPD_<ContainerAllocator> >
{
  static const char* value()
  {
    return "446283db465e7b7f5b8c7aa18e03016f";
  }

  static const char* value(const ::gps_starneto::GPFPD_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x446283db465e7b7fULL;
  static const uint64_t static_value2 = 0x5b8c7aa18e03016fULL;
};

template<class ContainerAllocator>
struct DataType< ::gps_starneto::GPFPD_<ContainerAllocator> >
{
  static const char* value()
  {
    return "gps_starneto/GPFPD";
  }

  static const char* value(const ::gps_starneto::GPFPD_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::gps_starneto::GPFPD_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
int32 GPSWeek\n\
float64 GPSTime\n\
float64 Heading\n\
float64 Pitch\n\
float64 Roll\n\
float64 Lattitude\n\
float64 Longitude\n\
float64 Altitude\n\
float64 Ve\n\
float64 Vn\n\
float64 Vu\n\
float64 Baseline\n\
int32 NSV1\n\
int32 NSV2\n\
int32 Status\n\
int32 Cs\n\
float64 utm_x\n\
float64 utm_y\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
";
  }

  static const char* value(const ::gps_starneto::GPFPD_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::gps_starneto::GPFPD_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.GPSWeek);
      stream.next(m.GPSTime);
      stream.next(m.Heading);
      stream.next(m.Pitch);
      stream.next(m.Roll);
      stream.next(m.Lattitude);
      stream.next(m.Longitude);
      stream.next(m.Altitude);
      stream.next(m.Ve);
      stream.next(m.Vn);
      stream.next(m.Vu);
      stream.next(m.Baseline);
      stream.next(m.NSV1);
      stream.next(m.NSV2);
      stream.next(m.Status);
      stream.next(m.Cs);
      stream.next(m.utm_x);
      stream.next(m.utm_y);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GPFPD_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::gps_starneto::GPFPD_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::gps_starneto::GPFPD_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "GPSWeek: ";
    Printer<int32_t>::stream(s, indent + "  ", v.GPSWeek);
    s << indent << "GPSTime: ";
    Printer<double>::stream(s, indent + "  ", v.GPSTime);
    s << indent << "Heading: ";
    Printer<double>::stream(s, indent + "  ", v.Heading);
    s << indent << "Pitch: ";
    Printer<double>::stream(s, indent + "  ", v.Pitch);
    s << indent << "Roll: ";
    Printer<double>::stream(s, indent + "  ", v.Roll);
    s << indent << "Lattitude: ";
    Printer<double>::stream(s, indent + "  ", v.Lattitude);
    s << indent << "Longitude: ";
    Printer<double>::stream(s, indent + "  ", v.Longitude);
    s << indent << "Altitude: ";
    Printer<double>::stream(s, indent + "  ", v.Altitude);
    s << indent << "Ve: ";
    Printer<double>::stream(s, indent + "  ", v.Ve);
    s << indent << "Vn: ";
    Printer<double>::stream(s, indent + "  ", v.Vn);
    s << indent << "Vu: ";
    Printer<double>::stream(s, indent + "  ", v.Vu);
    s << indent << "Baseline: ";
    Printer<double>::stream(s, indent + "  ", v.Baseline);
    s << indent << "NSV1: ";
    Printer<int32_t>::stream(s, indent + "  ", v.NSV1);
    s << indent << "NSV2: ";
    Printer<int32_t>::stream(s, indent + "  ", v.NSV2);
    s << indent << "Status: ";
    Printer<int32_t>::stream(s, indent + "  ", v.Status);
    s << indent << "Cs: ";
    Printer<int32_t>::stream(s, indent + "  ", v.Cs);
    s << indent << "utm_x: ";
    Printer<double>::stream(s, indent + "  ", v.utm_x);
    s << indent << "utm_y: ";
    Printer<double>::stream(s, indent + "  ", v.utm_y);
  }
};

} // namespace message_operations
} // namespace ros

#endif // GPS_STARNETO_MESSAGE_GPFPD_H
