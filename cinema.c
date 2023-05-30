#include "cinema.h"

// ---------------------------------------------------------------------------
// ��������
// ---------------------------------------------------------------------------

// ��ȡ�ַ���
// ������str -- �����ַ����ı����ĵ�ַ��num -- ������յ�����ַ���
// Ч������stdin��ȡָ����С���ַ�����ȥ�����е�'\n'����ˢ�»�����
// ���أ�ʧ�ܣ�����NULL���ɹ������ر����ĵ�ַ
char* str_get(char* str, int num)
{
	int i, flag;                             // flag: 1 -- ˢ�»�������0 -- �޲���
	char ch;

	if (NULL == fgets(str, num, stdin))      // ��ȡʧ��
	{
		errinfo();                           // ��ӡ������Ϣ
		return NULL;                         // ����NULL
	}

	flag = 1;                                // Ĭ�ϻ�������ʣ���ַ�

	for (i = 0; i < strlen(str); i++)        // ȥ���ַ����е�'\n'
		if ('\n' == str[i])
		{
			str[i] = '\0';
			flag = 0;                        // flag����
			break;
		}
	if (flag)
		while ((ch = getchar()) != '\n')     // ������������ַ�
			continue;

	return str;
}

// ---------------------------------------------------------------------------

// ��ȡ�ַ�
// ������ch -- �����ַ��ı����ĵ�ַ
// Ч������stdin��ȡһ���ַ�����ˢ�»�����
// ���أ�ʧ�ܣ�����NULL���ɹ������ر����ĵ�ַ
char* ch_get(char* ch)
{
	char temp;

	if (1 != scanf("%c", ch))              // ��ȡʧ��
	{
		errinfo();                         // ��ӡ������Ϣ
		return NULL;                       // ����NULL
	}

	// ������������һ��'\n'�ַ�
	while ((temp = getchar()) != '\n')
		continue;

	return ch;
}

// ---------------------------------------------------------------------------

// ��ȡ����
// ������i -- ���������ı����ĵ�ַ
// Ч������stdin��ȡһ����������ˢ�»�����
// ���أ�ʧ�ܣ�����NULL���ɹ������ر����ĵ�ַ
int* i_get(int* i)
{
	char temp;

	while (1 != scanf("%d", i))
	{
		printf("Please enter an ");
		printf("\033[31m");           // ������ɫ��ɫ
		printf("integer");
		printf("\033[0m");            // ������ɫ
		printf(".\n");

		// ������������һ��'\n'�ַ�
		while ((temp = getchar()) != '\n')
			continue;

		printf("> ");
	}

	// ������������һ��'\n'�ַ�
	while ((temp = getchar()) != '\n')
		continue;

	return i;
}

// ---------------------------------------------------------------------------

// ��ӡ������Ϣ
// Ч������ӡ������Ϣ
void errinfo(void)
{
	printf("\033[31m");           // ������ɫ��ɫ
	printf("error");
	printf("\033[0m");            // ������ɫ

	fprintf(stderr, ": %s\n", strerror(errno));     // ���ú���strerror()��ӡ������Ϣ
}

// ---------------------------------------------------------------------------

// ��ӡ��Ч������ʾ
void invalid(void)
{
	printf("\033[31m");           // ������ɫ��ɫ
	printf("Invalid command or choice.\n");
	printf("\033[0m");            // ������ɫ
}

// ---------------------------------------------------------------------------

