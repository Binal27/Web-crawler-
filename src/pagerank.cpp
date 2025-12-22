#include "pagerank.h"
#include <set>
#include <cmath>

std::map<std::string, double> PageRank::compute(const std::vector<std::pair<std::string, std::string>> &edges) {
    std::set<std::string> pages;
    for (auto &e : edges) {
        pages.insert(e.first);
        pages.insert(e.second);
    }

    int N = pages.size();
    std::map<std::string, double> rank;
    for (auto &p : pages) rank[p] = 1.0 / N;

    const double damping = 0.85;

    for (int iter = 0; iter < 50; iter++) {
        std::map<std::string, double> newRank;

        for (auto &p : pages) newRank[p] = (1 - damping) / N;

        for (auto &e : edges) {
            std::string from = e.first;
            std::string to = e.second;

            int outDegree = 0;
            for (auto &x : edges) if (x.first == from) outDegree++;

            if (outDegree > 0)
                newRank[to] += damping * (rank[from] / outDegree);
        }
        rank = newRank;
    }

    return rank;
}
