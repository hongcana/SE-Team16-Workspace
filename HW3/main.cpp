#include <iostream>
#include "item.h"
#include "member.h"
using namespace std;

#define INPUT_FILE_NAME "input1.txt"
#define OUTPUT_FILE_NAME "output1.txt"
#define MAX_MEMBER 100

item first;
int now_login_member = -1;
int memberCount = 0;
Member memberlist[MAX_MEMBER] = { Member() };

class MembershipAddControl {
public:
	void AddNewMember(char* memberName, char* memberResidentNumber, char* memberID, char* memberPW)
	{
		memberlist[memberCount].setmemberData(memberID, memberPW, memberName, memberResidentNumber);
		memberCount += 1;
	}
};

class MembershipAddUI {
public:
	void AddNewMember(FILE* in_fp, FILE* out_fp)
	{
		char memberName[MAX_STRING];
		char memberResidentNumber[MAX_STRING];
		char memberID[MAX_STRING];
		char memberPW[MAX_STRING];
		fscanf_s(in_fp, "%s %s %s %s", memberName, sizeof(memberName), memberResidentNumber, sizeof(memberResidentNumber), memberID, sizeof(memberID), memberPW, sizeof(memberPW));
		fprintf(out_fp, "1.1. 회원가입 \n");
		fprintf(out_fp, "> %s %s %s %s\n\n", memberName, memberResidentNumber, memberID, memberPW);
		MembershipAddControl* membershipadd = new MembershipAddControl;
		membershipadd->AddNewMember(memberName, memberResidentNumber, memberID, memberPW);
		delete membershipadd;
	}
};

class MembershipWithdrawalControl {
public:
	void MembershipWithdrawal()
	{
		if (now_login_member > -1){
			memberlist[now_login_member] = Member();
			now_login_member = -1;
		}
	}

};
class MembershipWithdrawalUI {
public:
	void MembershipWithdrawal(FILE* out_fp) {
		fprintf(out_fp, "1.2. 회원탈퇴 \n");
		const char* ID = memberlist[now_login_member].getmemberID();
		fprintf(out_fp, "> %s\n\n", ID);
		MembershipWithdrawalControl* membershipwithdrawal = new MembershipWithdrawalControl;
		membershipwithdrawal->MembershipWithdrawal();
		delete membershipwithdrawal;
	}
};

class LogInControl {
public:
	bool isCheckIDPW(char* memberID, char* memberPW) {
		for (int i = 0; i < MAX_MEMBER; i++){
			const char* ID = memberlist[i].getmemberID();
			const char* PW = memberlist[i].getmemberPW();
			if (strcmp(ID, memberID) == 0 && strcmp(PW, memberPW) == 0){
				now_login_member = i;
				return true;
			}
		}
	};
};

class LogInUI {
public:
	void CheckIDPW(FILE* in_fp, FILE* out_fp) {

		char memberID[MAX_STRING];
		char memberPW[MAX_STRING];
		fprintf(out_fp, "2.1. 로그인\n");
		fscanf_s(in_fp, "%s %s", memberID, sizeof(memberID), memberPW, sizeof(memberPW));
		LogInControl* login = new LogInControl;
		if (login->isCheckIDPW(memberID, memberPW)) {
			fprintf(out_fp, "> %s %s\n\n", memberID, memberPW);
		}
		delete login;
	}
};
class LogoutControl {
public:
	void Logout()
	{
		if (now_login_member > -1){
			now_login_member = -1;
		}
	}
};
class LogoutUI {
public:
	void Logout(FILE* out_fp) {
		fprintf(out_fp, "2.2 로그아웃 \n");
		LogoutControl* logout = new LogoutControl;
		int dummy = 0;
		fprintf(out_fp, "> %s\n\n", memberlist[now_login_member].getmemberID());
		logout->Logout();
		delete logout;
	}
};

class AddItemUIcontrol
{
public:
	void AddNewItem(const char* UserName, char* ItemName, char* ManufacturerName, int Price, int Stock)
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
		memberlist[now_login_member].addMyItem(newItem);
		memberlist[now_login_member].changeMyItemCount();
	}
};

