# ライブラリ名
set(PROJECT_NAME wx2common)

# ライブラリに含めるヘッダファイル
set(
    HEADERS
    layer.h
    layer_stack.h
    window_property.h
    assertion.h
    com_exception.h
    log.h
    runtime_error.h
    event_dispatcher.h
    file_dialog.h
    hash.h
    macro.h
    safe_release.h
    string_helper.h
    thread_pool.h
    timer.h
)

# ライブラリに含めるソースファイル
set(
    SOURCES
    layer_stack.cpp
    assertion.cpp
    log.cpp
    thread_pool.cpp
)

# オプション定義によって共有/静的ライブラリを切り替える
if (WX2_BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${SOURCES}) 
else()
    add_library(${PROJECT_NAME} STATIC ${SOURCES})
endif()

# ライブラリに含むソースファイルを設定
target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${SOURCES}
    ${HEADERS}
)

# ライブラリに含むヘッダファイルのディレクトリを設定
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

include(GNUInstallDirs)

# .libのインストール先を指定
install(
    TARGETS ${PROJECT_NAME} 
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBRARYDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBRARYDIR}
)

# ヘッダファイルのインストール先を指定
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})