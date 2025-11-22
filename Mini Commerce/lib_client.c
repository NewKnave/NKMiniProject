#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int idCounter = 0;

struct UserData
{
	char *name;
	char *password;
	int id;
};

struct UserData *ClientData;

int SignIn(void)
{
	fflush(stdin);

	int Size = idCounter;

	if(Size == 0)
	{
		printf("\nNo Data\n");
		return 0;
	}

	char CheckName[32];
	char CheckPassword[32];

	printf("\nName: ");
	fgets(CheckName, sizeof(CheckName), stdin);
	CheckName[strcspn(CheckName, "\n")] = '\0';

	printf("Password: ");
	fgets(CheckPassword, sizeof(CheckPassword), stdin);
	CheckPassword[strcspn(CheckPassword, "\n")] = '\0';

	for(int i = 0; i < Size; i++)
	{
		if(strcmp(CheckName, ClientData[i].name) == 0 && strcmp(CheckPassword, ClientData[i].password) == 0)
		{
			return 1;
		}
	}
	return 0;
} // End of SignIn

void SignInSuccess(void)
{
	printf("\nSigned in successfully!\n\n");
	return;
} // End of SignInSuccess

void SignInFail(void)
{
	printf("\nSign in failed\n\n");
	return;
} // End of SignInFail

int SignUp(void)
{
	fflush(stdin);

	int ValidateNameSession = 1;
	int ValidatePasswordSession = 1;

	char TemporaryName[32];
	char TemporaryPassword[32];
	int NameLenght = 0;
	int PasswordLenght = 0;
	int ErrorCounter = 0;

	printf("\nMinimum name lenght is 4 characters\n");
	printf("Maximum name lenght is 32 characters\n");
	while(ValidateNameSession == 1)
	{
		printf("Name: ");
		fgets(TemporaryName, sizeof(TemporaryName), stdin);
		TemporaryName[strcspn(TemporaryName, "\n")] = '\0';
		NameLenght = strlen(TemporaryName);
		if(NameLenght >= 4 && NameLenght <= 32)
		{
			printf("Name is valid\n");
			ValidateNameSession = 0;
		}
		else if(ErrorCounter == 2)
		{
			printf("Name is invalid\n");
			printf("3 errors, exiting\n\n");
			return 0;
		}
		else
		{
			ErrorCounter++;
			printf("Name is invalid, please try again\n");
		}
	}
	ErrorCounter = 0;

	printf("\nMinimum password lenght is 8 characters\n");
	printf("Maximum password lenght is 32 characters\n");
	while(ValidatePasswordSession == 1)
	{
		printf("Password: ");
		fgets(TemporaryPassword, sizeof(TemporaryPassword), stdin);
		TemporaryPassword[strcspn(TemporaryPassword, "\n")] = '\0';
		PasswordLenght = strlen(TemporaryPassword);
		if(PasswordLenght >= 8 && PasswordLenght <= 32)
		{
			printf("Password is valid\n");
			ValidatePasswordSession = 0;
		}
		else if(ErrorCounter == 2)
		{
			printf("Password is invalid\n");
			printf("3 errors, exiting\n\n");
			return 0;
		}
		else
		{
			ErrorCounter++;
			printf("Password is invalid, please try again\n");
		}
	}

	idCounter++;
	int ArrayLocation = (idCounter - 1);

	printf("\nYour id is %i\n\n", idCounter);

	ClientData = realloc(ClientData, idCounter);

	ClientData[ArrayLocation].name = realloc(ClientData[ArrayLocation].name, NameLenght);
	strcpy(ClientData[ArrayLocation].name, TemporaryName);

	ClientData[ArrayLocation].password = realloc(ClientData[ArrayLocation].password, PasswordLenght);
	strcpy(ClientData[ArrayLocation].password, TemporaryPassword);

	ClientData[ArrayLocation].id = idCounter;

	return 1;
} // End of SignUp

void SignUpSuccess(void)
{
	printf("Signed up successfully!\n\n");
	return;
} // End of SignUpSuccess

void SignUpFail(void)
{
	printf("Sign up failed\n\n");
	return;
} // End of SignUpFail