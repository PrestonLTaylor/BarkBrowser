#include "tokenizer.hpp"
#include "../../Common/not_implemented_exception.hpp"
#include <format>

namespace html {

// https://html.spec.whatwg.org/#writing
std::vector<html_token> tokenizer::tokenize() {
    reset_tokenizer_state();

    std::vector<html_token> html_tokens;

    // TODO: 1. Optionally, a single U+FEFF BYTE ORDER MARK (BOM) character.

    // FIXME: Technically comments are inserted in the DOM as comments are
    // accessible in JavaScript, however, it is it fine for now.
    // 2. Any number of comments and ASCII whitespace.
    skip_comments();
    skip_ascii_whitespace();

    while (can_consume()) {
        throw not_implemented_exception(std::format(
            "Found '{}', tokenization of character is not yet implemented",
            m_html[m_html_index]));
    }

    return html_tokens;
}

void tokenizer::reset_tokenizer_state() noexcept { m_html_index = 0; }

char tokenizer::peek() const { return m_html[m_html_index]; }

char tokenizer::consume() { return m_html[m_html_index++]; }

bool tokenizer::can_consume(std::uint32_t amount_to_consume) const noexcept {
    return m_html_index + (amount_to_consume - 1) < m_html.size();
}

void tokenizer::skip(std::uint32_t to_skip) noexcept {
    m_html_index += to_skip;
}

bool tokenizer::skip_until_matches(std::string_view to_match) {
    auto found_match = m_html.find(to_match, m_html_index);
    if (found_match == std::string::npos) {
        return false;
    }

    m_html_index = found_match + to_match.size();
    return true;
}

bool tokenizer::matches(std::string_view to_match) const {
    if (!can_consume(to_match.size())) {
        return false;
    }

    auto to_check = std::string_view(&m_html[m_html_index], to_match.size());
    return to_match == to_check;
}

// https://html.spec.whatwg.org/#syntax-comments
void tokenizer::skip_comments() {
    while (is_comment()) {
        // Comments must have the following format:
        // 1. The string "<!--".
        skip(4);

        skip_to_end_of_comment();
    }
}

bool tokenizer::is_comment() const {
    // Comments must have the following format:
    // 1. The string "<!--".
    return matches("<!--");
}

void tokenizer::skip_to_end_of_comment() {
    // 2. Optionally, text, with the additional restriction that the text
    // must not start with the string ">", nor start with the string "->",
    // nor contain the strings "<!--", "-->", or "--!>", nor end with the
    // string "<!-".
    if (matches(">")) {
        skip(1);
        return;
    }

    if (matches("->")) {
        skip(2);
        return;
    }

    // NOTE: --!> also ends the comment
    // 3. The string "-->".
    if (skip_until_matches("-->")) {
        return;
    }

    skip_until_matches("--!>");
}

void tokenizer::skip_ascii_whitespace() {
    while (is_whitespace()) {
        consume();
    }
}

// https://infra.spec.whatwg.org/#ascii-whitespace
bool tokenizer::is_whitespace() const {
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