cmake_minimum_required(VERSION 3.15)
project(Soundboard)

set(CMAKE_CXX_STANDARD 17)

# ---- Find packages installed by vcpkg ----
find_package(SDL2 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# ---- Your executable ----
add_executable(Soundboard
    src/core/main.cpp
)

# ---- Link libraries ----
target_link_libraries(Soundboard PRIVATE
    SDL2::SDL2
    nlohmann_json::nlohmann_json
    imgui::imgui
)