#include "database.h"
#include <iostream>

Database::Database() {
    if (sqlite3_open("links.db", &db)) {
        std::cerr << "Could not open DB\n";
    }

    const char *sql =
        "CREATE TABLE IF NOT EXISTS links ("
        "parent TEXT, child TEXT);";

    char *err;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &err) != SQLITE_OK) {
        std::cerr << "SQL error: " << err << "\n";
        sqlite3_free(err);
    }
}

Database::~Database() {
    sqlite3_close(db);
}

void Database::insertLink(const std::string &parent, const std::string &child) {
    std::string query = "INSERT INTO links (parent, child) VALUES ('" + parent + "', '" + child + "');";

    char *err;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &err) != SQLITE_OK) {
        std::cerr << "Insert error: " << err << "\n";
        sqlite3_free(err);
    }
}

std::vector<std::pair<std::string, std::string>> Database::getEdges() {
    std::vector<std::pair<std::string, std::string>> edges;

    const char *sql = "SELECT parent, child FROM links;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string parent = (const char *)sqlite3_column_text(stmt, 0);
            std::string child = (const char *)sqlite3_column_text(stmt, 1);
            edges.push_back({parent, child});
        }
    }

    sqlite3_finalize(stmt);
    return edges;
}

