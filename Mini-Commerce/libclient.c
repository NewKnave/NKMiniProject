// The contents
void Hash(const char *input, char *output, int hash_lenght); // JDB2
int SignIn(void);
int SignUpProcess(void);
void SignUp(void);

void Hash(const char *input, char *output, int hash_lenght) {
	unsigned long hash = 5381;
	int c;

	while ((c = *input++)) {
		hash = ((hash << 5) + hash) + c;
	}

	snprintf(output, hash_lenght, "%lx", hash);
	return;
}

int SignIn(void) {
	FILE *file_client = fopen("data_client.dat", "rb");
	if (file_client == NULL) {
		err("File not found");
		return FAILED;
	}

	CLIENT client[1];
	char FETCH_NAME[MAX_NAME_LENGHT];
	char FETCH_PASSWORD[MAX_HASH_LENGHT];
	char FETCH_HASH[MAX_HASH_LENGHT];

	char CACHE_PASSWORD = '\0';
	int CACHE_I = 0;

	for(int ERROR_COUNTER = 0; ERROR_COUNTER < 3; ERROR_COUNTER++) {
		printf("\nName: ");
		fgets(FETCH_NAME, sizeof(FETCH_NAME), stdin);
		FETCH_NAME[strcspn(FETCH_NAME, "\n")] = '\0';

		printf("Password: ");
		while(CACHE_PASSWORD = gerch() != ENTER) {
			if(CACHE_PASSWORD == BACKSPACE) {
				if(CACHE_I > 0) {
					CACHE_I--
					printf("\b\0\b");
				}
			}
			else {
				TEMP_PASSWORD[CACHE_I] = CACHE_PASSWORD;
				CACHE_I++;
				printf("*");
			}
		}
		FETCH_PASSWORD[CACHE_I] = '\0';
		Hash(FETCH_PASSWORD, FETCH_HASH, CLIENT_MAX_HASH_LENGHT);

		while(fread(&client, sizeof(CLIENT), 1, file_client) == 1) {
			if(strcmp(FETCH_NAME, client.name) == 0 && strcmp(FETCH_HASH, client.hash) == 0) {
				printf("\nSign in successfully!\n");
				printf("Hello, %s\n\n", client.name);

				// Clean the inputted name and password
				for(int i = 0; i < MAX_NAME_LENGHT; i++) {
					FETCH_NAME[i] = '\0';
				}
				for(int i = 0; i < MAX_HASH_LENGHT; i++) {
					FETCH_PASSWORD[i] = '\0';
					FETCH_HASH[i] = '\0';
				}

				// To use the fetched id
				MiniCommerce(client.id);
				fclose(file_client);
				return SUCCESS;
			}
		}

		if(ERROR_COUNTER < 2) {
			printf("\nInvalid name and/or password, please try again\n");
			CACHE_I = 0;
			CACHE_PASSWORD[0] = '\0';
		}
	}

	err("Too many invalid inputs, exiting");
	fclose(file_client);
	for(int i = 0; i < MAX_NAME_LENGHT; i++) {
		FETCH_NAME[i] = '\0';
	}
	for(int i = 0; i < MAX_HASH_LENGHT; i++) {
		FETCH_PASSWORD[i] = '\0';
		FETCH_HASH[i] = '\0';
	}
	return FAILED;
}

