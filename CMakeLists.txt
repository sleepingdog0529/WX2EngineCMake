# CMakeの最小要求バージョン
cmake_minimum_required(VERSION 3.9)

# in-sourceビルド防止
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds are not allowed.")
endif()

# プロジェクトを作成
project(
	WX2Engine 
	VERSION 1.0.0
	DESCRIPTION "Game engine written in modern C++."
	LANGUAGES CXX)
message("Project name: ${PROJECT_NAME}")
message("Project version: ${PROJECT_VERSION}")

# 共有ライブラリとして生成するかのオプション
option(WX2_BUILD_SHARED_LIBS "Build as a shared library." OFF)

# 出力先ディレクトリを指定
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib") # .lib
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin") # .dll
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin") # .exe
set(CMAKE_PDB_OUTPUT_DIRECTORY     "${PROJECT_BINARY_DIR}/bin") # .pdb

# C++23を標準バージョンに指定
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Boostディレクトリを環境変数から取得
set(Boost_ROOT $ENV{Boost_ROOT})
set(Boost_LIBRARYDIR $ENV{Boost_LIBRARYDIR})
set(Boost_INCLUDEDIR $ENV{Boost_INCLUDEDIR})

if(WIN32 AND NOT Boost_ROOT)
	message(WARNING "Please set the BOOST_ROOT environment variable." )
endif()

# Boostライブラリを探す
set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON) 
set(Boost_USE_STATIC_RUNTIME ON) 
set(Boost_ARCHITECTURE "-x64") 
set(Boost_DEBUG ON) 
find_package(Boost)

# Boostをリンク
include_directories(${Boost_INCLUDEDIR})
file(GLOB BOOST_LIBS ${Boost_LIBRARYDIR}/*.lib)
link_libraries(${BOOST_LIBS})

include_directories(
	${CMAKE_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/external/spdlog/include
	${CMAKE_SOURCE_DIR}/external/cereal/include
)

# デバッグビルド時の.libのポストフィックス
set(CMAKE_DEBUG_POSTFIX "d")

# インクルードファイルのインストール位置を変更
set(CMAKE_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_INCLUDEDIR}/wx2")

# サブプロジェクトを含めます。
add_subdirectory(wx2)
add_subdirectory(example)