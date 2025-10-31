Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1
)

FetchContent_MakeAvailable(Catch2)

# Give visability to our source code for the tests
include_directories("../src/")

add_executable("BarkBrowser.Tests"
	"main.cpp"
	"Engine/html/tokenizer_tests.cpp"
	"../src/Engine/html/tokenizer.cpp"
)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

catch_discover_tests("BarkBrowser.Tests")

target_link_libraries("BarkBrowser.Tests" PRIVATE Catch2::Catch2WithMain)
