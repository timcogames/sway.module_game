# Мета-информация о проекте
set(META_GAME_EXAMPLE_PRJNAME "module_game_example_fsm")
set(META_GAME_EXAMPLE_EXENAME "exe${META_GAME_EXAMPLE_PRJNAME}")

project(${META_GAME_EXAMPLE_PRJNAME} CXX)

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# include_directories("${MODULE_GRAPHICS_DIR}/submodules/sway.module_platform-glx11/lib/include")

# Получаем пути ко всем исходникам с тестами
file(GLOB MODULE_GAME_EXAMPLE_SOURCE ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(${META_GAME_EXAMPLE_EXENAME} ${MODULE_GAME_EXAMPLE_SOURCE})

target_link_libraries(${META_GAME_EXAMPLE_EXENAME} libmodule_game libmodule_graphics libmodule_platform_glx11 libmodule_ois_x11 libmodule_core)
