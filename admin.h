#ifndef ADMIN_H
#define ADMIN_H

#include "cinema.h"

//// ����Ա�˺ź�����
//Account admin_account = {
//	"admin",
//	"123456"
//};

extern Account admin_account;

// ����Ա����
int admin_login(Account* input);
// ����Ա����
void admin(Account* input);
// ����Ա�˵�
void admin_menu(void);
// ��Ƭ
void admin_arrange(void);


// �޸ĵ�Ӱ
void admin_edit(char* dest, char* src);

#endif