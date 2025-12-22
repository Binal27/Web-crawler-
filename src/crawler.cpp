#include "crawler.h"
#include <curl/curl.h>
#include <regex>
#include <iostream>

// Callback: store downloaded data into std::string
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    s->append((char*)contents, size * nmemb);
    return size * nmemb;
}
// Download page HTML

std::string Crawler::downloadPage(const std::string &url) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Important: many websites block curl unless User-Agent is set
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");

        // Follow HTTP redirects
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return readBuffer;
}

// -----------------------------
// Extract links using regex
// -----------------------------
std::vector<std::string> Crawler::extractLinks(const std::string &html) {
    std::vector<std::string> links;

    // Simple regex to capture URLs
    std::regex url_regex(R"((https?://[^\s"'<>]+))");
    std::smatch match;
    std::string text = html;

    // Iterate through all matches
    while (std::regex_search(text, match, url_regex)) {
        links.push_back(match.str(0));
        text = match.suffix();
    }

    return links;
}
