#include "cinema.h"

// 初始化程序
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
// 初始化放映厅
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
// 登入界面
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
// 获取账号和密码
Account* get_account(Account* input)
{
	printf("> username: ");
	get_info(input->username, USRNM);
	printf("> password: ");
	get_info(input->passward, PSD);

	return input;
}
// 获取选项
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
// 获取字符选项
char ch_choice(void)
{	
	char ch, input;

	printf("> ");
	scanf("%c", &input);
	while ((ch = getchar()) != '\n')
		continue;

	return input;
}



// 获取输入信息
// ptr --接收信息的指针；num -- 接收多少个字符
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

	flag = 1;                                // 默认缓冲区有剩余字符
	for (i = 0; i < strlen(ptr); i++)        // 去除命令中的\n
		if ('\n' == ptr[i])
		{
			ptr[i] = '\0';
			flag = 0;                        // flag置零
			break;
		}
	if (flag)
		while ((ch = getchar()) != '\n')     // 清除缓冲区的字符
			continue;

	//ptr = tmp;
	//tmp = NULL;

	return ptr;
}

// 打印错误信息
void errinfo(int error_code)
{
	printf("\033[31m");           // 字体颜色红色
	printf("error");
	printf("\033[0m");            // 重置颜色

	fprintf(stderr, ": %s\n", strerror(error_code));
}