#ifndef USER_H
#define USER_H

#include "cinema.h"

// ---------------------------------------------------------------------------
// 数据结构定义
// ---------------------------------------------------------------------------

// 购票信息
typedef struct Record
{
	int flag;                          // 1 -- 已购票；0 -- 未购票
	Movie film;
	Layout seat;
	int row;
	int col;
} Record;
// 用户账户
typedef struct UserAccount
{
	Account user_account;
	Record tickets[TICKETS];           // flag: 0 -- 未买票；1 -- 已买票
	Record history[HISTORY];           // flag: 0 -- 未占用；1 -- 已占用
} UserAccount;

// ---------------------------------------------------------------------------
// 函数声明
// --------------------------------------------------------------------------- 

int user_login(Account* input);                // 用户登入
int user_register(Account* input);             // 用户注册

void user(Account* input);                     // 用户界面
void user_menu(void);                          // 用户菜单

void user_movie(void);                         // 用户浏览影片信息
void user_buy(Account* input);                 // 用户购票
void user_return(Account* input);              // 用户退票
void user_history(Account* input);             // 用户历史记录

// --------------------------------------------------------------------------- 

#endif