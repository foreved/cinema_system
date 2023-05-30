#include "admin.h"
#include "cinema.h"

// ---------------------------------------------------------------------------
// ��������
// --------------------------------------------------------------------------- 
static void box_sort(Room arr[]);          // Ʊ������

// ����Ա�˺ź�����
Account admin_account = {
	"admin",
	"123"
};

// ---------------------------------------------------------------------------
// ��������
// ---------------------------------------------------------------------------

// ����Ա����
// ������input -- �����˻���Ϣ������ָ��
// Ч������֤����Ա�˻��Ƿ���ȷ
// ���أ�-1 -- �û�������0 -- �������1 -- ����ɹ�
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

// ����Ա����
// ������input -- �û��ĵ�����Ϣ
void admin(Account* input)
{
	int i;

	while (1)
	{
		admin_menu();                          // ��ӡ����Ա�˵�
		printf("> ");
		if (NULL == i_get(&i))                 // ��ȡ�û����룬��ʧ�ܣ���������
			exit(1);

		switch (i)
		{
		case 0:
			printf("\nBye!\n");
			break;
		case 1:
			admin_arrange();                    // ����Ա��Ƭ
			break;
		case 2:
			admin_sale();                       // ����Ա�鿴��ӰƱ��
			break;
		case 3:
			admin_box();                        // ����Ա�鿴Ʊ��
			break;
		default:
			invalid();
			break;
		}

		if (0 == i)          // ��������
			break;
	}

}

// ---------------------------------------------------------------------------

// ����Ա�˵�
// Ч������ӡ����Ա�˵�
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

// ����Ա��Ƭ
// Ч����������Ƭ
void admin_arrange(void)
{
	FILE* room_ptr;                          // room_ptr -- room�ļ�ָ��
	Room cinema[5];                          // Ӱ����Ϣ
	Movie film;                              // �������ӰƬ��Ϣ
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

	// �����ļ�ָ��
	rewind(room_ptr);

	// δ�޸�ǰ����Ƭ
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

	// �޸Ľ׶�
	while (1)
	{

		printf("Enter the room number (0-4).\n");
		printf("Enter '-1' to quit.\n");
		printf("> ");
		if (NULL == i_get(&num))                 // ��ȡ�û����룬��ʧ�ܣ���������
			exit(1);

		if (-1 == num)                      // ������Ƭ
		{
			break;
		}

		if (num >= 0 && num <= 4)           // ������Ƭ
		{
			// Ӱ������
			snprintf(film.room_name, ROOMNM, "%s", cinema[num].room_name);
			// ��Ӱ����
			printf("Enter the movie's name.\n");
			printf("> ");
			if (NULL == str_get(film.film_name, FILMNM))
			{
				fclose(room_ptr);
				return;
			}
			// ��Ӱ�۸�
			printf("Enter the movie's price.\n");
			printf("> ");
			if (NULL == i_get(&film.price))
			{
				fclose(room_ptr);
				return;
			}
			// ��Ӱ����
			printf("Enter the movie's date.\n");
			printf("> year: ");                         // ��
			if (NULL == i_get(&film.date.year))
			{
				fclose(room_ptr);
				return;
			}
			printf("> mouth: ");                        // ��
			if (NULL == i_get(&film.date.mouth))
			{
				fclose(room_ptr);
				return;
			}
			printf("> day: ");                          // ��
			if (NULL == i_get(&film.date.day))
			{
				fclose(room_ptr);
				return;
			}

			// �޸�Ӱ����Ϣ
			cinema[num].film = film;

			// д���ļ�
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

// �鿴Ʊ��
void admin_sale(void)
{
	FILE* room_ptr;                           // room_ptr -- room�ļ�ָ��
	Room cinema[5];                           // Ӱ����Ϣ
	int i, num;

	char film_name[FILMNM];
	char room_name[ROOMNM];

	// ��ȡӰ����Ϣ
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

	// Ӱ����Ϣ 
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
		if (NULL == i_get(&num))                 // ��ȡ�û����룬��ʧ�ܣ���������
			exit(1);

		if (-1 == num)                           // ������ѯƱ��
		{
			fclose(room_ptr);
			return;
		}

		// ��ѯƱ��
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

// �鿴Ʊ��
// Ч���������ӰƱ��������������
void admin_box(void)
{
	FILE* room_ptr;
	Room cinema[5];
	int i;

	// ��ȡӰ����Ϣ
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

	// ����ָ��
	rewind(room_ptr);

	// ����Ʊ��
	for (i = 0; i < 5; i++)
		cinema[i].boxes = cinema[i].sales * cinema[i].film.price;

	// д���ļ�
	for (i = 0; i < 5; i++)
		if (1 != fwrite(&cinema[i], sizeof(Room), 1, room_ptr))
		{
			errinfo();
			fclose(room_ptr);
			return;
		}

	// ����Ʊ������
	box_sort(cinema);

	// ��ӡƱ��
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

// Ʊ������
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
