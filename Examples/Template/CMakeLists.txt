cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(Template)

include_directories(../../System/Sources/Buffer
					../../System/Sources/Common
					../../System/Sources/Compression
					../../System/Sources/FileSystem
					../../System/Sources/Log
					../../System/Sources/Network
					../../System/Sources/Options
					../../System/Sources/Serialization
					../../System/Sources/Stream
					../../System/Sources/String)
				

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	link_directories(../../External/zlib-1.2.7/lib/x64)
	link_directories(../../External/curl-7.29.0/bin/windows/x64)
else(CMAKE_SIZEOF_VOID_P EQUAL 8)
	link_directories(../../External/zlib-1.2.7/lib/x32)
	link_directories(../../External/curl-7.29.0/bin/windows/x32)
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)

add_executable(Template Sources/main.cpp)

if(UNIX)
target_link_libraries(Template 	System
								z)
else(UNIX)
target_link_libraries(Template 	System
								zlib
								WS2_32
								libcurl)
endif(UNIX)
