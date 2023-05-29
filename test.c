#include "cinema.h"

int main()
{
	Account input;
	int num;
	char ch;
	
	printf("Inilization...\n");
	if (0 == initialize_cinema())
		exit(1);

	//menu(&input);

	do
	{
		menu();

		printf("> ");
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
				break;
			}
			break;
		case 2:
			printf("Do you have an account?(y/n) > ");
			ch = ch_choice();
			if ('y' == ch)
			{
				get_account(&input);
				switch (user_login(&input))
				{
				case -1:
					printf("用户不存在\n");
					break;
				case 0:
					printf("密码不正确\n");
					break;
				case 1:
					printf("登入成功\n");
					user(&input);
					break;
				}
			}
			else if ('n' == ch)
			{
				printf("Let's create an account.\n");
				get_account(&input);
				switch (user_register(&input))
				{
				case 1:
					printf("注册成功！\n");
					break;
				case 0:
					printf("用户名已存在！\n");
					break;
				case -1:
					printf("注册失败！\n");
					break;
				}
			}
			else
				printf("Invalid command!\n");
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	} while (num);

	return 0;
}