// 상품 추가
class AddItemUI
{
public:
	void CreateNewItem(FILE* in_fp, FILE* out_fp)
	{
		char ItemName[MAX_STRING], ManufacturerName[MAX_STRING];
		int ItemPrice = 0, Stock = 0;

		fprintf(out_fp, "3.1. 판매 의류 등록\n");
		fscanf_s(in_fp, "%s %s %d %d ",
						ItemName, 
						sizeof(ItemName), 
						ManufacturerName, 
						sizeof(ManufacturerName), 
						&ItemPrice, 
						&Stock);
		AddItemUIcontrol* control = new AddItemUIcontrol;
		control->AddNewItem(memberlist[now_login_member].getmemberID(), ItemName, ManufacturerName, ItemPrice, Stock);
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

//등록된 상품 목록 출력
class ShowItemUI
{
public:
	void ShowSellingItem(FILE* out_fp)	
	{
		item ItemList[100];

		fprintf(out_fp, "3.2. 등록 상품 조회\n");
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

//판매 완료 아이템 목록 출력
class ShowSoldoutItemUI
{
public:
	void ShowSoldoutItems(FILE* out_fp) 
	{
		item ItemList[100];

		fprintf(out_fp, "3.3. 판매 완료 상품 조회\n");
		ShowSoldoutItemUIcontrol* control = new ShowSoldoutItemUIcontrol;
		int itemNum = control->ShowSoldoutItems(ItemList);
		for (int i = 0; i < itemNum; i++) {
			fprintf(out_fp, "> %s %s %d %d %.1f\n",
				ItemList[i].GetItemName(),
				ItemList[i].GetManufecturerName(),
				ItemList[i].GetPrice(),
				ItemList[i].GetItemAmount(),
				ItemList[i].GetMeanScore());
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

//상품 정보 출력, 상품 구입
class ItemInfoUI
{
private:
	item* currentItem = NULL;
public:
	void ShowItemInfo(FILE* in_fp, FILE* out_fp)	
	{
		char ItemName[MAX_STRING];

		fprintf(out_fp, "4.1. 상품 정보 검색\n");
		fscanf_s(in_fp, "%s ", ItemName, sizeof(ItemName));
		ItemInfoUIcontrol* control = new ItemInfoUIcontrol;
		this->currentItem = control->GetItemInfo(ItemName);
		fprintf(out_fp, "> %s %s %s %d %d %.1f\n\n", 
						this->currentItem->GetSellerName(), 
						this->currentItem->GetItemName(), 
						this->currentItem->GetManufecturerName(), 
						this->currentItem->GetPrice(), 
						this->currentItem->GetStock(), 
						this->currentItem->GetMeanScore());
		memberlist[now_login_member].addPurchasedItem(currentItem);
		memberlist[now_login_member].changepCount();
		delete control;
	}
	void PurchaseItem(FILE* out_fp)
	{
		fprintf(out_fp, "4.2. 상품 구매\n");
		ItemInfoUIcontrol* control = new ItemInfoUIcontrol;
		control->PurchaseItem(this->currentItem);
		fprintf(out_fp, "> %s %s\n\n", 
						this->currentItem->GetSellerName(),
						this->currentItem->GetItemName());
		delete control;
	}
};

class BuyRecordUI
{
public:
	void GetBuyrecords(FILE* in_fp, FILE* out_fp) 
	{
		fprintf(out_fp, "4.3. 상품 구매 내역 조회\n");
		for (int i = 0; i < memberlist[now_login_member].getpCount(); i++) {
			fprintf(out_fp, "> %s %s %s %d %d %.1f\n",
				memberlist[now_login_member].getPurchasedItem(i)->GetSellerName(),
				memberlist[now_login_member].getPurchasedItem(i)->GetItemName(),
				memberlist[now_login_member].getPurchasedItem(i)->GetManufecturerName(),
				memberlist[now_login_member].getPurchasedItem(i)->GetPrice(),
				memberlist[now_login_member].getPurchasedItem(i)->GetStock(),
				memberlist[now_login_member].getPurchasedItem(i)->GetMeanScore());
		}
		fprintf(out_fp, "\n");
	}
};

class SetScoreUIControl
{
public:
	item* SetItemScore(char* ItemName, int Score)
	{
		item* tmpItem = first.GetNextItem();
		while (tmpItem->GetNextItem() != &first) {
			if (!strcmp(tmpItem->GetItemName(), ItemName))
				break;
			else
				tmpItem = tmpItem->GetNextItem();
		}
		tmpItem->AddScore(Score);
		return tmpItem;
	}
};

class SetScoreUI
{
public:
	void SetScore(FILE* in_fp, FILE* out_fp)
	{
		fprintf(out_fp, "4.4. 상품 구매만족도 평가\n");
		char ItemName[MAX_STRING];
		int ItemScore;
		item* currentItem;
		fscanf_s(in_fp, "%s %d ", ItemName, sizeof(ItemName), &ItemScore);
		SetScoreUIControl* control = new SetScoreUIControl;
		currentItem = control->SetItemScore(ItemName, ItemScore);
		fprintf(out_fp, "> %s %s %d\n\n", currentItem->GetSellerName(), currentItem->GetItemName(), ItemScore);
		delete control;
	}
};

class ItemsStatusUIcontrol
{
public:
	int getItemList(item* ItemList)
	{
		int count = 0;
		for (int i = 0; i < memberlist[now_login_member].getMyItemcount(); i++) {
			ItemList[i] = *memberlist[now_login_member].getMyItem(i);
			count++;
		}
		return count;
	}
};

class ItemsStatusUI
{
public:
	void getItemsStatus(FILE* out_fp)
	{
		fprintf(out_fp, "5.1. 판매 상품 통계\n");
		ItemsStatusUIcontrol* control = new ItemsStatusUIcontrol;
		if (memberlist[now_login_member].getMyItemcount() > 0) {
			item ItemList[100];
			int itemNum = control->getItemList(ItemList);
			for (int i = 0; i < itemNum; i++) {
				fprintf(out_fp, "> %s %d %.1f\n",
					ItemList[i].GetItemName(),
					ItemList[i].GetPrice() *ItemList[i].GetItemAmount(),
					ItemList[i].GetMeanScore());
			}
		}
		fprintf(out_fp, "\n");
		delete control;
	}
};

//종료
void Program_exit(FILE* out_fp)	
{
	fprintf(out_fp, "6.1. 종료\n");
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
	MembershipAddUI membershipaddUI;
	MembershipWithdrawalUI membershipwithdrawalUI;
	LogInUI loginUI;
	LogoutUI logoutUI;
	AddItemUI addItemUI;
	ShowItemUI showItemUI;
	ShowSoldoutItemUI showSoldoutItemUI;
	ItemInfoUI itemInfoUI;
	BuyRecordUI buyRecordUI;
	SetScoreUI setScoreUI;
	ItemsStatusUI itemsStatusUI;

	while (!is_program_exit){
		fscanf_s(in_fp, "%d %d ", &menu_level_1, &menu_level_2);

		switch (menu_level_1){
		case 1:
			switch (menu_level_2){
			case 1:		//1.1. 회원가입
				membershipaddUI.AddNewMember(in_fp, out_fp);
				break;
			case 2:		//1.2. 회원탈퇴
				membershipwithdrawalUI.MembershipWithdrawal(out_fp);
				break;
			}
			break;
		case 2:
			switch (menu_level_2){
			case 1:		//2.1. 로그인
				loginUI.CheckIDPW(in_fp, out_fp);
				break;
			case 2:		//2.2. 로그아웃
				logoutUI.Logout(out_fp);
				break;
			}
			break;
		case 3:			
			switch (menu_level_2){
			case 1:		//3.1. 판매 의류 등록
				addItemUI.CreateNewItem(in_fp, out_fp);
				break;
			case 2:		//3.2. 등록 상품 조회
				showItemUI.ShowSellingItem(out_fp);
				break;
			case 3:		//3.3. 판매 완료 상품 조회
				showSoldoutItemUI.ShowSoldoutItems(out_fp);
				break;
			}
			break;
		case 4:		
			switch (menu_level_2){
			case 1:		//4.1. 상품 정보 검색
				itemInfoUI.ShowItemInfo(in_fp, out_fp);
				break;
			case 2:		//4.2. 상품 구매
				itemInfoUI.PurchaseItem(out_fp);
				break;
			case 3:		//4.3. 상품 구매내역 조회
				buyRecordUI.GetBuyrecords(in_fp, out_fp);
				break;
			case 4:		//4.4. 상품 구매만족도 평가
				setScoreUI.SetScore(in_fp, out_fp);
				break;
			}
			break;
		case 5:
			switch (menu_level_2){
			case 1:		//5.1. 판매 상품 통계
				itemsStatusUI.getItemsStatus(out_fp);
				break;
			}
			break;
		case 6:
			switch (menu_level_2){
			case 1:		//6.1. 종료
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