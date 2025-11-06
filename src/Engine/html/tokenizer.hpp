#pragma once
#include <string_view>
#include <unordered_map>
#include <vector>

namespace html {

enum class html_token_type {
    less_than,
    greater_than,
    solidus,
    exclamation_mark,
    equals,
    colon,
    open_square_bracket,
    closed_square_bracket,
    ampersand,
    semicolon,
    number_sign
};

struct html_token {
public:
    html_token_type type;
    std::string_view value;
};

class tokenizer {
public:
    tokenizer(std::string_view html_to_tokenize) noexcept
        : m_html(html_to_tokenize), m_html_index(0) {}

    std::vector<html_token> tokenize();

private:
    void reset_tokenizer_state() noexcept;

    [[nodiscard]] char peek() const;
    std::string_view consume();
    [[nodiscard]] bool
    can_consume(std::uint32_t amount_to_consume = 1) const noexcept;
    void skip(std::uint32_t to_skip = 1) noexcept;
    bool skip_until_matches(std::string_view to_match);
    bool matches(std::string_view to_match) const;

    void skip_comments();
    [[nodiscard]] bool is_comment() const;
    void skip_to_end_of_comment();

    [[nodiscard]] bool is_whitespace() const;
    void skip_ascii_whitespace();

    [[nodiscard]] bool is_symbol() const;
    [[nodiscard]] html_token tokenize_symbol();

    std::string_view m_html;
    std::uint32_t m_html_index;

    const inline static std::unordered_map<char, html_token_type>
        s_token_char_to_type{
            {'<', html_token_type::less_than},
            {'>', html_token_type::greater_than},
            {'/', html_token_type::solidus},
            {'!', html_token_type::exclamation_mark},
            {'=', html_token_type::equals},
            {':', html_token_type::colon},
            {'[', html_token_type::open_square_bracket},
            {']', html_token_type::closed_square_bracket},
            {'&', html_token_type::ampersand},
            {';', html_token_type::semicolon},
            {'#', html_token_type::number_sign},
        };
};

} // namespace html