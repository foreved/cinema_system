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
// �鿴Ʊ��
void admin_sale(void);
// Ʊ������
void admin_box(void);
// �޸ĵ�Ӱ
void admin_edit(char* dest, char* src);
// �鿴��ӰƱ��
void admin_count(char* str);

#endif