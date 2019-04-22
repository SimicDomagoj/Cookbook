#pragma once
#include<exception>
#include<string>

class InvalidFormatException : std::exception
{
public:
    InvalidFormatException(){}
    explicit InvalidFormatException(std::string message) : message{message}{}
    virtual const char* what() const  _GLIBCXX_USE_NOEXCEPT{
        return message.c_str();
    }
private:
    std::string message;
};
