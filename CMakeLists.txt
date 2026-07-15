cmake_minimum_required(VERSION 3.15)
project(CypherMemScan VERSION 1.0.0 LANGUAGES CXX)

# Thiết lập chuẩn C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Định nghĩa cấu trúc thư mục
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Chỉ định thư mục chứa file Header
include_directories(${INC_DIR})

# (Tạm thời để trống phần executable, chúng ta sẽ thêm file nguồn vào sau)
# Khai báo file mã nguồn
set(SOURCES
    ${SRC_DIR}/Memory.cpp
)

# Tạo thư viện tĩnh (Static Library) cho Core Engine
add_library(MemEngineCore STATIC ${SOURCES})
