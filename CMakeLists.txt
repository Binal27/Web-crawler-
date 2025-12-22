cmake_minimum_required(VERSION 3.10)
project(WebCrawlerPageRank)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GUMBO REQUIRED gumbo)

include_directories(${GUMBO_INCLUDE_DIRS})

add_executable(webcrawler
    src/main.cpp
    src/crawler.cpp
    src/database.cpp
    src/pagerank.cpp
)

target_link_libraries(webcrawler
    CURL::libcurl
    ${GUMBO_LIBRARIES}
    sqlite3
)
