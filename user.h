#ifndef USER_H
#define USER_H

#include "cinema.h"

typedef struct Record
{
	int flag;                 // 1 -- �ѹ�Ʊ��0 -- δ��Ʊ
	char room_name[ROOMNM];
	Movie film;
	Layout seat;
} Record;
typedef struct UserAccount
{
	Account user_account;
	Record tickets[TICKETS];
} UserAccount;


// �û�����
int user_login(Account* input);
// �û�����
void user(Account* input);
// �û��˵�
void user_menu(void);
// �û�ע��
int user_register(Account* input);
// �û����ӰƬ��Ϣ
void user_movie(void);
// �û���Ʊ
void user_buy(Account* input);
// �û���Ʊ
void user_return(Account* input);

#endif