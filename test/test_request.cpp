#include <gtest/gtest.h>
#include "request.h"

TEST(RequestTest, ParseHostAndPort) {
    std::string raw_request = "GET / HTTP/1.1\r\nHost: www.example.com:8080\r\n\r\n";
    Request req(raw_request);
    
    EXPECT_NO_THROW(req.parse_host_and_port());
    EXPECT_EQ("www.example.com", req.getHost());
    EXPECT_EQ("8080", req.getPort());
}

TEST(RequestTest, ParseHostWithoutPort) {
    std::string raw_request = "GET / HTTP/1.1\r\nHost: www.example.com\r\n\r\n";
    Request req(raw_request);
    
    EXPECT_NO_THROW(req.parse_host_and_port());
    EXPECT_EQ("www.example.com", req.getHost());  
    EXPECT_EQ("80", req.getPort());
}

TEST(RequestTest, ParseRequestLine) {
    std::string raw_request = "GET /index.html HTTP/1.1\r\nHost: www.example.com\r\n\r\n";
    Request req(raw_request);
    
    EXPECT_NO_THROW(req.parse_request_line());
    EXPECT_EQ("GET /index.html HTTP/1.1", req.getReqLine());
}

TEST(RequestTest, ParseMethod) {
    std::string raw_request = "POST /submit HTTP/1.1\r\nHost: www.example.com\r\n\r\n";
    Request req(raw_request);
    
    EXPECT_NO_THROW(req.parse_Method());
    EXPECT_EQ("POST", req.getMethod());
}


