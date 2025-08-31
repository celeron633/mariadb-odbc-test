#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <sql.h>
#include <sqlext.h>

// common methods
void InitDatabase();
void DeInitDatabase();
int ConnectDataBase();

int CheckDatabaseConnection();
SQLHDBC GetHDBC(void);

#endif