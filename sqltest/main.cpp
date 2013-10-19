//
//  main.cpp
//  sqltest
//
//  Created by Kosuke Takami on 2013/10/19.
//  Copyright (c) 2013年 Kosuke Takami. All rights reserved.
//

#include <iostream>
#include "SqlTest.h"

int main(int argc, const char * argv[])
{
    // insert code here...
    SqlTest* sql = new SqlTest();
    sql->sqliteCreateTable();
    sql->sqliteSetValueForKey("first", "cocos2d-x");
    sql->sqliteSetValueForKey("second", "cocos2d-iphone");
    printf("get first:%s\n",sql->sqliteGetValueForKey("first"));
    printf("get test:%s\n",sql->sqliteGetValueForKey("test"));
    std::cout << "Hello, World!\n";
    return 0;
}