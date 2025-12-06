#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SUCCESS 0
#define FAILED -1

// ASCII
#define ENTER 13
#define BACKSPACE 8

const int MIN_NAME_LENGHT = (8 + 1);
const int MAX_NAME_LENGHT = (32 + 1);

const int MIN_HASH_LENGHT = (8 + 1);
const int MAX_HASH_LENGHT = (32 + 1);

const int MAX_ID_LENGHT = (8 + 1);

const int USER_INPUT_LIMIT = (8 + 1);

void err(const char *str) {
	fprintf(stderr, "\nError - %s\n\n", str);
	return;
}

typedef struct {
	int id;
	char name[MAX_NAME_LENGHT];
	float price;
	int quantity;
} COMMERCE;

typedef struct CART {
	int id;
	char name[MAX_NAME_LENGHT];
	float price;
	int quantity;
} CART;

typedef struct CART_HEAD {
	int client_id;
	CART *node;
} CART_HEAD;

typedef struct {
	char name[MAX_NAME_LENGHT];
	char hash[MAX_HASH_LENGHT];
	char id[MAX_ID_LENGHT];
	CART_HEAD *node;
} CLIENT;

#include "libdata.c"
#include "libclient.c"

int IsUnderMaintenance = false;

int main(void) {

	if(IsUnderMaintenance == true) {
		printf("Service is currently unavailable\n");
		return 0;
	}

	bool IsProgramRunning = true;
	char UserInput[USER_INPUT_LIMIT] = "\0";
	int Selection = 0;

	printf("%s\n\n", __DATE__);
	while (IsProgramRunning == true) {
		printf("# Home #\n\n");
		printf("Please select one of the following:\n");
		printf("[1] Sign In\n");
		printf("[2] Sign up\n");
		printf("[3] Exit\n");
		printf("User: ");

		fgets(UserInput, sizeof(UserInput), stdin);
		UserInput[strcspn(UserInput, "\n")] = '\0';
		Selection = atoi(UserInput);

		switch (Selection) {

		case 1:
			SignIn();
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

		int i = 0;
		int size = sizeof(UserInput);
		for(i = 0; i < size; i++) {
			UserInput[i] = '\0';
		}
		Selection = 0;
	}

	return 0;
}
