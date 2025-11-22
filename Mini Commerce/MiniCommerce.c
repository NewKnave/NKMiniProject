#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib_client.c"
#include "lib_market.c"

int main(void)
{
	int isRunning = 1;

	char input[8];
	int selected = 0;

	while(isRunning == 1)
	{
		printf("# Mini Commerce #\n");
		printf("[1] Sign in\n");
		printf("[2] Sign up\n");
		printf("[3] Exit\n");
		printf("User: ");
		fgets(input, sizeof(input), stdin);
		input[strcspn(input, "\n")] = 0;
		selected = atoi(input);

		switch(selected)
		{
			case 1:
				if(SignIn() == 1)
				{
					SignInSuccess();
					MiniCommerce();
				}
				else
				{
					SignInFail();
				}
				break;

			case 2:
				if(SignUp() == 1)
				{
					SignUpSuccess();
				}
				else
				{
					SignUpFail();
				}
				break;

			case 3:
				printf("\nExiting\n");
				isRunning = 0;
				break;

			default:
				printf("\n\"%s\" not found\n\n", input);
		}
		fflush(stdin);
	}
} // End of main