#include <string>
#include <iostream>
#include <exception>
class SocketConnException : public std::exception {
private:
    std::string message;

public:
    // Without explicit keyword
    SocketConnException(const std::string& msg) : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class RequestParseException : public std::exception {
private:
    std::string message;

public:
    // Without explicit keyword
    RequestParseException(const std::string& msg) : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class DateTimeException: public std::exception {
private:
    std::string message;

public:
    // Without explicit keyword
    DateTimeException(const std::string& msg) : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};


