#include "astra/version.hpp"

#ifndef ASTRA_VERSION_STRING
#define ASTRA_VERSION_STRING "0.0.0-unknown"
#endif

namespace astra {

std::string_view version() noexcept {
  return ASTRA_VERSION_STRING;
}

}  // namespace astra

