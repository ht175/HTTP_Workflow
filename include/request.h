#include <string>
#include "exception.h"
#include <sstream>
class Request {
    private:
    //get/post/connect
    std::string method;
    //target website & port 
    std::string host;
    std::string port;
    //example: GET www.bbc.co.uk/ HTTP/1.1
    std::string req_line;
    //request input string (whole request messages):
    std::string req_string;
    //time received (TIME)
    //UTC & asctime format
    // std::string recv_time;
    public:
    Request(std::string request);
    ~Request();
    std::string getHost() const;
    std::string getPort() const;
    std::string getReqLine() const;
    std::string getMethod() const;
    //convert a request object to string which could be send to target host
    std::string toString() const;
    void parse_request();
    void parse_Method();
    void parse_host_and_port();
    void parse_request_line();
};