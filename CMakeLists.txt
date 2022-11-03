# Проверяем версию CMake
cmake_minimum_required(VERSION 3.14.3 FATAL_ERROR)

include("${CMAKE_CURRENT_SOURCE_DIR}/submodules/sway.module_core/cmakehelpers/custom_enable_cxx17.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/submodules/sway.module_core/cmakehelpers/custom_add_subdirectory.cmake")

# Мета-информация о проекте
set(META_GAME_PRJNAME "module_game")
set(META_GAME_LIBNAME "lib${META_GAME_PRJNAME}")
set(META_GAME_VERSION_MAJOR 0)
set(META_GAME_VERSION_MINOR 4)
set(META_GAME_VERSION_PATCH 8)
set(META_GAME_VERSION ${META_GAME_VERSION_MAJOR}.${META_GAME_VERSION_MINOR}.${META_GAME_VERSION_PATCH})

# Опции сборки
option(MODULE_GAME_SHARED_LIB "Build shared library" OFF)
option(MODULE_GAME_ENABLE_COVERAGE "Enable coverage builds" OFF)
option(MODULE_GAME_ENABLE_TESTS "Enable test builds" OFF)
option(MODULE_GAME_ENABLE_EXAMPLES "Enable example builds" OFF)

project(${META_GAME_PRJNAME} VERSION ${META_GAME_VERSION} LANGUAGES CXX)

# Подмодули
custom_add_subdirectory("libmodule_core" submodules/sway.module_core)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(ENABLE_COVERAGE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# Определяем каталог вывода по умолчанию
if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/dbg")
  set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/dbg")
else()
  set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")
  set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")
endif()

set(SYSTEM_X11_INCLUDE_DIRS "/opt/X11/include")
set(SYSTEM_X11_LIBRARY_DIRS "/opt/X11/lib")
set(MODULE_GAME_DIR ${CMAKE_CURRENT_LIST_DIR})

# Добавляем пути для поиска хедеров
include_directories("${SYSTEM_X11_INCLUDE_DIRS}")
include_directories("${MODULE_GAME_DIR}/include")
include_directories("${MODULE_GAME_DIR}/submodules/sway.module_core/lib/include")
include_directories("${MODULE_GAME_DIR}/submodules/sway.module_math/lib/include")
include_directories("${MODULE_GAME_DIR}/submodules/sway.module_graphics/lib/include")
include_directories("${MODULE_GAME_DIR}/submodules/sway.module_graphics/submodules/sway.module_gapi/include")
include_directories("${MODULE_GAME_DIR}/submodules/sway.module_platform-glx11/lib/include")
include_directories("${MODULE_GAME_DIR}/submodules/sway.module_ois-x11/lib/include")

find_package(OpenGL REQUIRED)
find_library(GLUT_glut_LIBRARY GLUT DOC "GLUT library for OSX")

link_directories("${SYSTEM_X11_LIBRARY_DIRS}")

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_GAME_HEADERS "${MODULE_GAME_DIR}/include/*.*")
file(GLOB_RECURSE MODULE_GAME_SOURCES "${MODULE_GAME_DIR}/src/*.*")

if(MODULE_GAME_SHARED_LIB)
  # Добавляем в проект цель для сборки динамической библиотеки
  add_library(${META_GAME_LIBNAME} SHARED ${MODULE_GAME_SOURCES})
  set_target_properties(${META_GAME_LIBNAME} PROPERTIES OUTPUT_NAME ${META_GAME_PRJNAME})
  set_target_properties(${META_GAME_LIBNAME} PROPERTIES PREFIX "")
  set_target_properties(${META_GAME_LIBNAME} PROPERTIES SUFFIX ".so.${META_GAME_VERSION}")
else()
  # Добавляем в проект цель для сборки статической библиотеки
  add_library(${META_GAME_LIBNAME} STATIC ${MODULE_GAME_SOURCES})
  set_target_properties(${META_GAME_LIBNAME} PROPERTIES OUTPUT_NAME ${META_GAME_PRJNAME})
  set_target_properties(${META_GAME_LIBNAME} PROPERTIES PREFIX "")
  set_target_properties(${META_GAME_LIBNAME} PROPERTIES SUFFIX ".a.${META_GAME_VERSION}")
endif()

custom_enable_cxx17(${META_GAME_LIBNAME})
target_link_libraries(${META_GAME_LIBNAME} GL X11)

# Добавляем построение тестов
if(MODULE_GAME_ENABLE_TESTS)
  message(STATUS "Tests have been enabled")
endif()

# Добавляем построение примеров
if (MODULE_GAME_ENABLE_EXAMPLES)
  message(STATUS "Examples have been enabled")

  if (NOT TARGET module_platform_glx11)
    add_subdirectory("submodules/sway.module_platform-glx11")
  endif ()

  if (NOT TARGET module_graphics)
    add_subdirectory("submodules/sway.module_graphics")
  endif ()

  add_subdirectory("examples/demo")
endif ()
