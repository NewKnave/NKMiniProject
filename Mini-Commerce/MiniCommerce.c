#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libclient.c"
#include "libdata.c"

int IsUnderMaintenance = false;

int main(void) {

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
				MiniCommerce();
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
}
