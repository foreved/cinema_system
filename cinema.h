#ifndef CINEMA_H
#define CINEMA_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <Windows.h>

// ---------------------------------------------------------------------------
// ��ʶ������ 
// ---------------------------------------------------------------------------

// ��ӳ����Ϣ
#define ROW 5                       // ��
#define COL 10                      // ��
#define ROOMNM 20                   // ��ӳ�����ƴ�С
#define FILMNM 20                   // ��Ӱ���ƴ�С
#define ROOMFILE "room"             // ��ӳ���ļ���
// �˻���Ϣ
#define USRNM 8                     // �û�����С
#define PSD 8                       // �����С
#define TICKETS 5                   // ÿλ�û��Ĺ�Ʊ����
#define HISTORY "history"           // ��ʷ�ļ�����
#define USERFILE "user"             // �û���Ϣ�ļ���

// ---------------------------------------------------------------------------
// ���ݽṹ����
// ---------------------------------------------------------------------------

typedef struct Date                 // ʱ��
{
	int year;                       // ��
	int mouth;                      // ��
	int day;                        // ��
} Date;

typedef struct Layout               // ��λ�۳����
{
	int seats[ROW][COL];            // 1 -- ���ۣ�0 -- δ��
} Layout;

typedef struct Movie                // ��Ӱ��Ϣ
{
	char room_name[ROOMNM];         // ��ӳ�õ�Ӱ��Ӱ������
	char film_name[FILMNM];         // ��Ӱ����
	int price;                      // ��Ӱ�۸�
	Date date;                      // ��Ӱ����
} Movie;

typedef struct Room                 // ��ӳ��
{
	char room_name[ROOMNM];         // Ӱ������
	Movie film;                     // ��ӳ�ĵ�Ӱ��Ϣ
	Layout seat;                    // ��λ�۳����
	int sales;                      // ��Ʊ��
	int remainings;                 // ��Ʊ��
	int boxes;                      // Ʊ��
} Room;

typedef struct Account              // �˻�
{
	char username[USRNM];           // �û���
	char passward[PSD];             // ����
} Account;

// ---------------------------------------------------------------------------
// ��������
// --------------------------------------------------------------------------- 

char* str_get(char* str, int num);           // ��ȡ�ַ���
char* ch_get(char* ch);                      // ��ȡ�ַ�
int* i_get(int* i);                          // ��ȡ����

void errinfo(void);                          // ��ӡ������Ϣ
void invalid(void);                          // ��ӡ��Ч������ʾ


int initialize_cinema(void);	             // ��ʼ������
void initialize_room(Room cinema[]);         // ��ʼ����ӳ��

void menu(void);                             // �������˵�

Account* get_account(Account* input);        // ��ȡ�˻���Ϣ

void movie_style(void);                      // ӰƬ��Ϣ

#endif