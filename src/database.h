#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <sqlite3.h>

class Database {
public:
    Database();  
    ~Database();

    void insertLink(const std::string &parent, const std::string &child);
    std::vector<std::pair<std::string, std::string>> getEdges();

private:
    sqlite3 *db;
};

#endif
