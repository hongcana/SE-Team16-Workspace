#include <iostream>
#include "item.h"
using namespace std;

#define INPUT_FILE_NAME "input1.txt"
#define OUTPUT_FILE_NAME "output1.txt"
item first;

class AddItemUIcontrol
{
public:
	void AddNewItem(char* UserName, char* ItemName, char* ManufacturerName, int Price, int Stock)
	{
		item* newItem = new item;
		newItem->AddNewItem(UserName, ItemName, ManufacturerName, Price, Stock);
		item* tmpItem = &first;
		while (tmpItem->GetNextItem() != NULL && tmpItem->GetNextItem() != &first) {
			tmpItem = tmpItem->GetNextItem();
		}
		tmpItem->SetNextItem(newItem);
		newItem->SetPrevItem(tmpItem);
		first.SetPrevItem(newItem);
		newItem->SetNextItem(&first);
	}
};

// ��ǰ �߰�
class AddItemUI
{
public:
	void CreateNewItem(FILE* in_fp, FILE* out_fp)
	{
		char userName[MAX_STRING] = "chulsoo";
		char ItemName[MAX_STRING], ManufacturerName[MAX_STRING];
		int ItemPrice = 0, Stock = 0;

		fprintf(out_fp, "3.1. �Ǹ� �Ƿ� ���\n");
		fscanf_s(in_fp, "%s %s %d %d ",
						ItemName, 
						sizeof(ItemName), 
						ManufacturerName, 
						sizeof(ManufacturerName), 
						&ItemPrice, 
						&Stock);
		AddItemUIcontrol* control = new AddItemUIcontrol;
		control->AddNewItem(userName, ItemName, ManufacturerName, ItemPrice, Stock);
		fprintf(out_fp, "> %s %s %d %d\n\n", ItemName, ManufacturerName, ItemPrice, Stock);
		delete control;
	}
};

class ShowItemUIcontrol
{
public:
	int ShowSellingItem(item* ItemList)
	{
		item* tmpItem = &first;
		int i = 0;

		while (tmpItem->GetItem() != &first){
			tmpItem = tmpItem->GetItem();
			if (tmpItem->GetStock() != 0){
				ItemList[i] = *tmpItem;
				i++;
			}
		}
		return i;
	}
};

//��ϵ� ��ǰ ��� ���
class ShowItemUI
{
public:
	void ShowSellingItem(FILE* out_fp)	
	{
		item ItemList[100];

		fprintf(out_fp, "3.2. ��� ��ǰ ��ȸ\n");
		ShowItemUIcontrol* control = new ShowItemUIcontrol;
		int itemNum = control->ShowSellingItem(ItemList);
		for (int i = 0; i < itemNum; i++) {
			fprintf(out_fp, "> %s %s %d %d\n",
				ItemList[i].GetItemName(),
				ItemList[i].GetManufecturerName(),
				ItemList[i].GetPrice(),
				ItemList[i].GetStock());
		}
		fprintf(out_fp, "\n");
		delete control;
	}
};

class ShowSoldoutItemUIcontrol
{
public:
	int ShowSoldoutItems(item* ItemList)
	{
		item* tmpItem = &first;
		int i = 0;

		while (tmpItem->GetItem() != &first){
			tmpItem = tmpItem->GetItem();
			if (tmpItem->GetStock() == 0 && tmpItem->GetItemAmount() > 0){
				ItemList[i] = *tmpItem;
				i++;
			}
		}
		return i;
	}
};

//�Ǹ� �Ϸ� ������ ��� ���
class ShowSoldoutItemUI
{
public:
	void ShowSoldoutItems(FILE* out_fp) 
	{
		item ItemList[100];

		fprintf(out_fp, "3.3. �Ǹ� �Ϸ� ��ǰ ��ȸ\n");
		ShowSoldoutItemUIcontrol* control = new ShowSoldoutItemUIcontrol;
		int itemNum = control->ShowSoldoutItems(ItemList);
		for (int i = 0; i < itemNum; i++) {
			fprintf(out_fp, "> %s %s %d %d %d\n",
				ItemList[i].GetItemName(),
				ItemList[i].GetManufecturerName(),
				ItemList[i].GetPrice(),
				ItemList[i].GetItemAmount(),
				ItemList[i].GetScore());
		}
		fprintf(out_fp, "\n");
		delete control;
	}
};

class ItemInfoUIcontrol
{
public:
	item* GetItemInfo(char* ItemName)
	{
		item* tmpItem = first.GetNextItem();
		while (tmpItem->GetNextItem() != &first){
			if (!strcmp(tmpItem->GetItemName(), ItemName))
				break;
			else
				tmpItem = tmpItem->GetNextItem();
		}
		return tmpItem;
	}
	void PurchaseItem(item* currentItem)
	{
		currentItem->ChangeStock();
	}
};

