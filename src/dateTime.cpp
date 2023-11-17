#include "dateTime.h"
namespace DateTimeConstants {
    const std::unordered_map<std::string, int> months = {
        {"Jan", 0}, {"Feb", 1}, {"Mar", 2}, {"Apr", 3},
        {"May", 4}, {"Jun", 5}, {"Jul", 6}, {"Aug", 7},
        {"Sep", 8}, {"Oct", 9}, {"Nov", 10}, {"Dec", 11}
    };

    const std::unordered_map<std::string, int> weekdays = {
        {"Sun", 0}, {"Sunday", 0},
        {"Mon", 1}, {"Monday", 1},
        {"Tue", 2}, {"Tuesday", 2},
        {"Wed", 3}, {"Wednesday", 3},
        {"Thu", 4}, {"Thursday", 4},
        {"Fri", 5}, {"Friday", 5},
        {"Sat", 6}, {"Saturday", 6}
    };
}
DateTime::DateTime() : date(time(nullptr)) {
    std::memset(&time_info, 0, sizeof(time_info));
    localtime_r(&date, &time_info); 
}
DateTime::DateTime(std::string http_date)
{   
    std::memset(&time_info, 0, sizeof(time_info));
    parseTime(http_date);
}
DateTime::~DateTime(){}

void DateTime::parseTime(std::string http_date)
{
    // possible format:
    //  format1 = "Sun, 06 Nov 1994 08:49:37 GMT";
    //  format2 = "Sunday, 06-Nov-94 08:49:37 GMT";
    //  format3 = "Sun Nov  6 08:49:37 1994";
    std::regex time_pattern1(R"((\w{3}), (\d{2}) (\w{3}) (\d{4}) (\d{2}:\d{2}:\d{2}) GMT)");
    std::regex time_pattern2(R"((\w+), (\d{2})-(\w{3})-(\d{2}) (\d{2}:\d{2}:\d{2}) GMT)");
    std::regex time_pattern3(R"((\w{3}) (\w{3}) {1,2}(\d{1,2}) (\d{2}:\d{2}:\d{2}) (\d{4}))");

    std::smatch match_results;
    if (std::regex_match(http_date, match_results, time_pattern1))
    {
        fillTimeInfo(match_results,1);
    }
    else if (std::regex_match(http_date, match_results, time_pattern2))
    {
       fillTimeInfo(match_results,2);
    }
    else if (std::regex_match(http_date, match_results, time_pattern3))
    {
       fillTimeInfo(match_results,3);
    }
    else
    {
        // Handle error
        std::ostringstream errorMessage;
        errorMessage << "cannot parse time"
                     << http_date;
        throw DateTimeException(errorMessage.str());
        
    }
    date = mktime(&time_info);
}

std::string DateTime::toString() const{
    std::vector<char> buffer(26);
    asctime_r(&time_info, buffer.data());
    std::string timeAsString(buffer.data());
    return timeAsString;
}

void DateTime::fillTimeInfo(const std::smatch& match_results,int pattern) {
     switch (pattern) {
        case 1: // Pattern 1: "Sun, 06 Nov 1994 08:49:37 GMT"
        case 2: // Pattern 2: "Sunday, 06-Nov-94 08:49:37 GMT"
            time_info.tm_wday = DateTimeConstants::weekdays.at(match_results[1]);
            time_info.tm_mday = std::stoi(match_results[2]);
            time_info.tm_mon = DateTimeConstants::months.at(match_results[3]);
            time_info.tm_year = (pattern == 1) ? std::stoi(match_results[4]) - 1900
                                               : adjustYear(std::stoi(match_results[4]));
            std::sscanf(match_results[5].str().c_str(), "%d:%d:%d", &time_info.tm_hour, &time_info.tm_min, &time_info.tm_sec);
            break;
        case 3: // Pattern 3: "Sun Nov  6 08:49:37 1994"
            time_info.tm_wday = DateTimeConstants::weekdays.at(match_results[1]);
            time_info.tm_mon = DateTimeConstants::months.at(match_results[2]);
            time_info.tm_mday = std::stoi(match_results[3]);
            std::sscanf(match_results[5].str().c_str(), "%d:%d:%d", &time_info.tm_hour, &time_info.tm_min, &time_info.tm_sec);
            time_info.tm_year = std::stoi(match_results[5]) - 1900;
            break;
    }
}
int DateTime::adjustYear(int twoDigitYear) {
    // Adjust for two-digit years; you might want to modify this logic based on your requirements
    return (twoDigitYear >= 50 ? twoDigitYear + 1900 : twoDigitYear + 2000) - 1900;
}
time_t DateTime::getTime() const{
    return date;
}


