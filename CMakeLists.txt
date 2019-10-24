cmake_minimum_required (VERSION 3.12.0)
project (RenderTest)

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/master/conan.cmake"
                 "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
			 
conan_cmake_run(REQUIRES
	glfw/3.3@bincrafters/stable 
	glm/0.9.9.5@g-truc/stable
	lua/5.3.4@zimmerk/stable 
	jsonformoderncpp/3.1.2@vthiery/stable
	pugixml/1.10@bincrafters/stable
	sqlite3/3.29.0@bincrafters/stable
	sdl2_image/2.0.5@bincrafters/stable
	glad/0.1.29@bincrafters/stable 
	
	OPTIONS glad:profile=core
	OPTIONS glad:api_type=gl
	OPTIONS glad:api_version=4.6
	OPTIONS glad:spec=gl
	OPTIONS glad:no_loader=False
	
	BASIC_SETUP CMAKE_TARGETS
	BUILD missing
)

set (CXX_STANDARD_REQUIRED ON)

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
	PUBLIC CONAN_PKG::glm
	PUBLIC CONAN_PKG::sqlite3
	PUBLIC CONAN_PKG::jsonformoderncpp
	PUBLIC CONAN_PKG::pugixml
	PUBLIC CONAN_PKG::lua
	PUBLIC CONAN_PKG::sdl2_image

	PUBLIC ${OPENGL_gl_LIBRARY}
	PUBLIC CONAN_PKG::glfw
	PUBLIC CONAN_PKG::glad
)

target_include_directories(${PROJECT_NAME} 
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/source
	PRIVATE ${OPENGL_INCLUDE_DIR}
)

target_compile_definitions(${PROJECT_NAME} 
	PUBLIC -DGLM_ENABLE_EXPERIMENTAL
)