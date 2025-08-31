#include "student.h"
#include "database.h"

#include <stdio.h>
#include <stdlib.h>

int QueryAllStudents(void)
{
    if (CheckDatabaseConnection() < 0) {
        printf("数据库未连接!\r\n");
        return -1;
    }

    // STMT句柄
    SQLHSTMT hstmt;
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, GetHDBC(), &hstmt);

    // 执行查询
    SQLCHAR query[] = "SELECT id, name, age, gender, job, note, hobby FROM TBL_STUDENT_INFO";
    ret = SQLExecDirect(hstmt, query, SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        printf("执行SQL查询失败!\r\n");
        return -1;
    }

    // 定义结构体
    struct tbl_student_info student;
    // indicator, 保存长度
    SQLLEN db_ind;

    // 绑定列
    SQLBindCol(hstmt, 1, SQL_C_CHAR, student.id, sizeof(student.id), &db_ind);
    SQLBindCol(hstmt, 2, SQL_C_CHAR, student.name, sizeof(student.name), &db_ind);
    SQLBindCol(hstmt, 3, SQL_C_SLONG, &student.age, 0, &db_ind);
    SQLBindCol(hstmt, 4, SQL_C_CHAR, student.gender, sizeof(student.gender), &db_ind);
    SQLBindCol(hstmt, 5, SQL_C_CHAR, student.job, sizeof(student.job), &db_ind);
    SQLBindCol(hstmt, 6, SQL_C_CHAR, student.note, sizeof(student.note), &db_ind);
    SQLBindCol(hstmt, 7, SQL_C_CHAR, student.hobby, sizeof(student.hobby), &db_ind);

    while (1) {
        SQLRETURN ret = SQLFetch(hstmt);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            printf("ID: %s\n", student.id);
            printf("Name: %s\n", student.name);
            printf("Age: %d\n", student.age);
            printf("Gender: %s\n", student.gender);
            printf("Job: %s\n", student.job);
            printf("Note: %s\n", student.note);
            printf("Hobby: %s\n", student.hobby);
            printf("-------------------------\n");
        } else if (ret == SQL_NO_DATA) {
            printf("取完没有数据了!\r\n");
            break;
        } else if (ret == SQL_ERROR) {
            // 出错，打印诊断信息
            SQLCHAR state[6], msg[256];
            SQLINTEGER native;
            SQLSMALLINT len;
            if (SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, 1, state, &native, msg, sizeof(msg), &len) == SQL_SUCCESS) {
                printf("SQLFetch 错误: SQLSTATE=%s, Message=%s\n", state, msg);
            }
            break;
        } else if (ret == SQL_INVALID_HANDLE) {
            printf("无效句柄\n");
            break;
        } else {
            printf("其他返回值: %d\n", ret);
            break;
        }
    }

    // 关闭STMT
    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);

    return 0;
}