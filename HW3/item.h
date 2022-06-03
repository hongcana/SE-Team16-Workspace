#pragma once

#define MAX_STRING 32

class item
{
private:
	char SellerName[MAX_STRING];			//�Ǹ��ڸ�
	char ItemName[MAX_STRING];			//��ǰ��
	char ManufacturerName[MAX_STRING];	//����ȸ�� �̸�
	int Price;					//����
	int Score;					//����� ����
	int Stock;					//���
	int ItemAmount;				//�Ǹŷ�
	item* prevItem;
	item* nextItem;
public:
	item();
	item* GetItem();																											//��ǰ ������ ����
	void AddNewItem(char* SellerName, char* ItemName, char* ManufacturerName, int Price, int Stock);					//���� ������ item�� �ʱ�ȭ																					//ǰ���� ��ǰ�� ����� ����
	void ChangeStock();																											//�Ǹ��� ��ǰ�� ��� ����
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