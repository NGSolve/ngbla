#include "exception.hpp"
#include "utils.hpp"

namespace ngcore
{
  Exception :: Exception(const std::string& s)
    : m_what(s) {}
  
  Exception :: Exception(const char* s)
    : m_what(s) {}


  void ThrowException(const std::string & s)
  {
    throw Exception (s);
  }
  
  void ThrowException(const char * s)
  {
    throw Exception (s);
  }
} // namespace ngcore

