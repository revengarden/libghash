cmake_minimum_required(VERSION 3.5)
project(libghash C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(GHASH_DEBUG "Setting build type to debug." OFF)
option(GHASH_BUILD_SHARED "Build shared library" ON)
option(GHASH_BUILD_STATIC "Build static library" ON)
option(GHASH_BUILD_OBJECT "Build object library" ON)
option(GHASH_BUILD_TESTS "Build test executables" ON)

include(CheckIncludeFile)

set(version_major 1)
set(version_minor 0)
set(version_patch 0)
set(version ${version_major}.${version_minor}.${version_patch})
set(PACKAGE_VERSION ${version})

set(sources src/rshash.c src/pjw.c)

# -----
# Build type
#------

message(STATUS "")
if (NOT CMAKE_BUILD_TYPE)
  if (GHASH_DEBUG)
    message(STATUS "No build type selected, default to: Debug")
    set(CMAKE_BUILD_TYPE "Debug")
  else()
    message(STATUS "No build type selected, default to: Release")
    set(CMAKE_BUILD_TYPE "Release")
  endif()
endif()

# -------------------
# Check system files
# -------------------

CHECK_INCLUDE_FILE("stdint.h" HAVE_STDINT_H)
if(HAVE_STDINT_H)
	list(APPEND defines HAVE_STDINT_H)
endif()

CHECK_INCLUDE_FILE("stdio.h" HAVE_STDIO_H)
if(HAVE_STDIO_H)
	list(APPEND defines HAVE_STDIO_H)
endif()

CHECK_INCLUDE_FILE("stddef.h" HAVE_STDDEF_H)
if(HAVE_STDDEF_H)
	list(APPEND defines HAVE_STDDEF_H)
endif()

CHECK_INCLUDE_FILE("stdlib.h" HAVE_STDLIB_H)
if(HAVE_STDLIB_H)
	list(APPEND defines HAVE_STDLIB_H)
endif()

CHECK_INCLUDE_FILE("string.h" HAVE_STRING_H)
if(HAVE_STRING_H)
	list(APPEND defines HAVE_STRING_H)
endif()

CHECK_INCLUDE_FILE("errno.h" HAVE_ERRNO_H)
if(HAVE_ERRNO_H)
	list(APPEND defines HAVE_ERRNO_H)
endif()

# --
# Install info
# --
set(install_libdir "${CMAKE_INSTALL_LIBDIR}")
if (GHASH_INSTALL_TOPLEVEL)
  set(install_objdir     "${CMAKE_INSTALL_LIBDIR}")
  set(install_incdir     "${CMAKE_INSTALL_INCLUDEDIR}")
else()
  set(install_objdir     "${CMAKE_INSTALL_LIBDIR}/ghash-${version}")
  set(install_incdir     "${CMAKE_INSTALL_INCLUDEDIR}/ghash-${version}")
endif()

set(base_name "ghash")
set(cflags ${CMAKE_C_FLAGS})
set(libraries "")

if(GHASH_BUILD_SHARED)
  list(APPEND build_targets "shared")
endif()
if(GHASH_BUILD_STATIC)
  list(APPEND build_targets "static")
endif()
if(GHASH_BUILD_OBJECT)
  list(APPEND build_targets "object")
endif()
if(GHASH_BUILD_TESTS)
  list(APPEND build_targets "tests")
endif()

message(STATUS "")
message(STATUS "Library base name: ${base_name}")
message(STATUS "Version          : ${version}")
message(STATUS "Build type       : ${CMAKE_BUILD_TYPE}")
message(STATUS "C Compiler       : ${CMAKE_C_COMPILER}")
message(STATUS "Compiler flags   : ${cflags}")
message(STATUS "Compiler defines : ${defines}")
message(STATUS "Link libraries   : ${libraries}")
message(STATUS "Build targets    : ${build_targets}")
message(STATUS "")

# ------------
# Build target
# ------------

if(GHASH_BUILD_SHARED)
	add_library(ghash SHARED ${sources})
	set_target_properties(ghash PROPERTIES VERSION ${version} SOVERSION ${version_major} OUTPUT_NAME ${base_name})
	target_compile_definitions(ghash PRIVATE ${defines} GHASH_SHARED_LIB GHASH_SHARED_LIB_EXPORT)
	target_compile_options(ghash PRIVATE ${cflags})
	target_link_libraries(ghash PRIVATE ${libraries})
  target_include_directories(ghash PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:${install_incdir}>
  )
endif()

if (GHASH_BUILD_STATIC)
  add_library(ghash-static STATIC ${sources})
  set_property(TARGET ghash-static PROPERTY POSITION_INDEPENDENT_CODE ON)
	target_compile_definitions(ghash-static PRIVATE ${defines} GHASH_STATIC_LIB)
  target_compile_options(ghash-static PRIVATE ${cflags})
  target_link_libraries(ghash-static PRIVATE ${libraries})
  target_include_directories(ghash-static PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:${install_incdir}>
  )
  if(WIN32)
    string(REPLACE "ghash" "ghash-static" output_name ${base_name})
    set_target_properties(ghash-static PROPERTIES OUTPUT_NAME ${output_name})
  else()
    set_target_properties(ghash-static PROPERTIES OUTPUT_NAME ${base_name})
  endif()
endif()

if(GHASH_BUILD_TESTS)
	include(CTest)
	enable_testing()

	foreach(TEST_NAME pjwhash rshash)
		add_executable(ghash-test-${TEST_NAME} ${CMAKE_SOURCE_DIR}/tests/test-${TEST_NAME}.c)
		target_compile_definitions(ghash-test-${TEST_NAME} PRIVATE ${defines})
    target_compile_options(ghash-test-${TEST_NAME} PRIVATE ${cflags})
		target_include_directories(ghash-test-${TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(ghash-test-${TEST_NAME} PRIVATE ghash ${libraries})

    add_test(NAME test-${TEST_NAME} COMMAND ghash-test-${TEST_NAME})
  endforeach()
endif()
