cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

# Set to true to release game. Delete out folder and recompile after changing
option(PRODUCTION_BUILD "Make this a production build" OFF)

# Set to true to save as a .pyd or .so for modding
option(MODDING_BUILD "Build as a .pyd or .so (dependent on OS) to mod using Python." OFF)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) # Link time optimization

if(MSVC)
	add_compile_options(/arch:AVX2) # Make sure SIMD optimizations take place
endif()

project(Minecraft)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# remove unused libraries here and in thirdparty
add_subdirectory(thirdparty/glfw-3.3.2)			# window opener
add_subdirectory(thirdparty/glad)				# opengl loader
add_subdirectory(thirdparty/stb_image)			# image loader
add_subdirectory(thirdparty/stb_truetype)		# loading ttf files
#add_subdirectory(thirdparty/enet-1.3.17)		# networking
add_subdirectory(thirdparty/glm)				# math
add_subdirectory(thirdparty/imgui-docking)		# ui
add_subdirectory(thirdparty/pybind11)           # modding and scripting

# MY_SOURCES contains all sources. All are added with macro
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

if (MODDING_BUILD)
	add_library("${CMAKE_PROJECT_NAME}" SHARED "${MY_SOURCES}")
else()
	add_executable("${CMAKE_PROJECT_NAME}")
endif()

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 17)

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC GLFW_INCLUDE_NONE=1) 

if(PRODUCTION_BUILD)
	# setup RESOURCES_PATH macro
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/") 

	# remove the option to debug asserts.
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1) 
else()
	# get RESOURCES_PATH macro in IDE during development
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0) 
endif()

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES})

if(MSVC)
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)

	#set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") # no console
	
	#set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebug<$<CONFIG:Debug>:Debug>")
	#set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
endif()

# remove unused libraries from here too

#target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glm glfw 
#	glad stb_image stb_truetype imgui enet pybind11::module)

# enet not working yet on linux for some reason
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glm glfw 
	glad stb_image stb_truetype imgui pybind11::module)

if (MODDING_BUILD)
	if(WIN32)
		set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES SUFFIX ".pyd")
	else()
		set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES SUFFIX ".so")
	endif()
endif()
