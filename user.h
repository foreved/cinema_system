#ifndef USER_H
#define USER_H

#include "cinema.h"

typedef struct UserAccount
{
	Account user_account;
	char tickets[TICKETS][ROOMNM];
} UserAccount;

#endif