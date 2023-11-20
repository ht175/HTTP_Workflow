#include <string>
#include <sstream>
#include <unordered_map>
#include <ctime>
#include <vector>
class Response
{
private:
    std::string response_string;
    std::string status_line;
    std::string expires;
    std::string date;
    //two different dealing method transfer-encoding & content_length
    bool chunked;
    int content_length;
    std::string last_modified;
    std::string etag; 
    std::unordered_map<std::string, std::string> cache_directives;

public:
    enum class Cacheability {
       //cannot cache because
       UNCACHEABLE_NO_STORE,
       UNCACHEABLE_PRIVATE,
       UNCACHEABLE_CHUNKED,
       CACHEABLE_WILL_EXPIRE,
       CACHEABLE_NEED_VAILDATE,
       CACHE_DEFAULT,
   };
    enum class CacheStatus{
        VAILD,
        NEED_VAILDATE,
        EXPIRE,
   };
   
    Response(/* args */);
    ~Response();
    time_t calculateFreshnessLifetime();
    time_t calculateCurrentAge();
    Cacheability checkCacheability();
    CacheStatus checkCacheStatus();
    void parse_status_line();
    void parse_expire();
    void parse_date();
    void parse_chunked();
    void parse_content_length();
    void parse_cache_directives();
    void parse_response();
    void parse_etage();
    void parse_last_modified();
    std::string get_status_line() const;
    std::string get_etag() const;
    std::string get_last_modified() const;
    std::string get_expire() const;
    std::string get_date() const;
    bool checkChunked() const;
    int get_content_length() const;
    std::unordered_map<std::string, std::string> get_cache_directives() const;
    std::string getValueFromHeader(std::string header);
    std::vector<std::string> split(std::string line, std::string delimiter);

};


