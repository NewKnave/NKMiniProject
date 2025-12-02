#define SUCCESS 0
#define FAILED 1

const int CLIENT_MAX_NAME_LENGHT = (64 + 1);
const int CLIENT_MAX_HASH_LENGHT = (64 + 1);
const int CLIENT_MAX_ID_LENGHT = (20 + 1);

int CurrentClientSession(void);
int SignInValidation(void);
void SignInProcess(void);

void SignUp(void);
int SignUpProcess(void);

int SignInValidation(void) {

	SignInProcess();

	return SUCCESS;
}

void SignInProcess(void) {

	FILE *file_client;

	file_client = fopen("data_client", "r");

	if(file_client == NULL) {
		printf("\nNo data\n\n");
		fclose(file_client);
		return;
	}

	typedef struct {
		char name[CLIENT_MAX_NAME_LENGHT];
		char hash[CLIENT_MAX_HASH_LENGHT];
		char id[CLIENT_MAX_ID_LENGHT];
	} ClientData;

	ClientData client[1];

	char FETCH_NAME[CLIENT_MAX_NAME_LENGHT];
	char FETCH_HASH[CLIENT_MAX_HASH_LENGHT];

	printf("Name: ");
	fgets(FETCH_NAME, sizeof(FETCH_NAME), stdin);
	FETCH_NAME[strcspn(FETCH_NAME, "\n")] = '\0';

	printf("Password: ");
	fgets(FETCH_HASH, sizeof(FETCH_HASH), stdin);
	FETCH_HASH[strcspn(FETCH_HASH, "\n")] = '\0';

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

void SimpleHash(const char *input, char *output, int out_len) {
    unsigned long hash = 5381;
    int c;
    while ((c = *input++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    // Convert hash to hex string
    snprintf(output, out_len, "%lx", hash);
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
    printf("so please do not input any password\n");
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

        if(TEMP_NAME_LENGHT >= 4 && TEMP_NAME_LENGHT <= (CLIENT_MAX_NAME_LENGHT - 1)) {
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

	// Resetting the error counter to be reuse in the password
    ErrorCounter = 0;

    printf("\nPlease input a password\n");
    printf("Minimum password lenght is 8 characters\n");
    printf("Maximum password lenght is %i characters\n", (CLIENT_MAX_HASH_LENGHT - 1));
    while(IsValidatingPassword == true) {
        printf("Password: ");
        fgets(TEMP_PASSWORD, sizeof(TEMP_PASSWORD), stdin);
        TEMP_PASSWORD[strcspn(TEMP_PASSWORD, "\n")] = '\0';
        TEMP_PASSWORD_LENGHT = strlen(TEMP_PASSWORD);

        if(TEMP_PASSWORD_LENGHT >= 8 && TEMP_PASSWORD_LENGHT <= (CLIENT_MAX_HASH_LENGHT - 1)) {
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

    // Calculate the hash from scratch
    SimpleHash(TEMP_PASSWORD, TEMP_HASH, CLIENT_MAX_HASH_LENGHT);

    FILE *file_client = fopen("data_client.dat", "ab");
    if(file_client == NULL) {
        printf("\nSystem Error\n\n");
        return FAILED;
    }

    typedef struct {
        char name[CLIENT_MAX_NAME_LENGHT];
        char hash[CLIENT_MAX_HASH_LENGHT];
        char id[CLIENT_MAX_ID_LENGHT];
    } ClientData;

    ClientData client;

    strcpy(client.name, TEMP_NAME);
    strcpy(client.hash, TEMP_HASH);

    snprintf(client.id, CLIENT_MAX_ID_LENGHT, "C%ld", time(NULL));

    fwrite(&client, sizeof(ClientData), 1, file_client);

    fclose(file_client);

    return SUCCESS;
}