int SignUpProcess(void) {
	FILE *file_client = fopen("data_client.dat", "rb");
	CLIENT client[1];

	// - To initialize a NULL client
	// - It avoids the program calling a non-existing file
	// - When the user is inputting their name
	// the program will open the file to
	// compare the name and check whether is it already taken or not
	// - Ignores all of this if the data exists
	// - One time use, so...
	if(file_client == NULL) {
		file_client = fopen("data_client.dat", "ab");
		if(file_client == NULL) {
			err("Unable to initialize file");
			return FAILED;
		}

		CLIENT InitClient[1];

		char InitName[2];
		char InitHash[2];

		InitName = "\0\0";
		InitHash = "\0\0";

		strcpy(InitClient[0].name, InitName);
		strcpy(InitClient[0].hash, InitHash);
		InitClient.id = 0;

		fwrite(InitClient, sizeof(CLIENT), 1, file_client);
		fclose(file_client);

		file_client = fopen("data_client.dat", "rb");
	}

	// The main process of signing up
	char TEMP_NAME[MAX_NAME_LENGHT] = '\0';
	int TEMP_NAME_LENGHT = 0;
	int NameErrorCounter = 0;

	bool IsValidatingName = true;
	bool IsNameTaken = true;

	printf("\nThis program is a concept,\n");
	printf("so please do not input any password\n");
	printf("that you use to avoid potential leak,\n");
	printf("and DO NOT use your real name, please\n");

	printf("\nPlease input a name\n");
	printf("Minimum name lenght is 4 characters\n");
	printf("Maximum name lenght is %i characters\n", (CLIENT_MAX_NAME_LENGHT - 1));
	while(IsValidatingName == true) {
		printf("Name: ");
		fgets(TEMP_NAME, sizeof(TEMP_NAME), stdin);
		TEMP_NAME[strcspn(TEMP_NAME, "\n")] = '\0';
		TEMP_NAME_LENGHT = strlen(TEMP_NAME);

		if(TEMP_NAME_LENGHT >= 4 && TEMP_NAME_LENGHT <= CLIENT_MAX_NAME_LENGHT) {
			// Check if the name is already taken
			while(fread(&client, sizeof(CLIENT), 1, file_client) == 1) {
				if(strcmp(TEMP_NAME, client.name) == 0) {
					IsNameTaken = true;
					err("Name is already in use");
					break;
				}
			}
			if(IsNameTaken == false) {
				IsValidatingName = false;
			}
		}
		else if(NameErrorCounter == 2) {
			err("Too many invalid inputs");
			return FAILED;
		}
		else {
			err("Invalid name");
			NameErrorCounter++;
		}

		TEMP_NAME[0] = '\0';
		TEMP_NAME_LENGHT = 0;
	}
	// - After getting the name
	// - The memory of TEMP_NAME_LENGHT and NameErrorCounter
	// will no longer be allocated
	// - Do keep in mind that
	// TEMP_NAME will still have some memory allocated
	// - And FILE *file_client = fopen("data_client.dat", "rb"); is used

	char CACHE_PASSWORD = '\0';
	int CACHE_I = 0;

	char TEMP_PASSWORD[MAX_NAME_LENGHT] = '\0';
	int TEMP_PASSWORD_LENGHT = 0;
	int PasswordErrorCounter = 0;

	char TEMP_HASH[MAX_HASH_LENGHT] = '\0';

	bool IsValidatingPassword = true;
	bool IsValidatingConfirmPassword = true;

	printf("\nPlease input a password\n");
	printf("Minimum password lenght is 8 characters\n");
	printf("Maximum password lenght is %i characters\n", CLIENT_MAX_HASH_LENGHT);
	while(IsValidatingPassword == true) {
		printf("Password: ");
		while(CACHE_PASSWORD = getch() != ENTER) {
			if(CACHE_PASSWORD == BACKSPACE) {
				if(CACHE_I > 0) {
					CACHE_I--
					printf("\b\0\b");
				}
			}
			else {
				TEMP_PASSWORD[CACHE_I] = CACHE_PASSWORD;
				CACHE_I++;
				printf("*");
			}
		}
		TEMP_PASSWORD[CACHE_I] = '\0';
		TEMP_PASSWORD_LENGHT = strlen(TEMP_PASSWORD);

		if(TEMP_PASSWORD_LENGHT >= 8 && TEMP_PASSWORD_LENGHT <= CLIENT_MAX_HASH_LENGHT) {
			char TEMP_PASSWORD_COMFIRMATION[MAX_NAME_LENGHT] = '\0';
			int ConfirmPasswordErrorCounter = 0;
			CACHE_I = 0;

			while(IsValidatingConfirmPassword) {
				printf("Confirm password: ");
				while(CACHE_PASSWORD = getch() != ENTER) {
					if(CACHE_PASSWORD == BACKSPACE) {
						if(CACHE_I > 0) {
							CACHE_I--;
							printf("\b\0\b");
						}
					}
					else {
						TEMP_PASSWORD[CACHE_I] = CACHE_PASSWORD;
						CACHE_I++;
						printf("*");
					}
				}
				TEMP_PASSWORD_COMFIRMATION[CACHE_I] = '\0';

				if(strcmp(TEMP_PASSWORD_COMFIRMATION, TEMP_PASSWORD) == 0) {
					for(int i = 0; i < TEMP_PASSWORD_LENGHT; i++) {
						TEMP_PASSWORD_CONFIRMATION[i] = '\0'''
					}
					IsValidatingPassword = false;
					IsValidatingConfirmPassword = false;
				}
				else if(ConfirmPasswordErrorCounter == 2) {
					err("Too many invalid inputs");
					return FAILED;
				}
				else {
					printf("Password does not match\n\n");
					CACHE_PASSWORD[0] = '\0';
					ConfirmPasswordErrorCounter++;
				}
			}		
		}
		else if(PasswordErrorCounter == 2) {
			err("Too many invalid inputs");
			return FAILED;
		}
		else {
			err("Invalid password");
			PasswordErrorCounter++;
		}
	}

	// Note:
	// - file_client = fopen("data_client.dat", "rb");
	// - CLIENT client[1];
	// - Are declared

	// Saving user data
	int TEMP_ID = 100;
	int CACHE_ID = 0;

	// This is to fetch the lastest id
	if(file_client != NULL) {
		// Seek latest id from
		if(fseek(file_client, -sizeof(CLIENT), SEEK_END) == 0) {
			// Fetch latest id and store it to the struct of "client"
			if(fread(&client, sizeof(CLIENT), 1, file_client) == 1) {
				// If there is no id, the id will be "100"
				if(client[0].id != '\0') {
					CACHE_ID = atoi(client[0].id);
					TEMP_ID = (CACHE_ID + 1);
					fclose(file_client);
				}
			}
		}
	}
	// - If there are no data
	// close fopen("data_client.dat", "rb")
	// then place the id of "100" at the first client
	fclose(file_client);
	file_client = fopen("data_client.dat", "ab");

	// Store name in the struct
	strcpy(client.name, TEMP_NAME);
	for(int i = 0; i < MAX_NAME_LENGHT; i++) {
		TEMP_NAME[i] = '\0';
	}

	// Store hash in the struct
	Hash(TEMP_PASSWORD, TEMP_HASH, MAX_HASH_LENGHT);
	for(int i = 0; i < MAX_HASH_LENGHT; i++) {
		TEMP_PASSWORD[i] = '\0';
	}
	strcpy(client.hash, TEMP_HASH);
	for(int i = 0; i < MAX_HASH_LENGHT; i++) {
		TEMP_HASH[i] = '\0';
	}

	// Store id in the struct
	client.id = TEMP_ID;
	TEMP_ID = 0;

	// Store the struct in the file
	fwrite(&client, sizeof(CLIENT), 1, file_client);
	fclose(file_client);
	return SUCCESS;
}

void SignUp(void) {
	int Validation = SignUpProcess();

	if(Validation == SUCCESS) {
		printf("\nSign up successfully\n\n");
		return;
	}
	else if(Validation == FAILED) {
		printf("Sign up failed\n\n");
		return;
	}
	else {
		err("SignUp");
		return;
	}
}