// ��ʼ������
// Ч��������Ӱ�����û��ļ�������ļ�������жϳ����Ƿ�����������
// ���أ�ʧ�ܣ�����0���ɹ�������1
int initialize_cinema(void)
{
	FILE* room_ptr, * user_ptr;           // room_ptr -- room�ļ�ָ��
	int i;                                // user_ptr -- user�ļ�ָ��

	// Ӱ���ļ�
	room_ptr = fopen(ROOMFILE, "rb");
	if (NULL == room_ptr)                      // room�ļ��Ƿ����
	{
		room_ptr = fopen(ROOMFILE, "wb");      // �����ڣ��������ļ�
		if (NULL == room_ptr)                  // ����ʧ�ܣ�����0
		{
			errinfo();
			return 0;
		}

		Room cinema[5] = { 0 };
		initialize_room(cinema);

		for (i = 0; i < 5; i++)
			if (1 != fwrite(&cinema[i], sizeof(Room), 1, room_ptr))
			{
				errinfo();
				fclose(room_ptr);

				if (0 == remove(ROOMFILE))
					printf("Succeed to delete '%s'", ROOMFILE);
				else
					printf("Fail to delete '%s'. Please delete the file manually", ROOMFILE);
				
				return 0;
			}

		fclose(room_ptr);
	}

	// �û��ļ�
	user_ptr = fopen(USERFILE, "rb");
	if (NULL == user_ptr)                        // user�ļ��Ƿ����
	{
		user_ptr = fopen(USERFILE, "wb");        // �����ڣ��������ļ�
		if (NULL == user_ptr)                    // ����ʧ�ܣ�����0
		{
			errinfo(errno);
			return 0;
		}

		fclose(user_ptr);
	}

	return 1;
}

// ---------------------------------------------------------------------------

// ��ʼ����ӳ��
// ������cinema[] -- �������з�ӳ�����ݵ�����
// Ч������ʼ����ӳ�����ƺ�ӰƬ���ƣ����޸���Ʊ��
void initialize_room(Room cinema[])
{
	int i;

	for (i = 0; i < 5; i++)
	{
		snprintf(cinema[i].room_name, ROOMNM, "Room%d", i);
		snprintf(cinema[i].film.film_name, FILMNM, "To be determined");
		cinema[i].remainings = ROW * COL;
	}
}

// ---------------------------------------------------------------------------

// �������˵�
// Ч������ӡ�������˵�
void menu(void)
{
	putchar('\n');
	printf(" ********************************************\n");
	printf(" *                                          *\n");
	printf("*        Movie Theater Ticketing System      *\n");
	printf(" *                                          *\n");
	printf(" ********************************************\n");
	printf("\nPlease choose your login type:\n\n");
	printf("1. Administrator Login          2. User Login\n");
	printf("0. Exit\n");
	printf("\nPlease only enter the number to continue.\n\n");
}

// ---------------------------------------------------------------------------

// ��ȡ�˻���Ϣ
// ������input -- �����˻���Ϣ�ı����ĵ�ַ
// Ч��������һ����ʽ��ȡ�˻���Ϣ
// ���أ�ʧ�ܣ�����NULL���ɹ������ر����ĵ�ַ
Account* get_account(Account* input)
{
	printf("> username: ");
	if (NULL == str_get(input->username, USRNM))
	{
		errinfo();
		return NULL;
	}

	printf("> password: ");
	if (NULL == str_get(input->passward, PSD))
	{
		errinfo();
		return NULL;
	}

	return input;
}

// ---------------------------------------------------------------------------

// ӰƬ��Ϣ
// Ч������ӡӰƬ��Ϣ
void movie_style(void)
{
	FILE* room_ptr;                          // room_ptr -- room�ļ�ָ��
	Room cinema[5];                          // Ӱ����Ϣ
	int i;

	room_ptr = fopen(ROOMFILE, "rb+");
	if (NULL == room_ptr)
	{
		errinfo(errno);
		return;
	}

	for (i = 0; i < 5; i++)
		if (1 != fread(&cinema[i], sizeof(Room), 1, room_ptr))
		{
			errinfo();
			fclose(room_ptr);
			return;
		}

	fclose(room_ptr);

	putchar('\n');
	printf(" ********************************************\n");
	printf(" *                                          *\n");
	printf("*               Movie List                   *\n");
	printf(" *                                          *\n");
	printf(" ********************************************\n");
	printf("\nRoom                Movie               Price     Date\n");
	for (i = 0; i < 5; i++)
		printf("%-20s%-20s%-10d%d/%d/%d\n", cinema[i].room_name,
			cinema[i].film.film_name, cinema[i].film.price,
			cinema[i].film.date.year, cinema[i].film.date.mouth, cinema[i].film.date.day);
	putchar('\n');
}

// ---------------------------------------------------------------------------