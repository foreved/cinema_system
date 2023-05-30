#include "user.h"
#include "cinema.h"

// ---------------------------------------------------------------------------
// ��������
// ---------------------------------------------------------------------------

// �û�����
// Ч������֤�˻�
// ���أ�-1 -- �˻������ڣ�0 -- �������1 -- ����ɹ�
int user_login(Account* input)
{
	UserAccount temp;
	FILE* user_ptr;

	user_ptr = fopen(USERFILE, "rb");
	if (NULL == user_ptr)                      // �û��ļ���ʧ�ܣ��˳�����
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

	if (!feof(user_ptr))                // ָ��δ��EOF�����������⣬�˳�����
	{
		errinfo(errno);
		fclose(user_ptr);
		exit(1);
	}

	fclose(user_ptr);
	return -1;
}

// ---------------------------------------------------------------------------

// �û�����
void user(Account* input)
{
	int i;

	while (1)
	{
		user_menu();
		printf("> ");
		if (NULL == i_get(&i))                 // ��ȡ�û����룬��ʧ�ܣ���������
			exit(1);

		switch (i)
		{
		case 0:                                // �˳��û��˻�
			printf("\nBye!\n");
			break;
		case 1:
			user_movie();                      // ���ӰƬ��Ϣ
			break;
		case 2:
			user_buy(input);                   // �����ӰƱ
			break;
		case 3:
			user_return(input);                // ��Ʊ
			break;
		case 4:
			user_history(input);               // ��ʷ��¼
		default:
			invalid();
			break;
		}

		if (0 == i)          // ��������
			break;
	} 
}

// ---------------------------------------------------------------------------

// �û�ע��
// Ч����Ϊ�����ڵ��û���ע���˻�
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

	while (1 == fread(&temp, sizeof(UserAccount), 1, user_ptr))       // �û����Ƿ����
		if (0 == strcmp(input->username, temp.user_account.username))
			return 0;                               // �û����Ѵ���

	if (!feof(user_ptr))    // ָ��δ���ļ�ĩβ
	{
		errinfo(errno);
		return -1;
	}

	new_account.user_account = *input;   // д���û���Ϣ
	if (1 == fwrite(&new_account, sizeof(UserAccount), 1, user_ptr))
	{
		fclose(user_ptr);
		return 1;                         // ע��ɹ�
	}
	else
	{
		errinfo(errno);
		return -1;                        // ע��ʧ��
	}
}

// ---------------------------------------------------------------------------

// �û��˵�
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

// �û����ӰƬ��Ϣ
void user_movie(void)
{
	movie_style();                    // ��ӡӰƬ��Ϣ
}

// ---------------------------------------------------------------------------

