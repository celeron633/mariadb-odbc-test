# MariaDB odbc测试程序

## 开发环境
```javascript
OS:
Arch Linux 主线
GCC: 
gcc 15.2.1

安装的包:
REPO:
sudo pacman -S mariadb-lts unixodbc

AUR:
yay -S mariadb-connector-odbc
```

## 配置文件

### /etc/odbc.ini
```shell
[MySQL-test]
Description     = MySQL database test
Driver          = MySQL
Server          = localhost
Database        = test
Port            = 3306
Socket          = /var/run/mysqld/mysqld.sock
Option          =
Stmt            =
```

### /etc/odbcinst.ini
```shell
[MySQL]
Description     = ODBC Driver for MySQL
Driver          = /usr/lib/libmaodbc.so
FileUsage       = 1
```