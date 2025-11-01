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

TEST_CASE("Tokenizing white space returns an empty vector of html_tokens",
          "[html, tokenizer]") {
    SECTION("Tokenizing a U+0009 TAB returns an empty vector of html_tokens") {
        // Arrange
        html::tokenizer tokenizer("\u0009");

        // Act
        const auto result = tokenizer.tokenize();

        // Assert
        REQUIRE(result.size() == 0);
    }

    SECTION("Tokenizing a U+000A LF returns an empty vector of html_tokens") {
        // Arrange
        html::tokenizer tokenizer("\u000A");

        // Act
        const auto result = tokenizer.tokenize();

        // Assert
        REQUIRE(result.size() == 0);
    }

    SECTION("Tokenizing a U+000C FF returns an empty vector of html_tokens") {
        // Arrange
        html::tokenizer tokenizer("\u000C");

        // Act
        const auto result = tokenizer.tokenize();

        // Assert
        REQUIRE(result.size() == 0);
    }

    SECTION("Tokenizing a U+000D CR returns an empty vector of html_tokens") {
        // Arrange
        html::tokenizer tokenizer("\u000D");

        // Act
        const auto result = tokenizer.tokenize();

        // Assert
        REQUIRE(result.size() == 0);
    }

    SECTION(
        "Tokenizing a U+0020 SPACE returns an empty vector of html_tokens") {
        // Arrange
        html::tokenizer tokenizer("\u0020");

        // Act
        const auto result = tokenizer.tokenize();

        // Assert
        REQUIRE(result.size() == 0);
    }

    SECTION("Tokenizing a combination of ascii whitespace returns an empty "
            "vector of html_tokens") {
        // Arrange
        html::tokenizer tokenizer("\t\u0009\n\u000A\f\u000C\r\u000D \u0020");

        // Act
        const auto result = tokenizer.tokenize();

        // Assert
        REQUIRE(result.size() == 0);
    }
}
