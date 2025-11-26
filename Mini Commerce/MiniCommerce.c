#include "libprogram.c"

int IsUnderMaintenance = false;

int main(void)
{
	user = realloc(user, 1 * sizeof(user));
	user[0].name = malloc(4 * sizeof(char));
	char Test[5] = "test\0";
	strcpy(user[0].name, Test);
	user[0].password = malloc(8 * sizeof(char));
	char code[9] = "12344568\0";
	strcpy(user[0].password, code);
	user[0].id = 10;

	MiniCommerce(10);
}
/*
	if(IsUnderMaintenance == true) {
		printf("Service is currently unavailable\n");
		return 0;
	}

	bool IsProgramRunning = true;
	char UserInput[64];
	int Selection;

	while (IsProgramRunning == true) {
		printf("# Home #\n");
		printf("[1] Sign In\n");
		printf("[2] Sign up\n");
		printf("[3] Exit\n");
		printf("User: ");

		fgets(UserInput, sizeof(UserInput), stdin);
		UserInput[strcspn(UserInput, "\n")] = '\0';
		Selection = atoi(UserInput);

		switch (Selection) {

		case 1:
			if(SignIn() == SUCCESS) {
				MiniCommerce(ClientSession);
			}
			break;

		case 2:
			SignUp();
			break;

		case 3:
			printf("\nGoodbye user\n");
			IsProgramRunning = false;
			break;

		default:
			printf("\n\"%s\" not found\n\n", UserInput);
		}

		fflush(stdin);
	}

	return 0;
}*/