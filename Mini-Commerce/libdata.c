const int COMMERCE_MAX_ID_LENGHT = (20 + 1);
const int COMMERCE_MAX_NAME_LENGHT = (64 + 1);

void MiniCommerce(void);
void Profile(void);
void Buy(void);
void Sell(void);
void Cart(void);

bool IsMiniCommerceRunning = true;

void MiniCommerce(void) {

	char UserInput[64];
	int Selection;

	while (IsMiniCommerceRunning == true) {
		printf("# Mini Commerce #\n");
		printf("[1] Profile\n");
		printf("[2] Buy\n");
		printf("[3] Sell\n");
		printf("[4] Cart\n");
		printf("User: ");

		fgets(UserInput, sizeof(UserInput), stdin);
		UserInput[strcspn(UserInput, "\n")] = '\0';
		Selection = atoi(UserInput);

		switch (Selection) {

		case 1:
			Profile();
			break;

		case 2:
			Buy();
			break;

		case 3:
			Sell();
			break;

		case 4:
			Cart();
			break;

		default:
			printf("\n\"%s\" not found\n\n", UserInput);
		}

		fflush(stdin);
	}

	return;
}

void Profile(void) {

	FILE *file_client;

	typedef struct {
		char name[CLIENT_MAX_NAME_LENGHT];
		char hash[CLIENT_MAX_HASH_LENGHT];
		char id[CLIENT_MAX_ID_LENGHT];
	} CommerceData;

	return;
}

void Buy(void) {

	FILE *file_product;

	typedef struct {
		char id[COMMERCE_MAX_ID_LENGHT];
		char name[COMMERCE_MAX_NAME_LENGHT];
		float price;
		int quantity;
	} CommerceData;

	return;
}

void Sell(void) {

	int TEMP_ID;
	char TEMP_NAME[COMMERCE_MAX_NAME_LENGHT];
	float TEMP_PRICE;
	int TEMP_QUANTITY;

	FILE *file_product;

	typedef struct {
		int id[COMMERCE_MAX_ID_LENGHT];
		char name[COMMERCE_MAX_NAME_LENGHT];
		float price;
		int quantity;
	} CommerceData;

	return;
}

void Cart(void) {

	FILE *file_product;

	typedef struct {
		char id[COMMERCE_MAX_ID_LENGHT];
		char name[COMMERCE_MAX_NAME_LENGHT];
		float price;
		int quantity;
	} CommerceData;

	return;
}
