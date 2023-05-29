#ifndef USER_H
#define USER_H

#include "cinema.h"

typedef struct Record
{
	int flag;                 // 1 -- 已购票；0 -- 未购票
	char room_name[ROOMNM];
	Movie film;
	Layout seat;
} Record;
typedef struct UserAccount
{
	Account user_account;
	Record tickets[TICKETS];
} UserAccount;


// 用户登入
int user_login(Account* input);
// 用户界面
void user(Account* input);
// 用户菜单
void user_menu(void);
// 用户注册
int user_register(Account* input);
// 用户浏览影片信息
void user_movie(void);
// 用户购票
void user_buy(Account* input);
// 用户退票
void user_return(Account* input);

#endif