#include <iostream>
#include "crawler.h"
#include "database.h"
#include "pagerank.h"

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "Usage: ./webcrawler <URL>\n";
        return 1;
    }

    std::string startURL = argv[1];   // <-- READ URL FROM COMMAND LINE

    Crawler crawler;
    Database db;

    std::string html = crawler.downloadPage(startURL);
    auto links = crawler.extractLinks(html);

    for (auto &l : links) {
        db.insertLink(startURL, l);
    }

    auto edges = db.getEdges();

    auto scores = PageRank::compute(edges);

    std::cout << "\nPageRank Scores:\n";
    for (const auto &p : scores) {
        std::cout << p.first << " -> " << p.second << "\n";
    }

    return 0;
}
