#include "database.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// odbc support
SQLHENV henv;
SQLHDBC hdbc;
static SQLRETURN ret;

// connections
SQLCHAR connStr[] = "DSN=MySQL-test;UID=dengxh;PWD=12345678;";

void InitDatabase()
{
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
}

int ConnectDataBase()
{
    ret = SQLDriverConnect(hdbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
    if (!SQL_SUCCEEDED(ret)) {
        printf("数据库连接失败!!!\n");
        return -1;
    } else {
        printf("数据库连接成功!\n");
    }

    return 0;
}

void DeInitDatabase()
{
    SQLDisconnect(hdbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, henv);
}

int CheckDatabaseConnection()
{
    SQLUINTEGER dead;
    SQLRETURN ret = SQLGetConnectAttr(hdbc, SQL_ATTR_CONNECTION_DEAD, &dead, 0, NULL);

    if (SQL_SUCCEEDED(ret)) {
        if (dead == SQL_CD_FALSE) {
            printf("连接正常\n");
            return 0;
        } else {
            printf("连接已断开\n");
            return -1;
        }
    } else {
        printf("无法检查连接状态\n");
        return -1;
    }

    return 0;
}

SQLHDBC GetHDBC(void)
{
    return hdbc;
}