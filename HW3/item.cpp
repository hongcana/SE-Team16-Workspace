#include <iostream>
#include "item.h"

item::item()
{
	this->prevItem = NULL; 
	this->nextItem = NULL; 
}

item* item::GetItem()
{
	if (this->nextItem)
		return this->nextItem;
	else
		return this;
}

void item::AddNewItem(const char* SellerName, char* ItemName, char* ManufacturerName, int Price, int Stock)
{
	strcpy_s(this->SellerName, MAX_STRING, SellerName);
	strcpy_s(this->ItemName, MAX_STRING, ItemName);
	strcpy_s(this->ManufacturerName, MAX_STRING, ManufacturerName);
	this->Price = Price;
	this->meanScore = 0;
	memset(this->Score, 0, sizeof(this->Score));
	this->ScoreCount = 0;
	this->Stock = Stock;
	this->ItemAmount = 0;
}

void item::ChangeStock()
{
	this->Stock--;
	this->ItemAmount++;
}

char* item::GetSellerName() 
{
	return this->SellerName; 
}

char* item::GetItemName() 
{
	return this->ItemName; 
}

char* item::GetManufecturerName() 
{
	return this->ManufacturerName; 
}

int item::GetPrice() 
{
	return this->Price; 
}

float item::GetMeanScore() 
{
	float sum = 0;
	for (int i = 0; i < this->ScoreCount; i++)
		sum += this->Score[i];
	if (sum != 0)
		return sum / this->ScoreCount;
	else
		return 0;
}

int item::GetStock() 
{
	return this->Stock; 
}

int item::GetItemAmount() 
{
	return this->ItemAmount; 
}

item* item::GetPrevItem() 
{
	return this->prevItem; 
}

item* item::GetNextItem() 
{
	return this->nextItem; 
}

void item::SetPrevItem(item* target)
{
	this->prevItem = target;
}

void item::SetNextItem(item* target)
{
	this->nextItem = target;
}

void item::AddScore(int Score)
{
	this->Score[this->ScoreCount] = Score;
	this->ScoreCount++;
}