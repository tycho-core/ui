cmake_minimum_required (VERSION 2.8)

set(link_libs "")

if(ty_platform MATCHES "pc")
	include_directories("${CMAKE_SOURCE_DIR}/3rdparty/pc/dx9")
	link_directories("${CMAKE_SOURCE_DIR}/3rdparty/pc/dx9/lib")
	set(link_libs "d3dx9;d3d9;dxguid;xinput")
endif()

# layout.cpp includes flex generated code which emits warnings. Disable these
# only for this file.
ty_clang_file_disable_warnings(layout.cpp "unused-label;unused-variable")

tycho_add_library(ui "tyengine;tyinput;${link_libs}" "libs")



