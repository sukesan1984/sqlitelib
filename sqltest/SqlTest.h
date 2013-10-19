//
//  SqlTest.h
//  sqltest
//
//  Created by Kosuke Takami on 2013/10/19.
//  Copyright (c) 2013年 Kosuke Takami. All rights reserved.
//

#ifndef __sqltest__SqlTest__
#define __sqltest__SqlTest__

#include <iostream>
#include <string>
#include "sqlite3.h"

class SqlTest {
public:
    int sqliteOpen(sqlite3 **database);
    void sqliteCreateTable();
    const char* sqliteGetValueForKey(const char * key);
    void sqliteSetValueForKey(const char *key, const char *value);
};

#endif /* defined(__sqltest__SqlTest__) */
