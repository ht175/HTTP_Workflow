#include <string>
#include <ctime>
#include <regex>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "exception.h"
class DateTime
{
private:
    /* data */
    time_t date;
    struct tm time_info;
    


public:
//make time use current time
    DateTime();
//make time use "string" Eg: Sun, 06 Nov 1994 08:49:37 GMT
    DateTime(std::string http_date);
    ~DateTime();
    void parseTime(std::string http_date);
    //convert time_t to asc format string
    std::string toString() const;
    void fillTimeInfo(const std::smatch& match_results, int pattern);
    int adjustYear(int twoDigitYear);
    time_t getTime() const;


};


