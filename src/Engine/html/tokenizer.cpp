#include "tokenizer.hpp"
#include "../../Common/not_implemented_exception.hpp"
#include <format>

namespace html {

// https://html.spec.whatwg.org/#writing
std::vector<html_token> tokenizer::tokenize() {
    reset_tokenizer_state();

    std::vector<html_token> html_tokens;

    // TODO: 1. Optionally, a single U+FEFF BYTE ORDER MARK (BOM) character.

    // 2. Any number of (TODO: comments and) ASCII whitespace.
    skip_ascii_whitespace();

    while (can_consume()) {
        throw not_implemented_exception(std::format(
            "Found '{}', tokenization of character is not yet implemented",
            m_html[m_html_index]));
    }

    return html_tokens;
}

void tokenizer::reset_tokenizer_state() noexcept { m_html_index = 0; }

char tokenizer::peek() { return m_html[m_html_index]; }

char tokenizer::consume() { return m_html[m_html_index++]; }

bool tokenizer::can_consume() noexcept { return m_html_index < m_html.size(); }

void tokenizer::skip_ascii_whitespace() {
    while (is_whitespace()) {
        consume();
    }
}

// https://infra.spec.whatwg.org/#ascii-whitespace
bool tokenizer::is_whitespace() {
    if (!can_consume())
        return false;

    // ASCII whitespace is U+0009 TAB, U+000A LF, U+000C FF, U+000D CR, or
    // U+0020 SPACE.
    auto current = peek();
    switch (current) {
    case '\u0009':
    case '\u000A':
    case '\u000C':
    case '\u000D':
    case '\u0020':
        return true;
    }

    return false;
}

} // namespace html