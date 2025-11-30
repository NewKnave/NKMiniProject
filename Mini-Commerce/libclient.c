#define SUCCESS 0
#define FAILED 1

#define CLIENT_MAX_NAME_LENGHT 64+1
#define CLIENT_MAX_HASH_LENGHT 64
#define CLIENT_MAX_ID_LENGHT 20+1

int SignIn(void);
void SignInProcess(void);

void SignUp(void);
int SignUpProcess(void);

int SignIn(void) {

	return SUCCESS;
}

void SignInProcess(void) {

	FILE *file_client;

	typedef struct {
		char name[CLIENT_MAX_NAME_LENGHT];
		char hash[CLIENT_MAX_HASH_LENGHT];
		char id[CLIENT_MAX_ID_LENGHT];
	} ClientData;

	fclose(file_client);

	return;
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

int SignUpProcess(void) {

	char TEMP_NAME[CLIENT_MAX_NAME_LENGHT];
	int TEMP_NAME_LENGHT = 0;

	char TEMP_PASSWORD[CLIENT_MAX_HASH_LENGHT];
	int TEMP_PASSWORD_LENGHT = 0;

	char TEMP_HASH[CLIENT_MAX_HASH_LENGHT];

	bool IsValidatingName = true;
	bool IsValidatingPassword = true;

	int ErrorCounter = 0;

	printf("\nThis program is a concept,\n");
	printf("so please do not use any real password\n");
	printf("that you use to avoid potential leak,\n");
	printf("and DO NOT use your real name please\n");

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

	FILE *file_client;

	file_client = fopen("data_client.dat", "a");

	if(file_client == NULL) {
		printf("\nSystem Error\n\n");
		return FAILED;
	}

	typedef struct {
		char name[CLIENT_MAX_NAME_LENGHT];
		char hash[CLIENT_MAX_HASH_LENGHT];
		char id[CLIENT_MAX_ID_LENGHT];
	} ClientData;

	ClientData *NewClient;

	fclose(file_client);

	return SUCCESS;
}
