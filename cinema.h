#ifndef CINEMA_H
#define CINEMA_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <Windows.h>

// ---------------------------------------------------------------------------
// 标识符定义 
// ---------------------------------------------------------------------------

// 放映厅信息
#define ROW 5                       // 排
#define COL 10                      // 列
#define ROOMNM 20                   // 放映厅名称大小
#define FILMNM 20                   // 电影名称大小
#define ROOMFILE "room"             // 放映厅文件名
// 账户信息
#define USRNM 8                     // 用户名大小
#define PSD 8                       // 密码大小
#define TICKETS 5                   // 每位用户的购票上限
#define HISTORY "history"           // 历史文件夹名
#define USERFILE "user"             // 用户信息文件名

// ---------------------------------------------------------------------------
// 数据结构定义
// ---------------------------------------------------------------------------

typedef struct Date                 // 时间
{
	int year;                       // 年
	int mouth;                      // 月
	int day;                        // 日
} Date;

typedef struct Layout               // 座位售出情况
{
	int seats[ROW][COL];            // 1 -- 已售；0 -- 未售
} Layout;

typedef struct Movie                // 电影信息
{
	char room_name[ROOMNM];         // 放映该电影的影厅名称
	char film_name[FILMNM];         // 电影名称
	int price;                      // 电影价格
	Date date;                      // 电影日期
} Movie;

typedef struct Room                 // 放映厅
{
	char room_name[ROOMNM];         // 影厅名称
	Movie film;                     // 放映的电影信息
	Layout seat;                    // 座位售出情况
	int sales;                      // 售票数
	int remainings;                 // 余票数
	int boxes;                      // 票房
} Room;

typedef struct Account              // 账户
{
	char username[USRNM];           // 用户名
	char passward[PSD];             // 密码
} Account;

// ---------------------------------------------------------------------------
// 函数声明
// --------------------------------------------------------------------------- 

char* str_get(char* str, int num);           // 获取字符串
char* ch_get(char* ch);                      // 获取字符
int* i_get(int* i);                          // 获取整数

void errinfo(void);                          // 打印错误信息
void invalid(void);                          // 打印无效命令提示


int initialize_cinema(void);	             // 初始化程序
void initialize_room(Room cinema[]);         // 初始化放映厅

void menu(void);                             // 程序主菜单

Account* get_account(Account* input);        // 获取账户信息

void movie_style(void);                      // 影片信息

#endif