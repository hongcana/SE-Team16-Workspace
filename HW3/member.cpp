#include <iostream>
#include "member.h"

Member::Member() {
	this->pCount = 0;
	this->myItemCount = 0;
	strcpy_s(this->memberID, "\0");
	strcpy_s(this->memberPW, "\0");
	strcpy_s(this->memberName, "\0");
	strcpy_s(this->memberResidentNumber, "\0");
};

Member::Member(char memberName[], char memberResidentNumber[], char memberID[], char memberPW[]) {
	this->pCount = 0;
	this->myItemCount = 0;
	strcpy_s(this->memberID, memberID);
	strcpy_s(this->memberPW, memberPW);
	strcpy_s(this->memberName, memberName);
	strcpy_s(this->memberResidentNumber, memberResidentNumber);
};

void Member::setmemberData(char ID[], char PW[], char Name[], char ResidentNumber[]) {
	strcpy_s(this->memberID, ID);
	strcpy_s(this->memberPW, PW);
	strcpy_s(this->memberName, Name);
	strcpy_s(this->memberResidentNumber, ResidentNumber);
}

const char* Member::getmemberID() const {
	return this->memberID;
}

const char* Member::getmemberPW() const {
	return this->memberPW;
}

int Member::getpCount(){
	return this->pCount;
}

int Member::getMyItemcount() {
	return this->myItemCount;
}

void Member::changepCount() {
	this->pCount++;
}

void Member::changeMyItemCount() {
	this->myItemCount++;
}

item* Member::getPurchasedItem(int num){
	return this->purchasedItems[num];
}

void Member::addPurchasedItem(item* item) {
	this->purchasedItems[pCount] = item;
}

item* Member::getMyItem(int num) {
	return this->myItems[num];
}

void Member::addMyItem(item* item) {
	this->myItems[myItemCount] = item;
}