#ifndef PAGERANK_H
#define PAGERANK_H

#include <map>
#include <vector>
#include <string>

class PageRank {
public:
    static std::map<std::string, double> compute(
        const std::vector<std::pair<std::string, std::string>> &edges
    );
};

#endif
