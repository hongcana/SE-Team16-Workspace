#pragma once
#include "item.h"

#define MAX_STRING 32

class Member {
public:

	char memberID[MAX_STRING];
	char memberPW[MAX_STRING];
	char memberName[MAX_STRING];
	char memberResidentNumber[MAX_STRING];
	item* purchasedItems[100];
	item* myItems[100];
	int pCount;
	int myItemCount;

	Member();
	Member(char memberName[], char memberResidentNumber[], char memberID[], char memberPW[]);
	~Member() {}
	void setmemberData(char ID[], char PW[], char Name[], char ResidentNumber[]);
	const char* getmemberID() const;
	const char* getmemberPW() const;
	int getpCount();
	int getMyItemcount();
	void changepCount();
	void changeMyItemCount();
	item* getPurchasedItem(int num);
	void addPurchasedItem(item* item);
	item* getMyItem(int num);
	void addMyItem(item* item);
};