//��ǰ ���� ���, ��ǰ ����
class ItemInfoUI
{
private:
	item* currentItem;
public:
	void ShowItemInfo(FILE* in_fp, FILE* out_fp)	
	{
		char ItemName[MAX_STRING];

		fprintf(out_fp, "4.1. ��ǰ ���� �˻�\n");
		fscanf_s(in_fp, "%s ", ItemName, sizeof(ItemName));
		ItemInfoUIcontrol* control = new ItemInfoUIcontrol;
		this->currentItem = control->GetItemInfo(ItemName);
		fprintf(out_fp, "> %s %s %s %d %d %d\n\n", 
						this->currentItem->GetSellerName(), 
						this->currentItem->GetItemName(), 
						this->currentItem->GetManufecturerName(), 
						this->currentItem->GetPrice(), 
						this->currentItem->GetStock(), 
						this->currentItem->GetScore());
		delete control;
	}
	void PurchaseItem(FILE* out_fp)
	{
		fprintf(out_fp, "4.2. ��ǰ ����\n");
		ItemInfoUIcontrol* control = new ItemInfoUIcontrol;
		control->PurchaseItem(this->currentItem);
		fprintf(out_fp, "%s %s\n\n", 
						this->currentItem->GetSellerName(),
						this->currentItem->GetItemName());
		delete control;
	}
};

//����
void Program_exit(FILE* out_fp)	
{
	fprintf(out_fp, "6.1. ����\n");
	item* tmpItem = first.GetPrevItem();
	while (tmpItem != &first){
		tmpItem = tmpItem->GetPrevItem();
		delete tmpItem->GetNextItem();
	}
}

void doTask(FILE* in_fp, FILE* out_fp)
{
	int menu_level_1 = 0, menu_level_2 = 0; 
	int is_program_exit = 0;
	char tmp1[MAX_STRING], tmp2[MAX_STRING], tmp3[MAX_STRING], tmp4[MAX_STRING];
	int tmpInt1;
	item* currentItem = NULL;
	AddItemUI addItemUI;
	ShowItemUI showItemUI;
	ShowSoldoutItemUI showSoldoutItemUI;
	ItemInfoUI itemInfoUI;

	while (!is_program_exit){
		fscanf_s(in_fp, "%d %d ", &menu_level_1, &menu_level_2);

		switch (menu_level_1){
		case 1:
			switch (menu_level_2){
			case 1:
				fscanf_s(in_fp, "%s %s %s %s", tmp1, sizeof(tmp1), tmp2, sizeof(tmp2), tmp3, sizeof(tmp3), tmp4, sizeof(tmp4));
				break;
			case 2:		
				break;
			}
			break;
		case 2:
			switch (menu_level_2){
			case 1:
				fscanf_s(in_fp, "%s %s ", tmp1, sizeof(tmp1), tmp2, sizeof(tmp2));
				break;
			case 2:
				break;
			}
			break;
		case 3:			//�Ǹ� �Ƿ� ���, ��� ��ǰ ��ȸ, �Ǹ� �Ϸ� ��ǰ ��ȸ
			switch (menu_level_2){
			case 1:		//�Ǹ� �Ƿ� ���
				addItemUI.CreateNewItem(in_fp, out_fp);
				break;
			case 2:		//��� ��ǰ ��ȸ
				showItemUI.ShowSellingItem(out_fp);
				break;
			case 3:		//�Ǹ� �Ϸ� ��ǰ ��ȸ
				showSoldoutItemUI.ShowSoldoutItems(out_fp);
				break;
			}
			break;
		case 4:			//��ǰ ���� �˻�, ��ǰ ����
			switch (menu_level_2){
			case 1:		//��ǰ ���� �˻�
				itemInfoUI.ShowItemInfo(in_fp, out_fp);
				break;
			case 2:		//��ǰ ����
				itemInfoUI.PurchaseItem(out_fp);
				break;
			case 3:
				break;
			case 4:
				fscanf_s(in_fp, "%s %d ", tmp1, sizeof(tmp1), &tmpInt1);
				break;
			}
			break;
		case 5:
			switch (menu_level_2){
			case 1:
				break;
			}
			break;
		case 6:
			switch (menu_level_2){
			case 1:
				Program_exit(out_fp);
				is_program_exit = 1;
				break;
			}
			break;
		}
	}
}

int main()
{
	FILE* in_fp;
	FILE* out_fp;
	fopen_s(&in_fp, INPUT_FILE_NAME, "r+");
	fopen_s(&out_fp, OUTPUT_FILE_NAME, "w+");

	doTask(in_fp, out_fp);

	fclose(in_fp);
	fclose(out_fp);
	return 0;
}