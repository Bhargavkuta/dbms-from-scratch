#include "astra/version.hpp"

#include <cstdlib>
#include <iostream>

int main() {
  if (astra::version() != "0.1.0") {
    std::cerr << "Unexpected AstraDB version: " << astra::version() << '\n';
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

