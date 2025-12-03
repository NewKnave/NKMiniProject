// Variable set 2 on "libglobalvar.c"
// const int CLIENT_MAX_NAME_LENGHT = (64 + 1);
// const int CLIENT_MAX_HASH_LENGHT = (64 + 1);

// JDB2 hashing algorithn
void SimpleHash(const char *input, char *output, int hash_lenght) {

	unsigned long hash = 5381;
	int c;

	while((c = *input++)) {
		hash = ((hash << 5) + hash) + c; // hash * 33 + c
	}

	snprintf(output, hash_lenght, "%lx", hash);

	return;
}

int SignIn(void) {

	FILE *file_client = NULL;

	file_client = fopen("data_client.dat", "rb");

	if(file_client == NULL) {
		printf("\nClient database not found\n\n");
		return FAILED;
	}

	typedef struct {
		char name[CLIENT_MAX_NAME_LENGHT];
		char hash[CLIENT_MAX_HASH_LENGHT];
		int id;
	} ClientData;

	ClientData client[1];

	char FETCH_NAME[CLIENT_MAX_NAME_LENGHT];
	char FETCH_PASSWORD[CLIENT_MAX_HASH_LENGHT];
	char FETCH_HASH[CLIENT_MAX_HASH_LENGHT];

	for(int ERROR_COUNTER = 0; ERROR_COUNTER < 3; ERROR_COUNTER++) {
		printf("\nName: ");
		fgets(FETCH_NAME, sizeof(FETCH_NAME), stdin);
		FETCH_NAME[strcspn(FETCH_NAME, "\n")] = '\0';

		printf("Password: ");
		fgets(FETCH_PASSWORD, sizeof(FETCH_PASSWORD), stdin);
		FETCH_PASSWORD[strcspn(FETCH_PASSWORD, "\n")] = '\0';

		SimpleHash(FETCH_PASSWORD, FETCH_HASH, CLIENT_MAX_HASH_LENGHT);

		while(fread(&client[0], sizeof(ClientData), 1, file_client) == 1) {

			if(strcmp(FETCH_NAME, client[0].name) == 0 && strcmp(FETCH_HASH, client[0].hash) == 0) {

				printf("\nSign in successfully!\n");
				printf("Hello, %s\n\n", client[0].name;

				// To use the fetched id
				MiniCommerce(client[0].id);

				fclose(file_client);

				return SUCCESS;
			}
		}

		if(ERROR_COUNTER < 2) {
			printf("\nInvalid name and/or password, please try again\n");
		}
	}

	printf("\nToo many errors, exiting\n\n");

	fclose(file_client);

	return FAILED;
}

int SignUpProcess(void) {

	typedef struct {
		char name[CLIENT_MAX_NAME_LENGHT];
		char hash[CLIENT_MAX_HASH_LENGHT];
		int id;
	} ClientData;

	ClientData client[1];

	FILE *file_client = NULL;

	file_client = fopen("data_client.dat", "rb");

	// To initialize a Null client
	// Its to avoid the program calling a non-existing file
	// A solution to name comparison
	if(file_client == NULL) {
		file_client = fopen("data_client.dat", "ab");

		if(file_client == NULL) {
			printf("\nSystem Error\n\n");
			return FAILED;
		}

		ClientData *NullClient = NULL;

		NullClient = malloc(1 * sizeof(ClientData));

		char *NullName = NULL;
		char *NullHash = NULL;

		NullName = malloc(3 * sizeof(char));
		NullHash = malloc(3 * sizeof(char));

		NullName = "\0\0\0";
		NullHash = "\0\0\0";

		strcpy(NullClient[0].name, NullName);
		strcpy(NullClient[0].hash, NullHash);
		NullClient[0].id = 0;

		fwrite(&NullClient[0], sizeof(ClientData), 1, file_client);
		fclose(file_client);

		free(NullName);
		free(NullHash);
		free(NullClient);

		file_client = fopen("data_client.dat", "rb");
	}

	// The main process of signing up
	// Initialize variables
	char	TEMP_NAME[CLIENT_MAX_NAME_LENGHT];
	int	   TEMP_NAME_LENGHT = 0;

	char    TEMP_PASSWORD[CLIENT_MAX_HASH_LENGHT];
	char    TEMP_PASSWORD_COMFIRMATION[CLIENT_MAX_HASH_LENGHT];
	int       TEMP_PASSWORD_LENGHT = 0;

	char    TEMP_HASH[CLIENT_MAX_HASH_LENGHT];

	int       ErrorCounter = 0;

	bool IsValidatingName = true;
	bool IsValidatingPassword = true;

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
			IsValidatingName = false;
		}

		else if(ErrorCounter == 2) {
			printf("Too many errors, exiting\n\n");
			return FAILED;
		}

		else {
			printf("Invalid name\n\n");
			ErrorCounter++;
		}

		fflush(stdin);
	}

	// To reset the error counter
	ErrorCounter = 0;

	printf("\nPlease input a password\n");
	printf("Minimum password lenght is 8 characters\n");
	printf("Maximum password lenght is %i characters\n", CLIENT_MAX_HASH_LENGHT);
	while(IsValidatingPassword == true) {
		printf("Password: ");
		fgets(TEMP_PASSWORD, sizeof(TEMP_PASSWORD), stdin);
		TEMP_PASSWORD[strcspn(TEMP_PASSWORD, "\n")] = '\0';
		TEMP_PASSWORD_LENGHT = strlen(TEMP_PASSWORD);

		if(TEMP_PASSWORD_LENGHT >= 8 && TEMP_PASSWORD_LENGHT <= CLIENT_MAX_HASH_LENGHT) {
			IsValidatingPassword = false;
		}

		else if(ErrorCounter == 2) {
			printf("Too many errors, exiting\n\n");
			return FAILED;
		}

		else {
			printf("Invalid password\n\n");
			ErrorCounter++;
		}
	}

	// Note:
	// file_client = fopen("data_client.dat", "rb");
	// is used

	// Saving user data
	int TEMP_ID = 100;

	// This is to fetch the lastest id 
	if(file_client != NULL) {
		// Seek latest id from
		if(fseek(file_client, -sizeof(ClientData), SEEK_END) == 0) {

			// Fetch latest id and store it to the struct of "client"
			if(fread(&client, sizeof(ClientData), 1, file_client) == 1) {

				// If there is no id, the id will be "100"
				if(client[0].id != '\0') {
					TEMP_ID = client[0].id + 1;
					fclose(file_client);
				}
			}
		}
	}

	// If there are no data
	// Close fopen("data_client.dat", "rb")
	// Then place the id of "100" at the first client
	else {
		fclose(file_client);
	}

	file_client = fopen("data_client.dat", "ab");

	// Store name in the struct
	strcpy(client[0].name, TEMP_NAME);

	// Store hash in the struct
	SimpleHash(TEMP_PASSWORD, TEMP_HASH, CLIENT_MAX_HASH_LENGHT);
	strcpy(client[0].hash, TEMP_HASH);

	// Store id in the struct
	client[0].id = TEMP_ID;

	// Store the struct in the file
	fwrite(&client[0], sizeof(ClientData), 1, file_client);

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
		printf("\nSystem Error\n\n");
		return;
	}
}