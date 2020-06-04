cmake_minimum_required (VERSION 3.17.0)
project (RenderTest)

set (VS_STARTUP_PROJECT ${PROJECT_NAME})

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/master/conan.cmake"
                 "${CMAKE_BINARY_DIR}/conan.cmake")
endif()
include(${CMAKE_BINARY_DIR}/conan.cmake)

set (CXX_STANDARD_REQUIRED ON)

conan_cmake_run(REQUIRES
	glfw/3.3.2@bincrafters/stable 
	glad/0.1.33
	glm/0.9.9.8
	
	nlohmann_json/3.7.3
	soil2/1.20@bincrafters/stable 
	freetype/2.10.1
	assimp/5.0.1
	
	bullet3/2.89
	imgui/1.76 
	lua/5.3.5
	sol2/2.20.6
	
	OPTIONS glad:gl_profile=core
	OPTIONS glad:gl_version=4.6
	OPTIONS glad:spec=gl
	OPTIONS glad:no_loader=False
	
	BASIC_SETUP CMAKE_TARGETS
	BUILD missing
)

# OpenGL
find_package (OpenGL REQUIRED)

# Library source files
file (GLOB_RECURSE SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/*.cxx
	${CMAKE_CURRENT_SOURCE_DIR}/source/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/source/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/*.hxx
)

add_executable (${PROJECT_NAME} ${SOURCE_FILES})

set_target_properties (${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 17
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE ${OPENGL_gl_LIBRARY}
	PRIVATE CONAN_PKG::glad
	PRIVATE CONAN_PKG::glfw
	PRIVATE CONAN_PKG::glm
	
	PRIVATE CONAN_PKG::nlohmann_json
	PRIVATE CONAN_PKG::soil2
	PRIVATE CONAN_PKG::freetype
	PRIVATE CONAN_PKG::assimp
	
	PRIVATE CONAN_PKG::bullet3
	PRIVATE CONAN_PKG::imgui
	PRIVATE CONAN_PKG::lua
	PRIVATE CONAN_PKG::sol2
)

target_include_directories(${PROJECT_NAME} 
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/source
	PRIVATE ${OPENGL_INCLUDE_DIR}
)

# Required for glm extensions
target_compile_definitions(${PROJECT_NAME}
	PRIVATE GLM_EXT_INCLUDED
)

# Copy runtime data
file (COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})