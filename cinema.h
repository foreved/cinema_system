#ifndef CINEMA_H
#define CINEMA_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//Ӱ������
#define ROW 5       // ��
#define COL 10      // ��
// ��ӳ��
#define ROOMNM 20
#define FILMNM 20
#define ROOMFILE "room"
// �˻�
#define USRNM 8
#define PSD 8

// Ӱ���������ݽṹ
typedef struct Layout
{
	char screen;
	char seats[ROW][COL];
} Layout;
// ��ӳ�����ݽṹ
typedef struct Room
{
	char room_name[ROOMNM];
	char film_name[FILMNM];
	Layout seats;
	int sales;
	int remainings;
} Room;
// Account���ݽṹ
typedef struct Account
{
	char username[USRNM];
	char passward[PSD];
} Account;

// ��ȡ������Ϣ
char* get_info(char* ptr, int num);
// ��ӡ������Ϣ
void errinfo(int error_code);
// ��ʼ������
int initialize_cinema(void);
// ��ʼ����ӳ��
static void initialize_room(Room cinema[]);
// �������
void menu(void);
// ��ȡ�˺ź�����
Account* get_account(Account* input);
// ��ȡѡ��
int choice(void);
// ��ȡ�ַ�ѡ��
char ch_choice(void);

#endif