#pragma once
#include<exception>
#include<string>

class NoDataFoundException : std::exception
{
public:
    NoDataFoundException(){}
    explicit NoDataFoundException(std::string message) : message{message}{}
    virtual const char* what() const  _GLIBCXX_USE_NOEXCEPT{
        return message.c_str();
    }
private:
    std::string message;
};
