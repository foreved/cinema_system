#ifndef USER_H
#define USER_H

#include "cinema.h"

// ---------------------------------------------------------------------------
// ���ݽṹ����
// ---------------------------------------------------------------------------

// ��Ʊ��Ϣ
typedef struct Record
{
	int flag;                          // 1 -- �ѹ�Ʊ��0 -- δ��Ʊ
	Movie film;
	Layout seat;
	int row;
	int col;
} Record;
// �û��˻�
typedef struct UserAccount
{
	Account user_account;
	Record tickets[TICKETS];           // flag: 0 -- δ��Ʊ��1 -- ����Ʊ
	Record history[HISTORY];           // flag: 0 -- δռ�ã�1 -- ��ռ��
} UserAccount;

// ---------------------------------------------------------------------------
// ��������
// --------------------------------------------------------------------------- 

int user_login(Account* input);                // �û�����
int user_register(Account* input);             // �û�ע��

void user(Account* input);                     // �û�����
void user_menu(void);                          // �û��˵�

void user_movie(void);                         // �û����ӰƬ��Ϣ
void user_buy(Account* input);                 // �û���Ʊ
void user_return(Account* input);              // �û���Ʊ
void user_history(Account* input);             // �û���ʷ��¼

// --------------------------------------------------------------------------- 

#endif