cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(System)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY $(CMAKE_CURRENT_BINARY_DIR)/../Libs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $(CMAKE_CURRENT_BINARY_DIR)/../Libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $(CMAKE_CURRENT_BINARY_DIR)/../Bin)

# settings paths where IDE will look for headers upon including

include_directories(		Sources/Buffer
							Sources/Common
							Sources/Compression
							Sources/FileSystem
							Sources/Log
							Sources/Network
							Sources/Options
							Sources/Serialization
							Sources/Stream
							Sources/String
							../External
							../External/zlib-1.2.7
							../External/curl-7.29.0/include)
					
# setting paths to files to be placed in IDE filters
					
set(BUFFER_SOURCES			Sources/Buffer/Buffer.h
							Sources/Buffer/Buffer.cpp)
					
set(COMMON_SOURCES			Sources/Common/Config.h
							Sources/Common/Defines.h
							Sources/Common/Endianness.h
							Sources/Common/System.h
							Sources/Common/Timer.h
							Sources/Common/Timer.cpp
							Sources/Common/Types.h)
					
set(COMPRESSION_SOURCES		Sources/Compression/ICompressor.h
							Sources/Compression/ZLIBCompressor.h
							Sources/Compression/ZLIBCompressor.cpp)
							
set(CRYPTOGRAPHY_SOURCES	Sources/Cryptography/SHA1.h
							Sources/Cryptography/SHA1.cpp)
						
set(FILESYSTEM_SOURCES		Sources/FileSystem/Directory.h
							Sources/FileSystem/Directory.cpp
							Sources/FileSystem/File.h
							Sources/FileSystem/File.cpp
							Sources/FileSystem/FileSystem.h
							Sources/FileSystem/FileSystem.cpp)
						
set(LOG_SOURCES				Sources/Log/Log.h
							Sources/Log/Log.cpp)
						
set(NETWORK_SOURCES			Sources/Network/HTTPFileDownloader.h
							Sources/Network/HTTPFileDownloader.cpp)
							
set(OPTIONS_SOURCES			Sources/Options/Options.h
							Sources/Options/Options.cpp)
						
set(SERIALIZATION_SOURCES	Sources/Serialization/ISerializable.h)

set(STREAM_SOURCES			Sources/Stream/Stream.h
							Sources/Stream/Stream.cpp)
							
set(STRING_SOURCES			Sources/String/Tokenization.h
							Sources/String/Tokenization.cpp
							Sources/String/Utils.h
							Sources/String/Utils.cpp)
							
set(SYSTEM_SOURCES			${BUFFER_SOURCES}
							${COMMON_SOURCES}
							${COMPRESSION_SOURCES}
							${CRYPTOGRAPHY_SOURCES}
							${FILESYSTEM_SOURCES}
							${LOG_SOURCES}
							${NETWORK_SOURCES}
							${OPTIONS_SOURCES}
							${SERIALIZATION_SOURCES}
							${STREAM_SOURCES}
							${STRING_SOURCES})
							
# setting Sources groups for IDE

source_group(Buffer			FILES ${BUFFER_SOURCES})
source_group(Common			FILES ${COMMON_SOURCES})
source_group(Compression	FILES ${COMPRESSION_SOURCES})
source_group(Cryptography	FILES ${CRYPTOGRAPHY_SOURCES})
source_group(FileSystem		FILES ${FILESYSTEM_SOURCES})
source_group(Log			FILES ${LOG_SOURCES})
source_group(Network		FILES ${NETWORK_SOURCES})
source_group(Options		FILES ${OPTIONS_SOURCES})
source_group(Serialization	FILES ${SERIALIZATION_SOURCES})
source_group(Stream			FILES ${STREAM_SOURCES})
source_group(String			FILES ${STRING_SOURCES})

add_library(System STATIC ${SYSTEM_SOURCES})