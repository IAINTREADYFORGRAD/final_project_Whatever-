#ifndef BASE_H
#define BASE_H
#include "struct.h"
void add_course(Course *head, char *Name, char *Location, int room_number, char *week, int begin_hours, int begin_minutes, int end_hours, int end_minutes, double difficult, double course_credit);
void add_curriculum(Course *class_head, Course *curriculm, int max_cp_A); //新增一個course到課表內
void delete_course(Course *head, char *name);
void delete_cannot_time(Course *class_head, char *week); //刪掉該學生不行上課的課
void print_all(Course *head);                            //印出全部課程
int start_time_to_min(Course *p);                        //將開始時間轉成分鐘型態
int end_time_to_min(Course *p);                          //將結束時間轉成分鐘型態
void sort(Course *head);                                 //排序（依照開始時間排）
void set_node(Course *p);                                //初始化
Course *search(Course *head, const char *name);          //根據名稱找尋並回傳此指標
void print_single(Course *p);                            //印出一個只是方便看
#endif