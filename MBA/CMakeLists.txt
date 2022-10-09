add_library(MBA SHARED MBA.cpp)

# Allow undefined symbols in shared objects on Darwin (this is the default
# behaviour on Linux)
target_link_libraries(MBA
  "$<$<PLATFORM_ID:Darwin>:-undefined dynamic_lookup>")