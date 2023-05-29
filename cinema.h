#ifndef CINEMA_H
#define CINEMA_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//影厅布局
#define ROW 5       // 排
#define COL 10      // 列
// 放映厅
#define ROOMNM 20
#define FILMNM 20
#define ROOMFILE "room"
// 账户
#define USRNM 8
#define PSD 8

// 影厅布局数据结构
typedef struct Layout
{
	char screen;
	char seats[ROW][COL];
} Layout;
// 放映厅数据结构
typedef struct Room
{
	char room_name[ROOMNM];
	char film_name[FILMNM];
	Layout seats;
	int sales;
	int remainings;
} Room;
// Account数据结构
typedef struct Account
{
	char username[USRNM];
	char passward[PSD];
} Account;

// 获取输入信息
char* get_info(char* ptr, int num);
// 打印错误信息
void errinfo(int error_code);
// 初始化程序
int initialize_cinema(void);
// 初始化放映厅
static void initialize_room(Room cinema[]);
// 登入界面
void menu(void);
// 获取账号和密码
Account* get_account(Account* input);
// 获取选项
int choice(void);
// 获取字符选项
char ch_choice(void);

#endif