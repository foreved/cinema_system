#include "cinema.h"

// ��ʼ������
int initialize_cinema(void)
{
	FILE* room_ptr;
	int i;

	room_ptr = fopen(ROOMFILE, "r");
	if (NULL == room_ptr)
	{
		room_ptr = fopen(ROOMFILE, "w");
		if (NULL == room_ptr)
		{
			errinfo(errno);
			return 0;
		}

		Room cinema[5] = { 0 };
		initialize_room(cinema);

		for (i = 0; i < 5; i++)
			fwrite(&cinema[i], sizeof(Room), 1, room_ptr);

		fclose(room_ptr);
	}

	return 1;
}
// ��ʼ����ӳ��
static void initialize_room(Room cinema[])
{
	int i;

	for (i = 0; i < 5; i++)
	{
		sprintf(cinema[i].room_name, "Room%d", i);
		strcpy(cinema[i].film_name, "To be determined");
		cinema[i].remainings = ROW * COL;
	}
}
// �������
void menu(void)
{
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
// ��ȡ�˺ź�����
Account* get_account(Account* input)
{
	printf("> username: ");
	get_info(input->username, USRNM);
	printf("> password: ");
	get_info(input->passward, PSD);

	return input;
}
// ��ȡѡ��
int choice(void)
{
	int num;
	char ch;

	printf("> ");
	scanf("%d", &num);
	while ((ch = getchar()) != '\n')
		continue;

	return num;
}
// ��ȡ�ַ�ѡ��
char ch_choice(void)
{	
	char ch, input;

	printf("> ");
	scanf("%c", &input);
	while ((ch = getchar()) != '\n')
		continue;

	return input;
}



// ��ȡ������Ϣ
// ptr --������Ϣ��ָ�룻num -- ���ն��ٸ��ַ�
char* get_info(char* ptr, int num)
{
	//char* tmp;
	int i, flag;
	char ch;

	/*tmp = (char*)malloc(sizeof(char) * num);
	if (NULL == tmp)
	{
		errinfo(errno);
		exit(1);
	}

	fgets(tmp, num, stdin);
	if (NULL == tmp)
	{
		errinfo(errno);
		exit(1);
	}*/

	fgets(ptr, num, stdin);

	flag = 1;                                // Ĭ�ϻ�������ʣ���ַ�
	for (i = 0; i < strlen(ptr); i++)        // ȥ�������е�\n
		if ('\n' == ptr[i])
		{
			ptr[i] = '\0';
			flag = 0;                        // flag����
			break;
		}
	if (flag)
		while ((ch = getchar()) != '\n')     // ������������ַ�
			continue;

	//ptr = tmp;
	//tmp = NULL;

	return ptr;
}

// ��ӡ������Ϣ
void errinfo(int error_code)
{
	printf("\033[31m");           // ������ɫ��ɫ
	printf("error");
	printf("\033[0m");            // ������ɫ

	fprintf(stderr, ": %s\n", strerror(error_code));
}