// �û���Ʊ
void user_buy(Account* input)
{
	UserAccount temp;
	Room cinema[5];
	Record record;
	FILE* user_ptr, * room_ptr;
	int row, col;
	int num, i, j;
	char ch;

	// ��ȡӰ����Ϣ
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

	rewind(room_ptr);        // �����ļ�ָ�룬���ں���д��

	// �û���Ϣ
	user_ptr = fopen(USERFILE, "rb+");
	if (NULL == user_ptr)
	{
		errinfo(errno);
		fclose(user_ptr);
		return;
	}

	while (1 == fread(&temp, sizeof(UserAccount), 1, user_ptr))     // Ѱ�Ҹ��û��˻�����ȡ��Ϣ
		if ((0 == strcmp(input->username, temp.user_account.username)) &&
			(0 == strcmp(input->passward, temp.user_account.passward)))
		{
			fseek(user_ptr, -(long int)sizeof(UserAccount), SEEK_CUR);  // �ļ�ָ�����һ�������ں�������д��
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
					printf("\u25A1 ");   // ���ķ��� -- δ��
				else
					printf("\u25CF ");   // ʵ��Բ -- ����

			putchar('\n');
		}
		printf("\n\u25A1��δ��	\u25CF������\n\n");

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
			// ��
			printf("Please enter the coordinate of the seat.\n");
			printf("Enter the row.(0-%d) > ", ROW - 1);
			i_get(&row);
			while (row < 0 || row > ROW - 1)
			{
				invalid();
				printf("Enter the row.(0-%d) > ", ROW - 1);
				i_get(&row);
			}

			// ��
			printf("Enter the column.(0-%d) > ", COL - 1);
			i_get(&col);
			while (col < 0 || col > COL - 1)
			{
				invalid();
				printf("Enter the column.(0-%d) > ", COL - 1);
				i_get(&col);
			}

			if (cinema[num].seat.seats[row][col])
				printf("��λ��Ʊ���۳���������ѡ��\n");

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

		// ��ɹ�Ʊ
		for (i = 0; i < TICKETS; i++)
			if (0 == temp.tickets[i].flag)
				break;

		if (i >= TICKETS)
		{
			printf("�ѴﹺƱ����\n");
			continue;
		}

		// �˿�
		record.flag = 1;
		record.film = cinema[num].film;
		record.seat.seats[row][col] = 1;
		record.row = row;
		record.col = col;
		// ��Ʊ��¼
		temp.tickets[i] = record;
		// ��ʷ��¼
		// ��ʵ��

		if (1 != fwrite(&temp, sizeof(UserAccount), 1, user_ptr))
		{
			errinfo(errno);
			printf("����ʧ��\n");
			continue;
		}
		fseek(user_ptr, -(long int)sizeof(UserAccount), SEEK_CUR);  // �ļ�ָ�����һ�������ں�������д��

		// Ӱ��
		cinema[num].seat.seats[row][col] = 1;
		cinema[num].sales += 1;
		cinema[num].remainings -= 1;
		for (i = 0; i < 5; i++)
		{
			if (1 != fwrite(&cinema[i], sizeof(Room), 1, room_ptr))
			{
				errinfo(errno);
				printf("����ʧ��\n");

				// ����ʧ�ܣ����û���Ʊ����ȡ��
				temp.tickets[i].flag = 0;
				fseek(user_ptr, -1, SEEK_CUR);
				fwrite(&temp, sizeof(UserAccount), 1, user_ptr);
				fseek(user_ptr, -(long int)sizeof(UserAccount), SEEK_CUR);  // �ļ�ָ�����һ�������ں�������д��
				continue;
			}
		}
		rewind(room_ptr);        // �����ļ�ָ�룬���ں���д��

		printf("����ɹ�\n");
	}

	fclose(user_ptr);
	fclose(room_ptr);
	printf("лл�ݹˣ�\n");
}

// ---------------------------------------------------------------------------

// �û���Ʊ
void user_return(Account* input)
{
	UserAccount temp;
	Room cinema[5];
	FILE* user_ptr, * room_ptr;
	int row, col;
	int num, i, j, k;
	char ch;

	// ��ȡӰ����Ϣ
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

	rewind(room_ptr);        // �����ļ�ָ�룬���ں���д��

	// �û���Ϣ
	user_ptr = fopen(USERFILE, "rb+");
	if (NULL == user_ptr)
	{
		errinfo(errno);
		fclose(user_ptr);
		return;
	}

	while (1 == fread(&temp, sizeof(UserAccount), 1, user_ptr))     // Ѱ�Ҹ��û��˻�����ȡ��Ϣ
		if ((0 == strcmp(input->username, temp.user_account.username)) &&
			(0 == strcmp(input->passward, temp.user_account.passward)))
		{
			fseek(user_ptr, -(long int)sizeof(UserAccount), SEEK_CUR);  // �ļ�ָ�����һ�������ں�������д��
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

		// �ж�NO�Ƿ���Ч
		if (1 != temp.tickets[num].flag)
		{
			invalid();
			continue;
		}

		// �˿�
		row = temp.tickets[num].row;
		col = temp.tickets[num].col;

		temp.tickets[num].flag = 0;
		temp.tickets[num].seat.seats[row][col] = 0;
		if (1 != fwrite(&temp, sizeof(UserAccount), 1, user_ptr))
		{
			errinfo(errno);
			printf("��Ʊʧ��\n");
			continue;
		}
		fseek(user_ptr, -(long int)sizeof(UserAccount), SEEK_CUR);  // �ļ�ָ�����һ�������ں�������д��

		// Ӱ��
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
				printf("����ʧ��\n");

				// ����Ʊʧ�ܣ����û���Ʊ����ȡ��
				temp.tickets[num].flag = 1;
				temp.tickets[num].seat.seats[row][col] = 1;
				fseek(user_ptr, -1, SEEK_CUR);
				fwrite(&temp, sizeof(UserAccount), 1, user_ptr);
				fseek(user_ptr, -(long int)sizeof(UserAccount), SEEK_CUR);  // �ļ�ָ�����һ�������ں�������д��

				continue;
			}
		}
		rewind(room_ptr);        // �����ļ�ָ�룬���ں���д��

		printf("��Ʊ�ɹ�\n");
	}

	fclose(user_ptr);
	fclose(room_ptr);
}

// ---------------------------------------------------------------------------

// ��ʷ��¼
void user_history(void)
{
	// ��ʵ��
}

// ---------------------------------------------------------------------------
