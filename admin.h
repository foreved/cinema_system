#ifndef ADMIN_H
#define ADMIN_H

#include "cinema.h"

extern Account admin_account;

// ---------------------------------------------------------------------------
// ��������
// --------------------------------------------------------------------------- 

int admin_login(Account* input);							// ����Ա����

void admin(Account* input);									// ����Ա����
void admin_menu(void);										// ����Ա�˵�

void admin_arrange(void);									// ��Ƭ
void admin_sale(void);										// �鿴Ʊ��
void admin_box(void);										// �鿴Ʊ��

// --------------------------------------------------------------------------- 

#endif