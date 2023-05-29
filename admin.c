#include "admin.h"
#include "cinema.h"

// 票房排序
static void box_sort(Room arr[]);

// 管理员账号和密码
Account admin_account = {
	"admin",
	"123"
};

// 管理员登入
// -1 -- 用户名错误；0 -- 密码错误；1 -- 账号正确
int admin_login(Account* input)
{
	if (0 != strcmp(input->username, admin_account.username))
		return -1;
	else
		if (0 != strcmp(input->passward, admin_account.passward))
			return 0;

	return 1;
}
// 管理员界面
void admin(Account* input)
{
	int num;

	admin_menu();
	do
	{
		printf("> ");
		switch (num = choice())
		{
		case 0:
			printf("Bye!\n");
			break;
		case 1:
			admin_arrange();
			admin_menu();
			break;
		case 2:
			admin_sale();
			admin_menu();
			break;
		case 3:
			admin_box();
			admin_menu();
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	} while (num);
}
// 管理员菜单
void admin_menu(void)
{
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
// 排片
void admin_arrange(void)
{
	FILE* room_ptr;
	Room cinema[5];
	int i, num;
	char film_name[FILMNM];
	char room_name[ROOMNM];
	int film_price;

	room_ptr = fopen(ROOMFILE, "rb");
	if (NULL == room_ptr)
	{
		errinfo(errno);
		return;
	}

	for (i = 0; i < 5; i++)
		fread(&cinema[i], sizeof(Room), 1, room_ptr);

	printf(" ********************************************\n");
	printf(" *                                          *\n");
	printf("*               Movie List                   *\n");
	printf(" *                                          *\n");
	printf(" ********************************************\n");
	printf("Room                Movie               Price\n");
	for (i = 0; i < 5; i++)
		printf("%-20s%-20s%d\n", cinema[i].room_name, 
			cinema[i].film.film_name, cinema[i].film.price);

	printf("Enter the room number (0-4)\n");
	printf("Enter '-1' to quit.\n");
	printf("> ");
	num = choice();
	while (num != -1)
	{
		if (num >= 0 && num <= 4)
		{
			printf("Enter the movie's name.\n");
			printf("> ");
			get_info(film_name, FILMNM);

			printf("Enter the movie's price.\n");
			printf("> ");
			film_price = choice();

			strcpy(room_name, cinema[num].room_name);
			fclose(room_ptr);
			admin_edit(room_name, film_name, film_price);
		}
		else
			printf("Enter the correct roon number.\n");

		printf("Enter the room number (0-4)\n");
		printf("Enter '-1' to quit.\n");
		printf("> ");
		num = choice();
	}

	// 现状
	room_ptr = fopen(ROOMFILE, "rb");
	if (NULL == room_ptr)
	{
		errinfo(errno);
		return;
	}

	for (i = 0; i < 5; i++)
		fread(&cinema[i], sizeof(Room), 1, room_ptr);

	printf("This is the arrangement:\n");
	printf(" ********************************************\n");
	printf(" *                                          *\n");
	printf("*               Movie List                   *\n");
	printf(" *                                          *\n");
	printf(" ********************************************\n");
	printf("Room                Movie              Price\n");
	for (i = 0; i < 5; i++)
		printf("%-20s%-20s%d\n", cinema[i].room_name, 
			cinema[i].film.film_name, cinema[i].film.price);

	fclose(room_ptr);
}
// 查看票款
void admin_sale(void)
{
	FILE* room_ptr;
	Room cinema[5];
	int i, num;
	char film_name[FILMNM];
	char room_name[ROOMNM];

	room_ptr = fopen(ROOMFILE, "rb");
	if (NULL == room_ptr)
	{
		errinfo(errno);
		return;
	}

	for (i = 0; i < 5; i++)
		fread(&cinema[i], sizeof(Room), 1, room_ptr);

	printf(" ********************************************\n");
	printf(" *                                          *\n");
	printf("*               Movie List                   *\n");
	printf(" *                                          *\n");
	printf(" ********************************************\n");
	printf("Room                Movie              Price\n");
	for (i = 0; i < 5; i++)
		printf("%-20s%-20s%d\n", cinema[i].room_name,
			cinema[i].film.film_name, cinema[i].film.price);

	printf("Which movie's sales you want to count?\n");
	printf("Please enter the room number (0-4)\n");
	printf("Enter '-1' to quit.\n");
	printf("> ");
	num = choice();
	while (num != -1)
	{
		if (num >= 0 && num <= 4)
		{
			printf(" ********************************************\n");
			printf(" *                                          *\n");
			printf("*               Movie sales                  *\n");
			printf(" *                                          *\n");
			printf(" ********************************************\n");
			//printf("Room               Movie              Price     Sales\n");

			strcpy(film_name, cinema[num].film.film_name);
			admin_count(film_name);
		}
		else
			printf("Enter the correct roon number.\n");

		printf("Enter the room number (0-4)\n");
		printf("Enter '-1' to quit.\n");
		printf("> ");
		num = choice();
	}

	fclose(room_ptr);
}
// 票房排序
void admin_box(void)
{
	FILE* room_ptr;
	Room cinema[5];
	int i;

	room_ptr = fopen(ROOMFILE, "rb");
	if (NULL == room_ptr)
	{
		errinfo(errno);
		return;
	}

	for (i = 0; i < 5; i++)
		fread(&cinema[i], sizeof(Room), 1, room_ptr);

	box_sort(cinema);
	printf(" ********************************************\n");
	printf(" *                                          *\n");
	printf("*               Movie boxes                  *\n");
	printf(" *                                          *\n");
	printf(" ********************************************\n");
	printf("Room              Movie             Price     boxes\n");
	for (i = 0; i < 5; i++)
		printf("%-20s%-20s%-10d%d\n", cinema[i].room_name, cinema[i].film.film_name,
			cinema[i].film.price, cinema[i].sales);

	fclose(room_ptr);
}

// 修改电影
void admin_edit(char* dest, char* name, int price)
{
	FILE* room_ptr;
	Room cinema[5];
	int i;

	room_ptr = fopen(ROOMFILE, "rb+");
	if (NULL == room_ptr)
	{
		errinfo(errno);
		return;
	}

	for (i = 0; i < 5; i++)
		fread(&cinema[i], sizeof(Room), 1, room_ptr);

	for (i = 0; i < 5; i++)
		if (0 == strcmp(dest, cinema[i].room_name))
		{
			strcpy(cinema[i].film.film_name, name);
			cinema[i].film.price = price;
			break;
		}

	rewind(room_ptr);
	for (i = 0; i < 5; i++)
		fwrite(&cinema[i], sizeof(Room), 1, room_ptr);

	fclose(room_ptr);
}
// 查看电影票款
void admin_count(char* str)
{
	FILE* room_ptr;
	Room cinema[5];
	int i;

	room_ptr = fopen(ROOMFILE, "rb");
	if (NULL == room_ptr)
	{
		errinfo(errno);
		return;
	}

	for (i = 0; i < 5; i++)
		fread(&cinema[i], sizeof(Room), 1, room_ptr);
	
	for (i = 0; i < 5; i++)
		if (0 == strcmp(str, cinema[i].film.film_name))
		{
			printf("Room                Movie               Price     Sales\n");
			printf("%-20s%-20s%-10d%d\n", cinema[i].room_name, cinema[i].film.film_name,
				cinema[i].film.price, cinema[i].sales);
			break;
		}

	fclose(room_ptr);
}


// 票房排序
static void box_sort(Room arr[])
{
	int i, j;
	Room temp;

	for (i = 0; i < 4; i++) 
	{
		for (j = 0; j < 4 - i; j++)
		{
			if (arr[j].sales < arr[j + 1].sales) 
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}