#include "cinema.h"
#include "admin.h"
#include "user.h"

int main()
{
	Account input;
	int i;
	char ch;

	printf("Inilization...\n\n");              // 初始化程序，判断程序能否正常运行
	if (0 == initialize_cinema())
		exit(1);

	while (1)
	{
		menu();                                // 打印主菜单
		printf("> ");
		if (NULL == i_get(&i))                 // 获取用户输入，若失败，结束程序
			exit(1);

		switch (i)
		{
		case 0:                                     // 0 -- 退出程序
			printf("\nBye!\n");
			break;
		case 1:                                     // 1 -- 管理员登入
			get_account(&input);                    // 获取登入信息
			switch (admin_login(&input))            // 登入管理员账户
			{
			case -1:
				printf("用户不存在\n");
				break;
			case 0:
				printf("密码不正确\n");
				break;
			case 1:
				printf("登入成功\n");
				admin(&input);                       // 进入管理员操作界面 
				break;
			}
			break;
		case 2:                                      // 2 -- 普通用户登入
			printf("Do you have an account?(y/n) > ");
			if (NULL == ch_get(&ch))                    // 获取失败，结束程序
				exit(1);

			if ('y' == ch)                           // 'y' -- 有账户
			{
				get_account(&input);                 // 获取账户信息
				switch (user_login(&input))          // 登入用户账户
				{
				case -1:
					printf("用户不存在\n");
					break;
				case 0:
					printf("密码不正确\n");
					break;
				case 1:
					printf("登入成功\n");
					user(&input);                    // 进入用户操作界面
					break;
				}
			}
			else if ('n' == ch)                      // 'n' -- 无账户
			{
				printf("Let's create an account.\n");
				get_account(&input);                 // 获取账户信息
				switch (user_register(&input))       // 注册账户
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
				invalid();
			break;
		default:                                      // 对于其它输入的处理
			invalid();
			break;
		}

		if (0 == i)          // 结束程序
			break;
	}

	return 0;
}