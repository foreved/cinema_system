#include "cinema.h"

// ---------------------------------------------------------------------------
// 函数定义
// ---------------------------------------------------------------------------

// 获取字符串
// 参数：str -- 接收字符串的变量的地址；num -- 允许接收的最大字符数
// 效果：从stdin获取指定大小的字符串，去掉其中的'\n'，并刷新缓冲区
// 返回：失败，返回NULL；成功，返回变量的地址
char* str_get(char* str, int num)
{
	int i, flag;                             // flag: 1 -- 刷新缓冲区；0 -- 无操作
	char ch;

	if (NULL == fgets(str, num, stdin))      // 获取失败
	{
		errinfo();                           // 打印错误信息
		return NULL;                         // 返回NULL
	}

	flag = 1;                                // 默认缓冲区有剩余字符

	for (i = 0; i < strlen(str); i++)        // 去除字符串中的'\n'
		if ('\n' == str[i])
		{
			str[i] = '\0';
			flag = 0;                        // flag置零
			break;
		}
	if (flag)
		while ((ch = getchar()) != '\n')     // 清除缓冲区的字符
			continue;

	return str;
}

// ---------------------------------------------------------------------------

// 获取字符
// 参数：ch -- 接收字符的变量的地址
// 效果：从stdin获取一个字符，并刷新缓冲区
// 返回：失败，返回NULL；成功：返回变量的地址
char* ch_get(char* ch)
{
	char temp;

	if (1 != scanf("%c", ch))              // 获取失败
	{
		errinfo();                         // 打印错误信息
		return NULL;                       // 返回NULL
	}

	// 缓冲区至少有一个'\n'字符
	while ((temp = getchar()) != '\n')
		continue;

	return ch;
}

// ---------------------------------------------------------------------------

// 获取整数
// 参数：i -- 接收整数的变量的地址
// 效果：从stdin获取一个整数，并刷新缓冲区
// 返回：失败，返回NULL；成功：返回变量的地址
int* i_get(int* i)
{
	char temp;

	while (1 != scanf("%d", i))
	{
		printf("Please enter an ");
		printf("\033[31m");           // 字体颜色红色
		printf("integer");
		printf("\033[0m");            // 重置颜色
		printf(".\n");

		// 缓冲区至少有一个'\n'字符
		while ((temp = getchar()) != '\n')
			continue;

		printf("> ");
	}

	// 缓冲区至少有一个'\n'字符
	while ((temp = getchar()) != '\n')
		continue;

	return i;
}

// ---------------------------------------------------------------------------

// 打印错误信息
// 效果：打印错误信息
void errinfo(void)
{
	printf("\033[31m");           // 字体颜色红色
	printf("error");
	printf("\033[0m");            // 重置颜色

	fprintf(stderr, ": %s\n", strerror(errno));     // 调用函数strerror()打印错误信息
}

// ---------------------------------------------------------------------------

// 打印无效命令提示
void invalid(void)
{
	printf("\033[31m");           // 字体颜色红色
	printf("Invalid command or choice.\n");
	printf("\033[0m");            // 重置颜色
}

// ---------------------------------------------------------------------------

// 初始化程序
// 效果：生成影厅和用户文件，检测文件情况，判断程序是否能正常运行
// 返回：失败，返回0；成功，返回1
int initialize_cinema(void)
{
	FILE* room_ptr, * user_ptr;           // room_ptr -- room文件指针
	int i;                                // user_ptr -- user文件指针

	// 影厅文件
	room_ptr = fopen(ROOMFILE, "rb");
	if (NULL == room_ptr)                      // room文件是否存在
	{
		room_ptr = fopen(ROOMFILE, "wb");      // 不存在，创建新文件
		if (NULL == room_ptr)                  // 创建失败，返回0
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

	// 用户文件
	user_ptr = fopen(USERFILE, "rb");
	if (NULL == user_ptr)                        // user文件是否存在
	{
		user_ptr = fopen(USERFILE, "wb");        // 不存在，创建新文件
		if (NULL == user_ptr)                    // 创建失败，返回0
		{
			errinfo(errno);
			return 0;
		}

		fclose(user_ptr);
	}

	return 1;
}

// ---------------------------------------------------------------------------

// 初始化放映厅
// 参数：cinema[] -- 包含所有放映厅数据的数组
// 效果：初始化放映厅名称和影片名称，并修改余票数
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

// 程序主菜单
// 效果：打印程序主菜单
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

// 获取账户信息
// 参数：input -- 接收账户信息的变量的地址
// 效果：按照一定格式获取账户信息
// 返回：失败，返回NULL；成功，返回变量的地址
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

// 影片信息
// 效果：打印影片信息
void movie_style(void)
{
	FILE* room_ptr;                          // room_ptr -- room文件指针
	Room cinema[5];                          // 影厅信息
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