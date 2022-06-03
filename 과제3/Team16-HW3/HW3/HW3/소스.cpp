#include <stdio.h>
#include <string.h>

#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"
#define MAX_MEMBER 100
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

void doTask();
void AddNewMember();
void MembershipWithdrawal();
void CheckIDPW();
void Logout();
void program_exit();

FILE* in_fp, *out_fp;

int main()
{

	in_fp = fopen(INPUT_FILE_NAME, "r+");
	if (in_fp == NULL) {
		printf("input file null");
		return 1;
	}
	out_fp = fopen(OUTPUT_FILE_NAME, "w+");
	if (out_fp == NULL) {
		printf("output file null");
		return 1;
	}

	printf("file read success\n");
	doTask();


	return 0;
}
class Member {
public:

	char memberID[MAX_STRING];
	char memberPW[MAX_STRING];
	char memberName[MAX_STRING];
	char memberResidentNumber[MAX_STRING];

	Member() {
		strcpy(this->memberID, "\0");
		strcpy(this->memberPW, "\0");
		strcpy(this->memberName, "\0");
		strcpy(this->memberResidentNumber, "\0");

	};
	Member(char memberName[], char memberResidentNumber[], char memberID[], char memberPW[]) {
		printf("생성자.");
		strcpy(this->memberID, memberID);
		strcpy(this->memberPW, memberPW);
		strcpy(this->memberName, memberName);
		strcpy(this->memberResidentNumber, memberResidentNumber);
	};
	~Member() {}
	void setmemberData(char ID[], char PW[], char Name[], char ResidentNumber[]) {
		strcpy(this->memberID, ID);
		strcpy(this->memberPW, PW);
		strcpy(this->memberName, Name);
		strcpy(this->memberResidentNumber, ResidentNumber);
	}
	const char* getmemberID() const {
		return memberID;
	}
	const char* getmemberPW() const {
		return memberPW;
	}
};



int now_login_member = -1;
int count = 0;

Member memberlist[MAX_MEMBER] = { Member() };

class MembershipAddControl {
public:
	void AddNewMember(char* memberName, char* memberResidentNumber, char* memberID, char* memberPW)
	{
		memberlist[count].setmemberData(memberID, memberPW, memberName, memberResidentNumber);
		count += 1;

	}
};

class MembershipAddUI {
public:
	void AddNewMember()
	{
		char memberName[MAX_STRING];
		char memberResidentNumber[MAX_STRING];
		char memberID[MAX_STRING];
		char memberPW[MAX_STRING];
		fscanf(in_fp, "%s %s %s %s", memberName, memberResidentNumber, memberID, memberPW);
		fprintf(out_fp, "1.1 회원가입 \n");
		fprintf(out_fp, "%>s %s %s %s\n", memberName, memberResidentNumber, memberID, memberPW);
		MembershipAddControl* membershipadd = new MembershipAddControl;
		membershipadd->AddNewMember(memberName, memberResidentNumber, memberID, memberPW);
	}
};

class MembershipWithdrawalControl {
public:
	void MembershipWithdrawal()
	{
		
		if (now_login_member > -1)
		{
			memberlist[now_login_member] = Member();
			now_login_member = -1;
		}
	}

};
class MembershipWithdrawalUI {
public:
	void MembershipWithdrawal() {
		fprintf(out_fp, "1.2 회원탈퇴 \n");
		const char* ID = memberlist[now_login_member].getmemberID();
		fprintf(out_fp, ">%s\n", ID);
		MembershipWithdrawalControl* membershipwithdrawal = new MembershipWithdrawalControl;
		membershipwithdrawal->MembershipWithdrawal();
	}
};
class LogInControl {
public:
	void CheckIDPW(char* memberID, char* memberPW) {
		for (int i = 0; i < MAX_MEMBER;i++)
		{
			const char* ID = memberlist[i].getmemberID();
			const char* PW = memberlist[i].getmemberPW();
			if (strcmp(ID, memberID) == 0)
			{
				if (strcmp(PW, memberPW) == 0)
				{
					fprintf(out_fp, ">%s, %s\n", memberID, memberPW);
					now_login_member = i;
					break;
				}
			}
		}
	};
};


class LogInUI {
public:
	void CheckIDPW() {

		char memberID[MAX_STRING];
		char memberPW[MAX_STRING];
		fprintf(out_fp, "2.1 로그인\n");
		fscanf(in_fp, "%s %s", memberID, memberPW);
		LogInControl* login = new LogInControl;
		login->CheckIDPW(memberID, memberPW);
	}
};
class LogoutControl {
public:
	void Logout()
	{
		if (now_login_member > -1)
		{
			fprintf(out_fp, ">%s\n", memberlist[now_login_member].getmemberID());
			now_login_member = -1;
		}

	}
};
class LogoutUI {
public:
	void Logout() {
		fprintf(out_fp, "2.2 로그아웃 \n");
		LogoutControl* logout = new LogoutControl;
		int dummy = 0;
		logout->Logout();
	}
};
void doTask()
{
	int menu_level_1 = 0, menu_level_2 = 0;
	int is_program_exit = 0;

	while (!is_program_exit) {
		int result = fscanf(in_fp, "%d %d", &menu_level_1,&menu_level_2);
		if (result == EOF) {
			is_program_exit = 1;
			return;
		}
		MembershipAddUI membershipaddUI;
		MembershipWithdrawalUI membershipwithdrawalUI;
		LogInUI loginUI;
		LogoutUI logoutUI;

		switch (menu_level_1)
		{
			case 1:
			{
				switch (menu_level_2)
				{
				case 1: //1.1 회원가입
					membershipaddUI.AddNewMember();
					break;
				case 2: //1.2 회원탈퇴
					membershipwithdrawalUI.MembershipWithdrawal();
					break;
				}
				break;
			case 2:
				switch (menu_level_2)
				{
				case 1: //2.1 로그인
					loginUI.CheckIDPW();
					break;

				case 2: //2.2 로그아웃
					logoutUI.Logout();
					break;
				}
				break;
			}
		}
	}
	return;
}






