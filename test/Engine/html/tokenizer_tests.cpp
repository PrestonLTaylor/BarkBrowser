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

TEST_CASE("Tokenizing comments returns an empty vector of html_tokens",
          "[html, tokenizer]") {
    SECTION(
        "Tokenizing an empty comment returns an empty vector of html_tokens") {
        // Arrange
        html::tokenizer tokenizer_1("<!-->");
        html::tokenizer tokenizer_2("<!--->");
        html::tokenizer tokenizer_3("<!---->");

        // Act
        const auto result_1 = tokenizer_1.tokenize();
        const auto result_2 = tokenizer_2.tokenize();
        const auto result_3 = tokenizer_3.tokenize();

        // Assert
        REQUIRE(result_1.size() == 0);
        REQUIRE(result_2.size() == 0);
        REQUIRE(result_3.size() == 0);
    }

    SECTION("Tokenizing a comment with normal text returns an empty vector of "
            "html_tokens") {
        // Arrange
        html::tokenizer tokenizer_1("<!-- -->");
        html::tokenizer tokenizer_2(
            "<!--My favorite operators are > and <!-->");
        html::tokenizer tokenizer_3("<!-- > -->");
        html::tokenizer tokenizer_4("<!-- -> -->");

        // Act
        const auto result_1 = tokenizer_1.tokenize();
        const auto result_2 = tokenizer_2.tokenize();
        const auto result_3 = tokenizer_3.tokenize();
        const auto result_4 = tokenizer_4.tokenize();

        // Assert
        REQUIRE(result_1.size() == 0);
        REQUIRE(result_2.size() == 0);
        REQUIRE(result_3.size() == 0);
        REQUIRE(result_4.size() == 0);
    }

    SECTION("Tokenizing a comment ending in --!> returns an empty vector of "
            "html_tokens") {
        // Arrange
        html::tokenizer tokenizer("<!-- --!>");

        // Act
        const auto result = tokenizer.tokenize();

        // Assert
        REQUIRE(result.size() == 0);
    }
}
