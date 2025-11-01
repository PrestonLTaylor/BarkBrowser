#pragma once
#include <exception>
#include <string>

class not_implemented_exception : public std::exception {
public:
    not_implemented_exception(std::string &&msg) : m_msg(std::move(msg)) {}

    char const *what() const override { return m_msg.c_str(); }

private:
    std::string m_msg;
};
