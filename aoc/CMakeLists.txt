project(aoc)

include_directories(aoc src/)

file(GLOB_RECURSE SourceFiles src/*.cpp)
add_executable(aoc ${SourceFiles})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  target_link_libraries(aoc -lc++)

  if (UNIX)
    target_link_libraries(aoc -lm)
  endif()
endif()
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  target_link_libraries(qix -lstdc++)
  target_link_libraries(qix -lm)
endif()
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set_property(TARGET qix PROPERTY CXX_STANDARD 17)
endif()

file(GLOB_RECURSE SourceFiles src/*)
