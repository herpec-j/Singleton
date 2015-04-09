cmake_minimum_required(VERSION 2.6)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

project(Singleton)

if (MSVC)

else()
	include(CheckCXXCompilerFlag)
	CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
	CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
	if (COMPILER_SUPPORTS_CXX11)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	elseif (COMPILER_SUPPORTS_CXX0X)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	else ()
		message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
	endif ()
endif ()

set(Singleton_HDRS
	${PROJECT_SOURCE_DIR}/Singleton/Includes/Singleton/Singleton.hpp)

source_group(Includes FILES ${Singleton_HDRS})

set(Singleton_Private_HDRS
	${PROJECT_SOURCE_DIR}/Singleton/Includes/Singleton/Private/SpinLock.hpp)

source_group(Includes FILES ${Singleton_Private_HDRS})

set(HDRS
	${Singleton_HDRS}
	${Singleton_Private_HDRS})
	
set(SRCS
	${PROJECT_SOURCE_DIR}/Singleton/Sources/Test.cpp)

source_group(Sources FILES ${SRCS})

include_directories("$(PROJECT_SOURCE_DIR)/Singleton/Includes")

add_executable(SingletonTest ${SRCS} ${HDRS})

enable_testing()

add_test(SingletonUnitTests SingletonTest)

set_tests_properties(SingletonUnitTests
	PROPERTIES PASS_REGULAR_EXPRESSION "Success!")
