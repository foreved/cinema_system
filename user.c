#include "user.h"
#include "cinema.h"

// 用户登入
int user_login(Account* input)
{
	UserAccount temp;
	FILE* user_ptr;

	user_ptr = fopen(USERFILE, "rb");
	if (NULL == user_ptr)
	{
		errinfo(errno);
		fclose(user_ptr);
		return -1;
	}

	while (1 == fread(&temp, sizeof(UserAccount), 1, user_ptr))
	{
		if (0 != strcmp(input->username, temp.user_account.username))
			continue;
		else
			if (0 != strcmp(input->passward, temp.user_account.passward))
			{
				fclose(user_ptr);
				return 0;
			}
			else
			{
				fclose(user_ptr);
				return 1;
			}
	}

	if (!feof(user_ptr)) 
	{
		errinfo(errno);
		fclose(user_ptr);
		return -1;
	}

	fclose(user_ptr);
	return -1;
}
// 用户界面
void user(Account* input)
{
	int num;

	do
	{
		user_menu();
		printf("> ");
		num = choice();

		switch (num)
		{
		case 1:
			user_movie();
			break;
		case 2:
			user_buy(input);
			break;
		case 3:
			user_return(input);
			break;
		case 0:
			printf("Bye!\n");
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	} while (num);
}
// 用户菜单
void user_menu(void)
{
	printf(" ********************************************\n");
	printf(" *                                          *\n");
	printf("*              User Interface                *\n");
	printf(" *                                          *\n");
	printf(" ********************************************\n");
	printf("\nPlease select an option:\n\n");
	printf("1. Browse Movie Information\n");
	printf("2. Select Seat and Buy Ticket\n");
	printf("3. Return Ticket\n");
	printf("0. Logout\n");
	printf("\nPlease only enter the number to continue.\n\n");
}
// 用户注册
int user_register(Account* input)
{
	UserAccount temp;
	FILE* user_ptr;
	int i;

	user_ptr = fopen(USERFILE, "rb+");
	if (NULL == user_ptr)
	{
		errinfo(errno);
		return -1;
	}

	while (1 == fread(&temp, sizeof(UserAccount), 1, user_ptr))
		if (0 == strcmp(input->username, temp.user_account.username))
			return 0;

	if (!feof(user_ptr))
	{
		errinfo(errno);
		return -1;
	}

	temp.user_account = *input;
	for (i = 0; i < TICKETS; i++)
		temp.tickets[i].flag = 0;

	if (1 == fwrite(&temp, sizeof(UserAccount), 1, user_ptr))
	{
		fflush(user_ptr);
		fclose(user_ptr);
		return 1;
	}
	else
	{
		errinfo(errno);
		return -1;
	}
}
// 用户浏览影片信息
void user_movie(void)
{
	FILE* room_ptr;
	Room cinema[5];
	int i;

	room_ptr = fopen(ROOMFILE, "rb");
	if (NULL == room_ptr)
	{
		errinfo(errno);
		fclose(room_ptr);
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
}
// 用户购票
void user_buy(Account* input)
{
	UserAccount temp;
	Room cinema[5];
	FILE* user_ptr, *room_ptr;
	int row, col;
	int num, i, j;
	char ch;

	/*room_ptr = fopen(ROOMFILE, "rb+");
	if (NULL == room_ptr)
	{
		errinfo(errno);
		fclose(room_ptr);
		return;
	}
	for (i = 0; i < 5; i++)
		fread(&cinema[i], sizeof(Room), 1, room_ptr);
	rewind(room_ptr);

	user_ptr = fopen(USERFILE, "rb+");
	if (NULL == user_ptr)
	{
		errinfo(errno);
		fclose(user_ptr);
		return;
	}

	while (1 == fread(&temp, sizeof(UserAccount), 1, user_ptr))
		if ((0 == strcmp(input->username, temp.user_account.username)) &&
			(0 == strcmp(input->passward, temp.user_account.passward)))
		{
			fseek(user_ptr, -(long int)sizeof(UserAccount), SEEK_CUR);
			break;
		}*/

	do
	{
		room_ptr = fopen(ROOMFILE, "rb+");
		if (NULL == room_ptr)
		{
			errinfo(errno);
			fclose(room_ptr);
			return;
		}
		for (i = 0; i < 5; i++)
			fread(&cinema[i], sizeof(Room), 1, room_ptr);
		rewind(room_ptr);

		user_ptr = fopen(USERFILE, "rb+");
		if (NULL == user_ptr)
		{
			errinfo(errno);
			fclose(user_ptr);
			return;
		}

		while (1 == fread(&temp, sizeof(UserAccount), 1, user_ptr))
			if ((0 == strcmp(input->username, temp.user_account.username)) &&
				(0 == strcmp(input->passward, temp.user_account.passward)))
			{
				fseek(user_ptr, -(long int)sizeof(UserAccount), SEEK_CUR);
				break;
			}

		user_movie();
		printf("Which movie you want to buy?\n");
		printf("Please enter the room number to slect the seat, \n");
		printf("like 0-4. (enter '-1' to quit)\n");
		printf("> ");
		num = choice();
		if (-1 == num)
			break;
		else if (num < 0 || num > 4)
		{
			printf("Invalid number!\n");
			continue;
		}

		printf("\n\nRoom               Movie              Price\n");
		printf("%-20s%-20s%d\n\n\n", cinema[num].room_name,
			cinema[num].film.film_name, cinema[num].film.price);
		printf(" ======SCREEN===== \n\n");
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COL; j++)
				if (0 == cinema[num].seats.seats[i][j])
					printf("\u25A1 ");   // 空心方块 -- 未售
				else
					printf("\u25CF ");   // 实心圆 -- 已售

			putchar('\n');
		}
		printf("\n\u25A1：未售	\u25CF：已售\n\n");

		printf("If you want to buy the ticket?(y/n) > ");
		ch = ch_choice();
		while ('y' != ch && 'n' != ch)
		{
			printf("Invalid command! Please enter again.(y/n) > ");
			ch = ch_choice();
		}
		if ('n' == ch)
			continue;
		do
		{
			printf("Please enter the coordinate of the seat.\n");
			printf("Enter the row.(0-%d) > ", ROW - 1);
			row = choice();
			while (row < 0 || row > ROW - 1)
			{
				printf("Invalid row.\n");
				printf("Enter the row.(0-%d) > ", ROW - 1);
				row = choice();
			}
			printf("Enter the column.(0-%d) > ", COL - 1);
			col = choice();
			while (col < 0 || col > COL - 1)
			{
				printf("Invalid column.\n");
				printf("Enter the column.(0-%d) > ", COL - 1);
				col = choice();
			}

			if (cinema[num].seats.seats[row][col])
				printf("该位置票已售出，请重新选择\n");

		} while (cinema[num].seats.seats[row][col]);

		printf("Are you sure to buy the ticket?(y/n) > ");
		ch = ch_choice();
		while ('y' != ch && 'n' != ch)
		{
			printf("Invalid command! Please enter again.(y/n) > ");
			ch = ch_choice();
		}
		if ('n' == ch)
			continue;
		
		// 完成购票
		for (i = 0; i < TICKETS; i++)
			if (0 == temp.tickets[i].flag)
				break;

		if (i >= TICKETS)
		{
			printf("已达购票上限\n");
			continue;
		}

		// 顾客
		temp.tickets[i].flag = 1;
		strcpy(temp.tickets[i].room_name, cinema[num].room_name);
		temp.tickets[i].film = cinema[num].film;
		temp.tickets[i].seat.seats[row][col] = 1;

		if (1 != fwrite(&temp, sizeof(UserAccount), 1, user_ptr))
		{
			errinfo(errno);
			printf("购买失败\n");
			continue;
		}

		// 影厅
		cinema[num].seats.seats[row][col] = 1;
		cinema[num].sales += 1;
		cinema[num].remainings -= 1;
		for (i = 0; i < 5; i++)
		{
			if (1 != fwrite(&cinema[i], sizeof(Room), 1, room_ptr))
			{
				errinfo(errno);
				printf("购买失败\n");

				// 因购买失败，对用户购票进行取消
				temp.tickets[i].flag = 0;
				fseek(user_ptr, -1, SEEK_CUR);
				fwrite(&temp, sizeof(UserAccount), 1, user_ptr);

				continue;
			}
		}

		//if (1 != fwrite(&cinema[num], sizeof(Room), 1, room_ptr))
		//{
		//	errinfo(errno);
		//	printf("购买失败\n");

		//	// 因购买失败，对用户购票进行取消
		//	temp.tickets[i].flag = 0;
		//	fseek(user_ptr, -1, SEEK_CUR);
		//	fwrite(&temp, sizeof(UserAccount), 1, user_ptr);

		//	continue;
		//}

		/*fflush(user_ptr);
		fflush(room_ptr);*/

		fclose(user_ptr);
		fclose(room_ptr);

		printf("购买成功\n");
	} while (-1 != num);

	printf("谢谢惠顾！\n");
}
// 用户退票
void user_return(Account* input)
{

}