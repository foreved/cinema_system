#include "user.h"
#include "cinema.h"

// ---------------------------------------------------------------------------
// 函数定义
// ---------------------------------------------------------------------------

// 用户登入
// 效果：验证账户
// 返回：-1 -- 账户不存在；0 -- 密码错误；1 -- 登入成功
int user_login(Account* input)
{
	UserAccount temp;
	FILE* user_ptr;

	user_ptr = fopen(USERFILE, "rb");
	if (NULL == user_ptr)                      // 用户文件打开失败，退出程序
	{
		errinfo(errno);
		exit(1);
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

	if (!feof(user_ptr))                // 指针未到EOF处，存在问题，退出程序
	{
		errinfo(errno);
		fclose(user_ptr);
		exit(1);
	}

	fclose(user_ptr);
	return -1;
}

// ---------------------------------------------------------------------------

// 用户界面
void user(Account* input)
{
	int i;

	while (1)
	{
		user_menu();
		printf("> ");
		if (NULL == i_get(&i))                 // 获取用户输入，若失败，结束程序
			exit(1);

		switch (i)
		{
		case 0:                                // 退出用户账户
			printf("\nBye!\n");
			break;
		case 1:
			user_movie();                      // 浏览影片信息
			break;
		case 2:
			user_buy(input);                   // 购买电影票
			break;
		case 3:
			user_return(input);                // 退票
			break;
		case 4:
			user_history(input);               // 历史记录
		default:
			invalid();
			break;
		}

		if (0 == i)          // 结束函数
			break;
	} 
}

// ---------------------------------------------------------------------------

// 用户注册
// 效果：为不存在的用户名注册账户
int user_register(Account* input)
{
	UserAccount temp;
	UserAccount new_account = { 0 };
	FILE* user_ptr;
	int i, j, k;

	user_ptr = fopen(USERFILE, "rb+");
	if (NULL == user_ptr)
	{
		errinfo(errno);
		return -1;
	}

	while (1 == fread(&temp, sizeof(UserAccount), 1, user_ptr))       // 用户名是否存在
		if (0 == strcmp(input->username, temp.user_account.username))
			return 0;                               // 用户名已存在

	if (!feof(user_ptr))    // 指针未到文件末尾
	{
		errinfo(errno);
		return -1;
	}

	new_account.user_account = *input;   // 写入用户信息
	if (1 == fwrite(&new_account, sizeof(UserAccount), 1, user_ptr))
	{
		fclose(user_ptr);
		return 1;                         // 注册成功
	}
	else
	{
		errinfo(errno);
		return -1;                        // 注册失败
	}
}

// ---------------------------------------------------------------------------

// 用户菜单
void user_menu(void)
{
	putchar('\n');
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

// ---------------------------------------------------------------------------

// 用户浏览影片信息
void user_movie(void)
{
	movie_style();                    // 打印影片信息
}

// ---------------------------------------------------------------------------

// 用户购票
void user_buy(Account* input)
{
	UserAccount temp;
	Room cinema[5];
	Record record;
	FILE* user_ptr, * room_ptr;
	int row, col;
	int num, i, j;
	char ch;

	// 读取影厅信息
	room_ptr = fopen(ROOMFILE, "rb+");
	if (NULL == room_ptr)
	{
		errinfo(errno);
		fclose(room_ptr);
		return;
	}
	for (i = 0; i < 5; i++)
		if (1 != fread(&cinema[i], sizeof(Room), 1, room_ptr))
		{
			errinfo();
			fclose(room_ptr);
			return;
		}

	rewind(room_ptr);        // 重置文件指针，便于后来写入

	// 用户信息
	user_ptr = fopen(USERFILE, "rb+");
	if (NULL == user_ptr)
	{
		errinfo(errno);
		fclose(user_ptr);
		return;
	}

	while (1 == fread(&temp, sizeof(UserAccount), 1, user_ptr))     // 寻找该用户账户并读取信息
		if ((0 == strcmp(input->username, temp.user_account.username)) &&
			(0 == strcmp(input->passward, temp.user_account.passward)))
		{
			fseek(user_ptr, -(long int)sizeof(UserAccount), SEEK_CUR);  // 文件指针后退一个，便于后来重新写入
			break;
		}

	while (1)
	{
		user_movie();
		printf("Which movie you want to buy?\n");
		printf("Please enter the room number to slect the seat, ");
		printf("like 0-4. (enter '-1' to quit)\n");
		printf("> ");
		i_get(&num);

		if (-1 == num)
		{
			fclose(user_ptr);
			fclose(room_ptr);
			break;
		}
		else if (num < 0 || num > 4)
		{
			invalid();
			continue;
		}

		printf("\nRoom                Movie               Price     Date\n");
		printf("%-20s%-20s%-10d%d/%d/%d\n", cinema[num].room_name, 
			cinema[num].film.film_name, cinema[num].film.price, 
			cinema[num].film.date.year, cinema[num].film.date.mouth, cinema[num].film.date.day);
		putchar('\n');

		printf(" ======SCREEN===== \n\n");
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COL; j++)
				if (0 == cinema[num].seat.seats[i][j])
					printf("\u25A1 ");   // 空心方块 -- 未售
				else
					printf("\u25CF ");   // 实心圆 -- 已售

			putchar('\n');
		}
		printf("\n\u25A1：未售	\u25CF：已售\n\n");

		printf("If you want to buy the ticket?(y/n) > ");
		ch_get(&ch);
		while ('y' != ch && 'n' != ch)
		{
			invalid();
			printf("Please enter again.(y/n) > ");
			ch_get(&ch);
		}
		if ('n' == ch)
		{
			continue;
		}
		do
		{
			// 行
			printf("Please enter the coordinate of the seat.\n");
			printf("Enter the row.(0-%d) > ", ROW - 1);
			i_get(&row);
			while (row < 0 || row > ROW - 1)
			{
				invalid();
				printf("Enter the row.(0-%d) > ", ROW - 1);
				i_get(&row);
			}

			// 列
			printf("Enter the column.(0-%d) > ", COL - 1);
			i_get(&col);
			while (col < 0 || col > COL - 1)
			{
				invalid();
				printf("Enter the column.(0-%d) > ", COL - 1);
				i_get(&col);
			}

			if (cinema[num].seat.seats[row][col])
				printf("该位置票已售出，请重新选择\n");

		} while (cinema[num].seat.seats[row][col]);

		printf("Are you sure to buy the ticket?(y/n) > ");
		ch_get(&ch);
		while ('y' != ch && 'n' != ch)
		{
			invalid();
			printf("Please enter again.(y/n) > ");
			ch_get(&ch);
		}
		if ('n' == ch)
		{
			continue;
		}

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
		record.flag = 1;
		record.film = cinema[num].film;
		record.seat.seats[row][col] = 1;
		record.row = row;
		record.col = col;
		// 购票记录
		temp.tickets[i] = record;
		// 历史记录
		// 带实现

		if (1 != fwrite(&temp, sizeof(UserAccount), 1, user_ptr))
		{
			errinfo(errno);
			printf("购买失败\n");
			continue;
		}
		fseek(user_ptr, -(long int)sizeof(UserAccount), SEEK_CUR);  // 文件指针后退一个，便于后来重新写入

		// 影厅
		cinema[num].seat.seats[row][col] = 1;
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
				fseek(user_ptr, -(long int)sizeof(UserAccount), SEEK_CUR);  // 文件指针后退一个，便于后来重新写入
				continue;
			}
		}
		rewind(room_ptr);        // 重置文件指针，便于后来写入

		printf("购买成功\n");
	}

	fclose(user_ptr);
	fclose(room_ptr);
	printf("谢谢惠顾！\n");
}

