# NOTE: We set CMAKE_CXX_CLANG_TIDY in this CMakeLists as we only want the src to be clang-tidy'd when building
set (CMAKE_CXX_CLANG_TIDY
  clang-tidy;
  -format-style='file';
  -header-filter=${CMAKE_CURRENT_SOURCE_DIR};
)

add_subdirectory ("Engine")
