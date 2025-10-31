#include "tokenizer.hpp"

namespace html {

std::vector<html_token> tokenizer::tokenize() {
    reset_tokenizer_state();

    std::vector<html_token> html_tokens;

    return html_tokens;
}

void tokenizer::reset_tokenizer_state() noexcept { m_html_index = 0; }

bool tokenizer::can_consume() noexcept { return m_html_index < m_html.size(); }

} // namespace html