#include "database.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// odbc support
SQLHENV henv;
SQLHDBC hdbc;
// SQLHSTMT hstmt;
static SQLRETURN ret;

// connections
SQLCHAR connStr[] = "DSN=MySQL-test;UID=dengxh;PWD=12345678;";
int isConnected = 0;

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
        isConnected = 0;
        return -1;
    } else {
        printf("数据库连接成功!\n");
        isConnected = 1;
    }

    return 0;
}

void DeInitDatabase()
{
    SQLDisconnect(hdbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, henv);
}

int IsDatabaseConnected()
{
    return isConnected;
}

SQLHDBC GetHDBC(void)
{
    return hdbc;
}

// inline SQLHSTMT GetHSTMT(void)
// {
//     return hstmt;
// }