#include "request.h"
Request::Request(std::string request):req_string(request){
    parse_request();
}
Request::~Request(){}
std::string Request::getHost() const{
    return host;
}
std::string Request::getMethod() const{
    return method;
}
std::string Request::getPort() const{
    return port;
}
std::string Request::getReqLine() const{
    return req_line;
}

std::string Request::toString() const{
    return req_string;
}

void Request::parse_request(){
    parse_Method();
    parse_request_line();
    parse_host_and_port();
}
void Request::parse_host_and_port(){
    std::string header_mark = "Host: ";
    std::string lineEnd = "\r\n";
    std::string delimiter = ":";
    size_t host_pos = req_string.find(header_mark) +header_mark.length();
    std::string after_host = req_string.substr(host_pos);
    std::string host_post = after_host.substr(0, after_host.find(lineEnd));
    if(host_pos != std::string::npos){   
        //host_post = "hostname:port"
        //host_post = "hostname"
        size_t delimiter_pos = host_post.find(delimiter);
        if(delimiter_pos != std::string::npos){
            host = host_post.substr(0, delimiter_pos);
            port = host_post.substr(delimiter_pos + 1);
        }else{
            host = host_post;
            //default HTTP port
            port = "80";
        }
    }else{
        std::ostringstream errorMessage;
        errorMessage << "cannot parse host and ip: "
                     << req_string;
        throw RequestParseException(errorMessage.str());
    }
}

void Request::parse_request_line(){
    std::string lineEnd = "\r\n";
    size_t firstLineEnd_pos = req_string.find(lineEnd);
    if(firstLineEnd_pos != std::string::npos){
        req_line = req_string.substr(0, firstLineEnd_pos);
    }else{
        std::ostringstream errorMessage;
        errorMessage << "cannot parse request_line"
                     << req_string;
        throw RequestParseException(errorMessage.str());
    }
    
}

void Request::parse_Method(){
    std::string delimiter = " ";
    size_t delimiter_pos = req_string.find(delimiter);
    if(delimiter_pos != std::string::npos){
        method = req_string.substr(0, delimiter_pos);
    }else{
        std::ostringstream errorMessage;
        errorMessage << "cannot parse method"
                     << req_string;
        throw RequestParseException(errorMessage.str());
    }
    
}
