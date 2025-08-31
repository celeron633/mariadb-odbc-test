#ifndef __STUDENT_H__
#define __STUDENT_H__

// types def
struct tbl_student_info {
    char id[100 + 1];
    char name[100 + 1];
    int age;
    char gender[8 + 1];
    char job[100 + 1];
    char note[1024 + 1];
    char hobby[16 + 1];
};

// busi methods
int QueryAllStudents(void);

#endif