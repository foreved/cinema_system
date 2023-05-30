#include "admin.h"
#include "cinema.h"

// ---------------------------------------------------------------------------
// 函数声明
// --------------------------------------------------------------------------- 
static void box_sort(Room arr[]);          // 票房排序

// 管理员账号和密码
Account admin_account = {
	"admin",
	"123"
};

// ---------------------------------------------------------------------------
// 函数定义
// ---------------------------------------------------------------------------

// 管理员登入
// 参数：input -- 输入账户信息变量的指针
// 效果：验证管理员账户是否正确
// 返回：-1 -- 用户名错误；0 -- 密码错误；1 -- 登入成功
int admin_login(Account* input)
{
	if (0 != strcmp(input->username, admin_account.username))
		return -1;
	else
		if (0 != strcmp(input->passward, admin_account.passward))
			return 0;

	return 1;
}

// ---------------------------------------------------------------------------

// 管理员界面
// 参数：input -- 用户的登入信息
void admin(Account* input)
{
	int i;

	while (1)
	{
		admin_menu();                          // 打印管理员菜单
		printf("> ");
		if (NULL == i_get(&i))                 // 获取用户输入，若失败，结束程序
			exit(1);

		switch (i)
		{
		case 0:
			printf("\nBye!\n");
			break;
		case 1:
			admin_arrange();                    // 管理员排片
			break;
		case 2:
			admin_sale();                       // 管理员查看电影票款
			break;
		case 3:
			admin_box();                        // 管理员查看票房
			break;
		default:
			invalid();
			break;
		}

		if (0 == i)          // 结束函数
			break;
	}

}

// ---------------------------------------------------------------------------

// 管理员菜单
// 效果：打印管理员菜单
void admin_menu(void)
{
	putchar('\n');
	printf(" ********************************************\n");
	printf(" *                                          *\n");
	printf("*           Administrator Interface          *\n");
	printf(" *                                          *\n");
	printf(" ********************************************\n");
	printf("\nPlease select an option:\n\n");
	printf("1. Schedule Movies\n");
	printf("2. Ticket Sales\n");
	printf("3. Box Office Ranking\n");
	printf("0. Logout\n");
	printf("\nPlease only enter the number to continue.\n\n");
}

// ---------------------------------------------------------------------------

// 管理员排片
// 效果：进行排片
void admin_arrange(void)
{
	FILE* room_ptr;                          // room_ptr -- room文件指针
	Room cinema[5];                          // 影厅信息
	Movie film;                              // 待填入的影片信息
	int i, num;

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

	// 重置文件指针
	rewind(room_ptr);

	// 未修改前的排片
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

	// 修改阶段
	while (1)
	{

		printf("Enter the room number (0-4).\n");
		printf("Enter '-1' to quit.\n");
		printf("> ");
		if (NULL == i_get(&num))                 // 获取用户输入，若失败，结束程序
			exit(1);

		if (-1 == num)                      // 结束排片
		{
			break;
		}

		if (num >= 0 && num <= 4)           // 进行排片
		{
			// 影厅名称
			snprintf(film.room_name, ROOMNM, "%s", cinema[num].room_name);
			// 电影名称
			printf("Enter the movie's name.\n");
			printf("> ");
			if (NULL == str_get(film.film_name, FILMNM))
			{
				fclose(room_ptr);
				return;
			}
			// 电影价格
			printf("Enter the movie's price.\n");
			printf("> ");
			if (NULL == i_get(&film.price))
			{
				fclose(room_ptr);
				return;
			}
			// 电影日期
			printf("Enter the movie's date.\n");
			printf("> year: ");                         // 年
			if (NULL == i_get(&film.date.year))
			{
				fclose(room_ptr);
				return;
			}
			printf("> mouth: ");                        // 月
			if (NULL == i_get(&film.date.mouth))
			{
				fclose(room_ptr);
				return;
			}
			printf("> day: ");                          // 日
			if (NULL == i_get(&film.date.day))
			{
				fclose(room_ptr);
				return;
			}

			// 修改影厅信息
			cinema[num].film = film;

			// 写入文件
			for (i = 0; i < 5; i++)
				if (1 != fwrite(&cinema[i], sizeof(Room), 1, room_ptr))
				{
					errinfo();
					fclose(room_ptr);
					return;
				}

			fflush(room_ptr);
			rewind(room_ptr);
		}
		else
			invalid();
	}

	for (i = 0; i < 5; i++)
		if (1 != fread(&cinema[i], sizeof(Room), 1, room_ptr))
		{
			errinfo();
			fclose(room_ptr);
			return;
		}

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

	fclose(room_ptr);
}

// ---------------------------------------------------------------------------

// 查看票款
void admin_sale(void)
{
	FILE* room_ptr;                           // room_ptr -- room文件指针
	Room cinema[5];                           // 影厅信息
	int i, num;

	char film_name[FILMNM];
	char room_name[ROOMNM];

	// 读取影厅信息
	room_ptr = fopen(ROOMFILE, "rb");
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

	// 影厅信息 
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

	while (1)
	{

		printf("Enter the room number (0-4).\n");
		printf("Enter '-1' to quit.\n");
		printf("> ");
		if (NULL == i_get(&num))                 // 获取用户输入，若失败，结束程序
			exit(1);

		if (-1 == num)                           // 结束查询票款
		{
			fclose(room_ptr);
			return;
		}

		// 查询票款
		if (num >= 0 && num <= 4)
		{
			putchar('\n');
			printf(" ********************************************\n");
			printf(" *                                          *\n");
			printf("*               Movie sales                  *\n");
			printf(" *                                          *\n");
			printf(" ********************************************\n");
			printf("\nRoom                Movie               Price     Sales\n");
			printf("%-20s%-20s%-10d%d\n", cinema[num].room_name, cinema[num].film.film_name,
					cinema[num].film.price, cinema[num].sales);
			putchar('\n');
		}
		else
			invalid();
	}
	fclose(room_ptr);
}

// ---------------------------------------------------------------------------

// 查看票房
// 效果：计算电影票房，并进行排序
void admin_box(void)
{
	FILE* room_ptr;
	Room cinema[5];
	int i;

	// 读取影厅信息
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

	// 重置指针
	rewind(room_ptr);

	// 计算票房
	for (i = 0; i < 5; i++)
		cinema[i].boxes = cinema[i].sales * cinema[i].film.price;

	// 写入文件
	for (i = 0; i < 5; i++)
		if (1 != fwrite(&cinema[i], sizeof(Room), 1, room_ptr))
		{
			errinfo();
			fclose(room_ptr);
			return;
		}

	// 进行票房排序
	box_sort(cinema);

	// 打印票房
	putchar('\n');
	printf(" ********************************************\n");
	printf(" *                                          *\n");
	printf("*               Movie boxes                  *\n");
	printf(" *                                          *\n");
	printf(" ********************************************\n");
	printf("\nRoom                Movie             Price     boxes\n");
	for (i = 0; i < 5; i++)
		printf("%-20s%-20s%-10d%d\n", cinema[i].room_name, cinema[i].film.film_name,
			cinema[i].film.price, cinema[i].boxes);
	putchar('\n');

	fclose(room_ptr);
}

// ---------------------------------------------------------------------------

// 票房排序
static void box_sort(Room arr[])
{
	int i, j;
	Room temp;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4 - i; j++)
		{
			if (arr[j].boxes < arr[j + 1].boxes)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

// ---------------------------------------------------------------------------
