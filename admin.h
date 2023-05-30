#ifndef ADMIN_H
#define ADMIN_H

#include "cinema.h"

extern Account admin_account;

// ---------------------------------------------------------------------------
// 函数声明
// --------------------------------------------------------------------------- 

int admin_login(Account* input);							// 管理员登入

void admin(Account* input);									// 管理员界面
void admin_menu(void);										// 管理员菜单

void admin_arrange(void);									// 排片
void admin_sale(void);										// 查看票款
void admin_box(void);										// 查看票房

// --------------------------------------------------------------------------- 

#endif