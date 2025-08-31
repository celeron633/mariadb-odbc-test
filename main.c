#include <sql.h>
#include <sqlext.h>

#include "student.h"
#include "database.h"

int main()
{
    int ret = 0;

    InitDatabase();
    ret = ConnectDataBase();
    if (ret < 0) {
        return -1;
    }

    QueryAllStudents();

    DeInitDatabase();

    return 0;
}