#include "cinema.h"
#include "admin.h"
#include "user.h"

int main()
{
	Account input;
	int i;
	char ch;

	printf("Inilization...\n\n");              // ��ʼ�������жϳ����ܷ���������
	if (0 == initialize_cinema())
		exit(1);

	while (1)
	{
		menu();                                // ��ӡ���˵�
		printf("> ");
		if (NULL == i_get(&i))                 // ��ȡ�û����룬��ʧ�ܣ���������
			exit(1);

		switch (i)
		{
		case 0:                                     // 0 -- �˳�����
			printf("\nBye!\n");
			break;
		case 1:                                     // 1 -- ����Ա����
			get_account(&input);                    // ��ȡ������Ϣ
			switch (admin_login(&input))            // �������Ա�˻�
			{
			case -1:
				printf("�û�������\n");
				break;
			case 0:
				printf("���벻��ȷ\n");
				break;
			case 1:
				printf("����ɹ�\n");
				admin(&input);                       // �������Ա�������� 
				break;
			}
			break;
		case 2:                                      // 2 -- ��ͨ�û�����
			printf("Do you have an account?(y/n) > ");
			if (NULL == ch_get(&ch))                    // ��ȡʧ�ܣ���������
				exit(1);

			if ('y' == ch)                           // 'y' -- ���˻�
			{
				get_account(&input);                 // ��ȡ�˻���Ϣ
				switch (user_login(&input))          // �����û��˻�
				{
				case -1:
					printf("�û�������\n");
					break;
				case 0:
					printf("���벻��ȷ\n");
					break;
				case 1:
					printf("����ɹ�\n");
					user(&input);                    // �����û���������
					break;
				}
			}
			else if ('n' == ch)                      // 'n' -- ���˻�
			{
				printf("Let's create an account.\n");
				get_account(&input);                 // ��ȡ�˻���Ϣ
				switch (user_register(&input))       // ע���˻�
				{
				case 1:
					printf("ע��ɹ���\n");
					break;
				case 0:
					printf("�û����Ѵ��ڣ�\n");
					break;
				case -1:
					printf("ע��ʧ�ܣ�\n");
					break;
				}
			}
			else
				invalid();
			break;
		default:                                      // ������������Ĵ���
			invalid();
			break;
		}

		if (0 == i)          // ��������
			break;
	}

	return 0;
}