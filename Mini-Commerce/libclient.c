#define SUCCESS 0
#define FAILED 1

typedef struct
{
	char *name;
	char *password;
	int id;
} ClientData;

ClientData *user;

int ClientIDCounter = 0;
int TotalClients = 0;

int ClientSession = 0;

int SignIn(void);
int SignInProcess(void);
void SignUp(void);
int SignUpProcess(void);

int SignIn(void)
{
	int ValidClientID = SignInProcess();

	if(ValidClientID >= 10) {
		printf("\nWelcome user\n\n");
		ClientSession = ValidClientID;
		return SUCCESS;
	}

	else if(ValidClientID == 0) {
		printf("\nSign in failed\n\n");
		return FAILED;
	}

	else {
		printf("\nSystem Error\n\n");
		return FAILED;
	}
}

int SignInProcess(void)
{
	if(TotalClients == 0) {
		printf("\nZero user had signed up");
		return 0;
	}

	char NameInput[64];
	char PasswordInput[64];
	int PasswordLenght;
	char HashCache[64];

	printf("\nName: ");
	fgets(NameInput, sizeof(NameInput), stdin);
	NameInput[strcspn(NameInput, "\n")] = '\0';

	printf("Password: ");
	fgets(PasswordInput, sizeof(PasswordInput), stdin);
	PasswordInput[strcspn(PasswordInput, "\n")] = '\0';
	PasswordLenght = strlen(PasswordInput);

	for(int i = 0; i < PasswordLenght; i++) {
		HashCache[i] = ((PasswordInput[i] % 10) + '0');
	}
	HashCache[PasswordLenght] = '\0';

	for(int i = 0; i < TotalClients; i++) {
		if(strcmp(NameInput, user[i].name) == 0 && strcmp(HashCache, user[i].password) == 0) {
			return user[i].id;
		}
	}

	printf("\nInvalid user name or password");
	return 0;
}

void SignUp(void)
{
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

int SignUpProcess(void)
{
	char NameInput[64];
	int NameLenght = 0;
	char PasswordInput[64];
	int PasswordLenght = 0;
	char HashCache[64];

	bool IsValidatingName = true;
	bool IsValidatingPassword = true;
	int ErrorCounter = 0;

	printf("\nPlease do not use your real name\n");
	printf("Minimum name lenght is 4\n");
	printf("Maximum name lenght is 64\n");
	while(IsValidatingName == true) {
		printf("\nEnter name: ");
		fgets(NameInput, sizeof(NameInput), stdin);
		NameInput[strcspn(NameInput, "\n")] = '\0';
		NameLenght = strlen(NameInput);

		if(NameLenght >= 4 && NameLenght <= 64) {
			ErrorCounter = 0;
			IsValidatingName = false;
		}

		else if(ErrorCounter == 2) {
			printf("Too many errors, exiting\n");
			return FAILED;
		}

		else {
			printf("Invalid name, please try again\n");
			ErrorCounter++;
		}
	}

	printf("\nMinimum password lenght is 8\n");
	printf("Maximum password lenght is 64\n\n");
	while(IsValidatingPassword == true) {
		printf("Password: ");
		fgets(PasswordInput, sizeof(PasswordInput), stdin);
		PasswordInput[strcspn(PasswordInput, "\n")] = '\0';
		PasswordLenght = strlen(PasswordInput);

		if(PasswordLenght >= 8 && PasswordLenght <= 64) {
			IsValidatingPassword = false;
		}

		else if(ErrorCounter == 2) {
			printf("Too many errors, exiting\n");
			return FAILED;
		}

		else {
			printf("Invalid password, please try again\n\n");
			ErrorCounter++;
		}
	}

	ClientIDCounter = ClientIDCounter + 10;
	TotalClients = TotalClients + 1;
	int ArrayLocation = (TotalClients - 1);

	user = realloc(user, TotalClients * sizeof(user));
	if(user == NULL) {
		printf("System error - LC1 - Memory allocation failure\n");
		return FAILED;
	}

	// Name
	user[ArrayLocation].name = malloc(NameLenght * sizeof(char));
	if(user[ArrayLocation].name == NULL) {
		printf("System error - LC2 - Memory allocation failure\n");
		return FAILED;
	}
	strcpy(user[ArrayLocation].name, NameInput);

	// Password
	user[ArrayLocation].password = malloc(PasswordLenght * sizeof(char));
	if(user[ArrayLocation].password == NULL) {
		printf("System error - LC3 - Memory allocation failure\n");
		return FAILED;
	}

	// Mini hash
	for(int i = 0; i < PasswordLenght; i++) {
		HashCache[i] = ((PasswordInput[i] % 10) + '0');
	}
	HashCache[PasswordLenght] = '\0';
	strcpy(user[ArrayLocation].password, HashCache);

	// ID
	user[ArrayLocation].id = ClientIDCounter;

	return SUCCESS;
}