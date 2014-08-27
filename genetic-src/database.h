#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <string>
#include <map>
#include <vector>
#include "sqlite3.h"

using namespace std;

class Database {
public:
    Database(string db) {
        this->open(db);
    }
    ~Database(void) {
        this->close();
    }

    bool open(string database) {
        return sqlite3_open(database.c_str(), &db);
    }

    void close(void) {
        sqlite3_close(db);
    }

    vector<vector<string> > query(string stmt) {
        sqlite3_stmt *statement;
        vector<vector<string> > results;

        if(sqlite3_prepare_v2(db, stmt.c_str(), -1, &statement, 0) == SQLITE_OK) {
            int cols = sqlite3_column_count(statement);
            int result = 0;
            for(;;) {
                result = sqlite3_step(statement);

                if(result == SQLITE_ROW) {
                    vector<string> values;
                    for(int col = 0; col < cols; col++)
                    {
                        string val((char*)sqlite3_column_text(statement, col));
                        values.push_back(val);
                    }
                    results.push_back(values);
                } else {
                    break;
                }
            }
            sqlite3_finalize(statement);
        }

        string error = sqlite3_errmsg(db);
        if(error != "not an error") {
            printf("%s %s\n", stmt.c_str(), error.c_str());
        }

        return results;
    }
private:
    sqlite3* db;
};

#endif