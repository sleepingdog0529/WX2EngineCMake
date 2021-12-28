# ライブラリ名
set(PROJECT_NAME example)

# ライブラリに含めるソースファイル
set(
    SOURCES
    main.cpp
)

# オプション定義によって共有/静的ライブラリを切り替える
add_executable(${PROJECT_NAME} ${SOURCES})

include_directories(${CMAKE_SOURCE_DIR}/common/src)

include(GNUInstallDirs)

install(
    TARGETS ${PROJECT_NAME} 
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})