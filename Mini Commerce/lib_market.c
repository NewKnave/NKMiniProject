#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Buy(void);
void Sell(void);

void ProductAdd(void);
void ProductUpdate(void);
void ProductView(int ID);

void Cart(void);
void CartView(void);
void CartAddProduct(void);
void CartRemoveProduct(void);

void CheckOut(void);

void UserRemoveProduct(void);
void SystemRemoveProduct(void);

void DataSort(void);
void DataSeach(void);

typedef struct
{
	int id;
	char *name;
	float price;
	int quantity;
} DataBase;

DataBase *Buffer;
DataBase *MainData;

void MiniCommerce(void)
{
	return;
}

void Buy(void)
{
	return;
} // End of Buy

void Sell(void)
{
	return;
} // End of Sell

void ProductAdd(void)
{
	return;
} // End of ProductAdd

void ProductUpdate(void)
{
	return;	
} // End of ProductUpdate

void ProductView(int ID)
{
	printf("\nProduct ID: %i\n", MainData[ID].id);
	printf("Name: %s\n", MainData[ID].name);
	printf("Price: %.2f\n", MainData[ID].price);
	printf("Available: %i\n\n", MainData[ID].quantity);
	return;
} // End of ProductView

void Cart(void)
{
	return;
} // End of Cart

void CartView(void)
{
	return;
} // End of CartView

void CartAddProduct(void)
{
	return;
} // End of CartAddProduct

void CartRemoveProduct(void)
{
	return;
} // End of CartRemoveProduct

void CheckOut(void)
{
	return;
} // End of CheckOut

void UserRemoveProduct(void)
{
	return;
} // End if UserRemoveProduct

void SystemRemoveProduct(void)
{
	return;
} // End of SystemRemoveProduct

void DataSort(void)
{
	return;
} // End of DataSort

void DataSeach(void)
{
	return;
} // End of DataSearch