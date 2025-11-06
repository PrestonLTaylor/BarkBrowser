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

TEST_CASE("Tokenizing a symbol returns a vector of html_tokens with a "
          "token with the corrisponding type",
          "[html, tokenizer]") {
    const std::vector<std::string> symbols = {"<", ">", "/", "!", "=", ":",
                                              "[", "]", "&", ";", "#"};

    const std::vector<html::html_token_type> types = {
        html::html_token_type::less_than,
        html::html_token_type::greater_than,
        html::html_token_type::solidus,
        html::html_token_type::exclamation_mark,
        html::html_token_type::equals,
        html::html_token_type::colon,
        html::html_token_type::open_square_bracket,
        html::html_token_type::closed_square_bracket,
        html::html_token_type::ampersand,
        html::html_token_type::semicolon,
        html::html_token_type::number_sign};

    SECTION("Tokenizing a single symbol returns a vector of just that symbol "
            "and it's type") {
        for (int i = 0; i < symbols.size(); ++i) {
            // Arrange
            html::tokenizer tokenizer(symbols[i]);

            // Act
            const auto result = tokenizer.tokenize();

            // Assert
            REQUIRE(result.size() == 1);

            const auto &token = result.at(0);
            REQUIRE(token.type == types[i]);
            REQUIRE(token.value == symbols[i]);
        }
    }

    SECTION("Tokenizing every symbol in the same string returns a vector of "
            "each symbol and its type") {
        std::string symbols_string = "";
        for (int i = 0; i < symbols.size(); ++i) {
            symbols_string += symbols[i];
        }

        // Arrange
        html::tokenizer tokenizer(symbols_string);

        // Act
        const auto result = tokenizer.tokenize();

        // Assert
        REQUIRE(result.size() == symbols.size());

        for (int i = 0; i < symbols.size(); ++i) {
            const auto &token = result.at(i);
            REQUIRE(token.type == types[i]);
            REQUIRE(token.value == symbols[i]);
        }
    }
}
