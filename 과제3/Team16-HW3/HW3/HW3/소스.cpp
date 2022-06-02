#include <stdio.h>
#include <string.h>

#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"
#define MAX_MEMBER 100
#define _CRT_SECURE_NO_WARNINGS

void doTask();
void AddNewMember();
void MembershipWithdrawal();
void CheckIDPW();
void Logout();
//void program_exit();

FILE* in_fp, * out_fp;

int main()
{

	FILE* in_fp = fopen(INPUT_FILE_NAME, "r+");
	FILE* out_fp = fopen(OUTPUT_FILE_NAME, "W+");


	doTask();


	return 0;
}
class Member {
public:

	char memberID;
	char memberPW;
	char memberName;
	char memberResidentNumber;

	Member() {
		memberID = NULL;
		memberPW = NULL;
		memberName = NULL;
		memberResidentNumber = NULL;

	};
	Member(char memberName, char memberResidentNumber, char memberID, char memberPW) {
		memberID = memberName;
		memberPW = memberResidentNumber;
		memberName = memberID;
		memberResidentNumber = memberPW;
	};
	/* 멤버 함수인데 당장은 필요없을듯 하다.
	void AddMemberInformation();
	void CheckIDPW();
	void DeleteMemberInformation();
	void CheckValidIDPW();
	*/
};
int now_login_member = NULL;
Member memberlist[MAX_MEMBER] = { Member() };

void doTask()
{
	int menu_level_1 = 0, menu_level_2 = 0;
	int is_program_exit = 0;
	while (!is_program_exit) {
		fscanf(in_fp, "%d %d", &menu_level_1,&menu_level_2);

		switch (menu_level_1)
		{
			case 1:
			{
				switch (menu_level_2)
				{
				case 1: //1.1 회원가입
					AddNewMember();
				case 2: //1.2 회원탈퇴
					MembershipWithdrawal();
				}
			case 2:
				switch (menu_level_2)
				{
				case 1: //2.1 로그인
					CheckIDPW();

				case 2: //2.2 로그아웃
					Logout();
				}

			}
		}
	}
	return;
}

void AddNewMember()
{
	char memberName[MAX_STRING];
	char memberResidentNumber[MAX_STRING];
	char memberID[MAX_STRING];
	char memberPW[MAX_STRING];
	fscanf(in_fp, "%s %s %s %s", memberName, memberResidentNumber, memberID, memberPW);
	Member newmember(memberName[MAX_STRING], memberResidentNumber[MAX_STRING], memberID[MAX_STRING], memberPW[MAX_STRING]);
	for (int i = 0; i < MAX_MEMBER;i++) {
		if (memberlist[i].memberID != NULL)
		{
			memberlist[i] = newmember;
			fprintf(out_fp, "1.1 회원가입 \n");
			fprintf(out_fp, "%s %s %s %s\n", memberName, memberResidentNumber, memberID, memberPW);
		}
	}
}



void MembershipWithdrawal()
{
	if(now_login_member > -1)
	{	
		fprintf(out_fp, "1.2 회원탈퇴 \n");
		memberlist[now_login_member] = Member();
		fprintf(out_fp, "%s\n", memberlist[now_login_member].memberID);
		now_login_member = -1;
	}
}
void CheckIDPW() {
	char memberID[MAX_STRING];
	char memberPW[MAX_STRING];
	fscanf(in_fp, "%s %s", memberID, memberPW);
	for (int i = 0; i < MAX_MEMBER;i++) 
	{
		if (&memberlist[i].memberID == memberID && memberPW == &memberlist[i].memberPW)
		{
			fprintf(out_fp, "2.1 로그인\n");
			fprintf(out_fp, "%s, %s\n", memberID, memberPW);
			now_login_member = i;
		}
	}
};
void Logout()
{
	if (now_login_member > -1)
	{
		fprintf(out_fp, "2.2 로그아웃 \n");
		fprintf(out_fp, "%s\n", memberlist[now_login_member].memberID);
		now_login_member = -1;
	}
	else
		printf("현재 로그인 되지 않았습니다.");
}