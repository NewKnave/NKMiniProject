// The contents
void Profile(int ClientID);
void Buy(void);
void Sell(void);
void Cart(void);
void MiniCommerce(int CLIENT_ID, char CLIENT_NAME);

bool IsMiniCommerceRunning = true;

void Profile(int ClientID) {
	bool IsProfileRunning = true;

	FILE *file_client = fopen("data_client.dat", "rb");
	CLIENT client[1];

	while(fread(&client, sizeof(CLIENT), 1, file_client) == 1) {
		if(strcmp(CLIENT_ID, client.id) == 0) {
			break
		}
	}

	while(IsProfileRunning == true) {
		printf("Profile\n");
		printf("Name: %s\n", client.name);
		printf("ID: %s\n\n", client.id);
		printf("[1] Change name\n");
		printf("[2] Change password");
		printf("[3] Exit\n");
		printf("[4] Log out\n");
		printf("User: ");
	}

	fclose(file_client);
	return;
}

void Buy(void) {

	FILE *file_product = fopen("data_markert.dat", "rb");
	if(file_product == NULL) {
		err("Market is empty");
		return;
	} 
	
	COMMERCE product[1];
	int Product_I = 1;

	printf("Number\tID\tPrice\tQuantity\tName");
	while(fread(&product, sizeof(COMMERCE), 1, file_product) {
		printf("%i\t%i\t%f\t%i\t%s", Product_I, product.id, product.price, product.quantity, product.name);
		Product_I++;
	}
	return;
}

void Sell(void) {

	int TEMP_ID = 0;
	char TEMP_NAME[COMMERCE_MAX_NAME_LENGHT];
	float TEMP_PRICE = 0.0f;
	int TEMP_QUANTITY = 0;

	char UserInput[64];
	int Selection;

	bool IsFuncSellRunning = true;

	while(IsFuncSellRunning == true) {
		printf("# Selling #\n");
		printf("[1] Sell product\n");
		printf("[2] Update product\n");
		printf("[3] Remove product\n");
		printf("User: ");
	}

	return;
}

void Cart(void) {

	FILE *file_cart = NULL;

	CART *client_cart = NULL;

	return;
}

void MiniCommerce(int CLIENT_ID) {

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
			Profile(CLIENT_ID);
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
