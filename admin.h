#ifndef ADMIN_H
#define ADMIN_H

#include "cinema.h"

//// 管理员账号和密码
//Account admin_account = {
//	"admin",
//	"123456"
//};

extern Account admin_account;

// 管理员登入
int admin_login(Account* input);
// 管理员界面
void admin(Account* input);
// 管理员菜单
void admin_menu(void);
// 排片
void admin_arrange(void);
// 查看票款
void admin_sale(void);
// 票房排序
void admin_box(void);
// 修改电影
void admin_edit(char* dest, char* src);
// 查看电影票款
void admin_count(char* str);

#endif