// ---------------------------------------------------------------------------

// 用户退票
void user_return(Account* input)
{
	UserAccount temp;
	Room cinema[5];
	FILE* user_ptr, * room_ptr;
	int row, col;
	int num, i, j, k;
	char ch;

	// 读取影厅信息
	room_ptr = fopen(ROOMFILE, "rb+");
	if (NULL == room_ptr)
	{
		errinfo(errno);
		fclose(room_ptr);
		return;
	}
	for (i = 0; i < 5; i++)
		if (1 != fread(&cinema[i], sizeof(Room), 1, room_ptr))
		{
			errinfo();
			fclose(room_ptr);
			return;
		}

	rewind(room_ptr);        // 重置文件指针，便于后来写入

	// 用户信息
	user_ptr = fopen(USERFILE, "rb+");
	if (NULL == user_ptr)
	{
		errinfo(errno);
		fclose(user_ptr);
		return;
	}

	while (1 == fread(&temp, sizeof(UserAccount), 1, user_ptr))     // 寻找该用户账户并读取信息
		if ((0 == strcmp(input->username, temp.user_account.username)) &&
			(0 == strcmp(input->passward, temp.user_account.passward)))
		{
			fseek(user_ptr, -(long int)sizeof(UserAccount), SEEK_CUR);  // 文件指针后退一个，便于后来重新写入
			break;
		}

	while (1)
	{
		printf("\nNO   Room                Movie               Price     Row  Column    Date\n");
		for (i = 0; i < TICKETS; i++)
			if (1 == temp.tickets[i].flag)
			{
				printf("%-5d%-20s%-20s%-10d%-5d%-10d%d/%d/%d\n", i, temp.tickets[i].film.room_name, 
					temp.tickets[i].film.film_name, temp.tickets[i].film.price, 
					temp.tickets[i].row, temp.tickets[i].col, temp.tickets[i].film.date.year, 
					temp.tickets[i].film.date.mouth, temp.tickets[i].film.date.day);				
			}
		putchar('\n');

		printf("Enter NO you want to return.(enter '-1' to quit)\n");
		printf("> ");
		i_get(&num);
		
		if (num < -1 || num >= TICKETS)
		{
			invalid();
			continue;
		}
		if (-1 == num)
		{
			break;
		}

		// 判断NO是否有效
		if (1 != temp.tickets[num].flag)
		{
			invalid();
			continue;
		}

		// 顾客
		row = temp.tickets[num].row;
		col = temp.tickets[num].col;

		temp.tickets[num].flag = 0;
		temp.tickets[num].seat.seats[row][col] = 0;
		if (1 != fwrite(&temp, sizeof(UserAccount), 1, user_ptr))
		{
			errinfo(errno);
			printf("退票失败\n");
			continue;
		}
		fseek(user_ptr, -(long int)sizeof(UserAccount), SEEK_CUR);  // 文件指针后退一个，便于后来重新写入

		// 影厅
		for (i = 0; i < 5; i++)
			if (0 == strcmp(cinema[i].room_name, temp.tickets[num].film.room_name))
			{
				cinema[i].seat.seats[row][col] = 0;
				cinema[i].sales -= 1;
				cinema[i].remainings += 1;
				break;
			}

		for (i = 0; i < 5; i++)
		{
			if (1 != fwrite(&cinema[i], sizeof(Room), 1, room_ptr))
			{
				errinfo(errno);
				printf("购买失败\n");

				// 因退票失败，对用户退票进行取消
				temp.tickets[num].flag = 1;
				temp.tickets[num].seat.seats[row][col] = 1;
				fseek(user_ptr, -1, SEEK_CUR);
				fwrite(&temp, sizeof(UserAccount), 1, user_ptr);
				fseek(user_ptr, -(long int)sizeof(UserAccount), SEEK_CUR);  // 文件指针后退一个，便于后来重新写入

				continue;
			}
		}
		rewind(room_ptr);        // 重置文件指针，便于后来写入

		printf("退票成功\n");
	}

	fclose(user_ptr);
	fclose(room_ptr);
}

// ---------------------------------------------------------------------------

// 历史记录
void user_history(void)
{
	// 待实现
}

// ---------------------------------------------------------------------------
