#pragma once
#include <string_view>
#include <vector>

namespace html {

enum class html_token_type { open_tag, close_tag };

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

    [[nodiscard]] char peek();
    char consume();
    [[nodiscard]] bool can_consume() noexcept;

    void skip_ascii_whitespace();
    [[nodiscard]] bool is_whitespace();

    std::string_view m_html;
    std::uint32_t m_html_index;
};

} // namespace html