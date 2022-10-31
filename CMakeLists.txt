# Проверяем версию CMake
cmake_minimum_required(VERSION 3.14.3 FATAL_ERROR)

# Мета-информация о проекте
set(META_PROJECT_NAME module_game)
set(META_LIB_NAME lib${META_PROJECT_NAME})
set(META_VERSION_MAJOR 0)
set(META_VERSION_MINOR 4)
set(META_VERSION_PATCH 8)
set(META_VERSION ${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH})

# Опции сборки
option(BUILD_SHARED "Build shared library" OFF)
option(ENABLE_COVERAGE "Enable coverage builds" OFF)
option(ENABLE_TESTS "Enable test builds" OFF)

project(${META_PROJECT_NAME) CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(ENABLE_COVERAGE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# Определяем каталог вывода по умолчанию
if(CMAKE_BUILD_TYPE MATCHES Debug)
	set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/dbg)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/dbg)
else()
	set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
endif()

set(MODULE_GAME_DIR ${CMAKE_CURRENT_LIST_DIR})

# Добавляем пути для поиска хедеров
include_directories(${MODULE_GAME_DIR}/include)
include_directories(${MODULE_GAME_DIR}/modules/sway.module_core/include)
include_directories(${MODULE_GAME_DIR}/modules/sway.module_math/include)
include_directories(${MODULE_GAME_DIR}/modules/sway.module_graphics/include)
include_directories(${MODULE_GAME_DIR}/modules/sway.module_platform-glx11/include)
include_directories(${MODULE_GAME_DIR}/modules/sway.module_ois-x11/include)

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_GAME_HEADERS ${MODULE_GAME_DIR}/include/*.*)
file(GLOB_RECURSE MODULE_GAME_SOURCE ${MODULE_GAME_DIR}/src/*.*)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_NO_SYSTEM_PATHS TRUE)
set(BOOST_COMPONENTS system filesystem)
set(BOOST_INCLUDEDIR "${BOOST_ROOT}/")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")

find_package(Boost 1.69.0 REQUIRED COMPONENTS ${BOOST_COMPONENTS})
if(NOT Boost_FOUND)
	message(FATAL_ERROR "Fatal error: Boost (version >= 1.69.0) required.")
else()
	message(STATUS "Boost includes: ${BOOST_INCLUDEDIR}")
	message(STATUS "Boost libs: ${BOOST_LIBRARYDIR}")

	include_directories(${BOOST_INCLUDEDIR})
endif()

if(BUILD_SHARED)
	# Добавляем в проект цель для сборки динамической библиотеки
	add_library(${META_LIB_NAME} SHARED ${MODULE_GAME_SOURCE})
	set_target_properties(${META_LIB_NAME} PROPERTIES OUTPUT_NAME ${META_PROJECT_NAME})
	set_target_properties(${META_LIB_NAME} PROPERTIES PREFIX "")
	set_target_properties(${META_LIB_NAME} PROPERTIES SUFFIX ".so.${META_VERSION}")
else()
	# Добавляем в проект цель для сборки статической библиотеки
	add_library(${META_LIB_NAME} STATIC ${MODULE_GAME_SOURCE})
	set_target_properties(${META_LIB_NAME} PROPERTIES OUTPUT_NAME ${META_PROJECT_NAME})
	set_target_properties(${META_LIB_NAME} PROPERTIES PREFIX "")
	set_target_properties(${META_LIB_NAME} PROPERTIES SUFFIX ".a.${META_VERSION}")
endif()

target_link_libraries(${META_LIB_NAME} GL X11 ${BOOST_LIBRARIES})

# Добавляем построение тестов
if(ENABLE_TESTS)
	message(STATUS "Tests have been enabled")
endif()
