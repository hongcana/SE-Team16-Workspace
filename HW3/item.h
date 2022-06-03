#pragma once

#define MAX_STRING 32

class item
{
private:
	char SellerName[MAX_STRING];			//판매자명
	char ItemName[MAX_STRING];			//상품명
	char ManufacturerName[MAX_STRING];	//제조회사 이름
	int Price;					//가격
	int Score;					//사용자 평점
	int Stock;					//재고
	int ItemAmount;				//판매량
	item* prevItem;
	item* nextItem;
public:
	item();
	item* GetItem();																											//상품 정보를 전달
	void AddNewItem(char* SellerName, char* ItemName, char* ManufacturerName, int Price, int Stock);					//새로 생성한 item의 초기화																					//품절된 상품의 목록을 전달
	void ChangeStock();																											//판매한 상품의 재고 수정
	char* GetSellerName();
	char* GetItemName();
	char* GetManufecturerName();
	int GetPrice();
	int GetScore();
	int GetStock();
	int GetItemAmount();
	item* GetPrevItem();
	item* GetNextItem();
	void SetPrevItem(item* target);
	void SetNextItem(item* target);
};