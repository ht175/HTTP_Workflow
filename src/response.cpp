#include "response.h"

Response::Response(){

}

Response::~Response(){

}

void Response::parse_status_line(){
    std::string first_crlf = "\r\n";
    std::size_t end_pos = response_string.find_first_of(first_crlf);
    status_line = response_string.substr(0, end_pos);
}

void Response::parse_expire(){
    expires = getValueFromHeader("Expires: ");
}

void Response::parse_date(){
    date = getValueFromHeader("Date: ");
}

void Response::parse_etage(){
    etag = getValueFromHeader("ETag: ");
}

void Response::parse_last_modified(){
    last_modified = getValueFromHeader("Last-Modified: ");
}

void Response::parse_chunked(){
    std::string transfer_encoding = getValueFromHeader("Transfer-Encoding: ");
    if(!transfer_encoding.empty())
    {
        if (transfer_encoding.find("chunked") != std::string::npos)
        {
            chunked = true;
        }
    }
}

void Response::parse_cache_directives(){
    std::string cache_value = getValueFromHeader("Cache-Control: ");
    std::string delimiter = ",";
    std::vector<std::string> cache_entries = split(cache_value,delimiter);
    for(auto & entry: cache_entries){
        std::vector<std::string> key_value = split(entry,"=");
        std::string key;
        std::string value;
        if(key_value.size()==2){
            key = key_value[0];
            value = key_value[1];
        }else{
            value = "";
        }
        cache_directives[key]=value;
    }
    //add to unorder_map

}


std::string Response::getValueFromHeader(std::string header){
    size_t header_val_pos = response_string.find(header)+header.length();
    std::string crlf = "\r\n";
    if (header_val_pos != std::string::npos)
    {
        std::string after_header = response_string.substr(header_val_pos);
        std::string value = after_header.substr(0,after_header.find(crlf));
       return value;
    }
    return "";
}

 std::vector<std::string> Response::split(std::string line, std::string delimiter){
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = line.find(delimiter);

    while (end != std::string::npos) {
        tokens.push_back(line.substr(start, end - start));
        start = end + delimiter.length();
        end = line.find(delimiter, start);
    }

    tokens.push_back(line.substr(start));
    return tokens;
 }













