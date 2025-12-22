#ifndef CRAWLER_H
#define CRAWLER_H

#include <string>
#include <vector>

class Crawler {
public:
    std::string downloadPage(const std::string &url);
    std::vector<std::string> extractLinks(const std::string &html);
};

#endif
