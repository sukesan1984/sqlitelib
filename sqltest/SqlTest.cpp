///Users/takami.kosuke/work/cplusplus/sqltest/sqltest.xcodeproj
//  SqlTest.cpp
//  sqltest
//
//  Created by Kosuke Takami on 2013/10/19.
//  Copyright (c) 2013年 Kosuke Takami. All rights reserved.
//

#include "SqlTest.h"

int SqlTest::sqliteOpen(sqlite3 **database){
    std::string path = "sample.db";
    return sqlite3_open(path.c_str(), database);
}

void SqlTest::sqliteCreateTable(){
    //データベースファイルを作成する。
    sqlite3 *db = NULL;
    if(sqliteOpen(&db) == SQLITE_OK){
        const char *sql_createtable = "CREATE TABLE test1(key TEXT, value TEXT)";
        sqlite3_stmt *stmt = NULL;
        if(sqlite3_prepare_v2(db, sql_createtable, -1, &stmt, NULL) == SQLITE_OK){
            if(sqlite3_step(stmt) == SQLITE_DONE){
                printf("create table done\n");
            }
            sqlite3_reset(stmt);
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
}

const char* SqlTest::sqliteGetValueForKey(const char *key){
    printf("get key: %s\n", key);
    std::string *retVal = 0;
    sqlite3 *db = NULL;
    if(sqliteOpen(&db) == SQLITE_OK){
        const char *sql_select = "select value from test1 where key = ?";
        sqlite3_stmt *stmt = NULL;
        if(sqlite3_prepare_v2(db, sql_select, -1, &stmt, NULL) == SQLITE_OK){
            sqlite3_bind_text(stmt, 1, key, -1, SQLITE_TRANSIENT);
            int ret = sqlite3_step(stmt);
            if( ret == SQLITE_DONE || ret == SQLITE_ROW){
                printf(" ret == SQLITE_DONE || ret == SQLITE_ROW \n");
                const char *val = (const char*) sqlite3_column_text(stmt, 0);
                printf("val: %s\n", val);
                retVal = new std::string(val);
            }
            sqlite3_reset(stmt);
        } else {
            printf("error!!!\n");
        }
        sqlite3_finalize(stmt);
    } else {
        printf("error!!! open db\n");
    }
    sqlite3_close(db);
    if(retVal != NULL){
        return retVal->c_str();
    }
    return NULL;
}

void SqlTest::sqliteSetValueForKey(const char *key, const char *value){
    std::string path = "sample.db";
    sqlite3 *db = NULL;
    if (sqlite3_open(path.c_str(), &db) == SQLITE_OK){
        const char  *sql_select = "REPLACE INTO test1 (key, value) VALUES (?, ?)";
        sqlite3_stmt *stmt = NULL;
        if(sqlite3_prepare_v2(db, sql_select, -1, &stmt, NULL) == SQLITE_OK){
            sqlite3_bind_text(stmt, 1, key, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, value, -1, SQLITE_TRANSIENT);
            if( sqlite3_step(stmt) == SQLITE_DONE){
                printf("replace key:%s value:%s\n", key, value);
            }
            sqlite3_reset(stmt);
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
}