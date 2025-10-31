#include "../../../src/Engine/html/tokenizer.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Tokenizing an empty string returns an empty vector of html_tokens",
          "[html, tokenizer]") {
    // Arrange
    html::tokenizer tokenizer("");

    // Act
    const auto result = tokenizer.tokenize();

    REQUIRE(result.size() == 0);
}
