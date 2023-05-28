#include "cinema.h"

int main()
{
	Account input;
	int num;
	
	printf("Inilization...\n");
	if (0 == initialize_cinema())
		exit(1);

	//menu(&input);

	menu();
	do
	{
		switch (num = choice())
		{
		case 0:
			printf("Bye!\n");
			break;
		case 1:
			get_account(&input);
			switch (admin_login(&input))
			{
			case -1:
				printf("用户不存在\n");
				break;
			case 0:
				printf("密码不正确\n");
				break;
			case 1:
				printf("登入成功\n");
				admin(&input);
				menu();
				break;
			}
			break;
		case 2:
			printf("u\n");
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	} while (num);

	return 0;
}