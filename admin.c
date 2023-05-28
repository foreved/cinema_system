#include "admin.h"
#include "cinema.h"

// ����Ա�˺ź�����
Account admin_account = {
	"admin",
	"123456"
};

// ����Ա����
// -1 -- �û�������0 -- �������1 -- �˺���ȷ
int admin_login(Account* input)
{
	if (0 != strcmp(input->username, admin_account.username))
		return -1;
	else
		if (0 != strcmp(input->passward, admin_account.passward))
			return 0;

	return 1;
}
// ����Ա����
void admin(Account* input)
{
	int num;

	admin_menu();
	do
	{
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
			//admin_sale();
			break;
		case 3:
			//admin_box();
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	} while (num);
}
// ����Ա�˵�
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
// ��Ƭ
void admin_arrange(void)
{
	FILE* room_ptr;
	Room cinema[5];
	int i;

	room_ptr = fopen(ROOMFILE, "r");
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
	printf("Room                 Movie\n");
	for (i = 0; i < 5; i++)
		printf("%-20s %s\n", cinema[i].room_name, cinema[i].film_name);

}