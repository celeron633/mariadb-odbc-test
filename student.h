#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "common.h"

/*
修改方案:
    1. char数组大小用宏控制 比如 char name[STR_LEN_16], STR_LEN_16实际是 16*4 + 1或者16*3 + 1 (最好这样, 可以自动生成, 替换可以用大模型或者re替换)
    2. 使用wchar_t保存char (破坏可移植性, 编译告警级别高也会报警告)
    3. 直接改原来数组的大小, 统一扩长3倍 (不推荐, 容易搞错)
    4. 先Fetch, 再GetData, 然后增加函数utf-8转gbk, 不用改原来的 (代码改动大, 以前直接into的, 现在要加很多逻辑, 人力修改不现实)
    5. 改成cpp, 然后用std::string (不推荐, 不如用Java或者python写新逻辑)
*/

/*
-- test.TBL_STUDENT_INFO definition
CREATE TABLE `TBL_STUDENT_INFO` (
  `id` varchar(100) NOT NULL,
  `name` varchar(100) DEFAULT NULL,
  `age` int(10) unsigned DEFAULT NULL,
  `gender` varchar(8) DEFAULT NULL,
  `job` varchar(100) DEFAULT NULL,
  `note` varchar(1024) DEFAULT NULL,
  `hobby` varchar(16) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_uca1400_ai_ci;
*/

// types def
typedef struct tbl_student_info {
    char id[STR_LEN_100];
    char name[STR_LEN_100];
    int age;
    char gender[STR_LEN_8];
    char job[STR_LEN_100];
    char note[STR_LEN_1024];
    char hobby[STR_LEN_16];
} tbl_student_info;

// busi methods
int QueryAllStudents(void);
int AddStudent(tbl_student_info *stuInfo);

#endif