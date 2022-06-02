#include <stdio.h>
#include <string.h>

#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"
#define MAX_MEMBER 100

void doTask();
void join();
void program_exit();

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
	Member();
	Member(char memberName, int memberResidentNumber, char memberID, char memberPW);
	char memberID;
	char memberPW;
	char memberName;
	int memberResidentNumber;
	void AddMemberInformation();
	void CheckIDPW();
	void DeleteMemberInformation();
	void CheckValidIDPW();
};
int member_count = 0;
int now_login_member = NULL;
Member memberlist[MAX_MEMBER];

void AddNewMember(char memberName, int memberResidentNumber, char memberID, char memberPW);
void ShowCheckWithdrawal();
void MembershipWithdrawal();
void CheckIDPW();
void Logout();
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
				case 1: //1.1 È¸¿ø°¡ÀÔ
					char name;
					int resident_id;
					char id;
					char pw;
					AddNewMember(name, resident_id,id,pw);
				case 2: //1.2 È¸¿øÅ»Åð
					ShowCheckWithdrawal();
					MembershipWithdrawal();
				}
			case 2:
				switch (menu_level_2)
				{
				case 1: //2.1 ·Î±×ÀÎ
					CheckIDPW();
				case 2: //2.2 ·Î±×¾Æ¿ô
					Logout();
				}

			}
		}
	}
}

void AddNewMember(char memberName, int memberResidentNumber, char memberID, char memberPW) {
	int result = fscanf(in_fp, "%c %d %c %c", &memberName, &memberResidentNumber,&memberID, &memberPW);
	Member member = Member(memberName, memberResidentNumber, memberID, memberPW);
	memberlist[member_count] = member;
	member_count += 1;
	printf("%c %d %c %c", memberName, memberResidentNumber, memberID, memberPW);
}


void ShowCheckWithdrawal();
void MembershipWithdrawal();
void CheckIDPW(char memberID, char memberPW) {
	int result = fscanf(in_fp, "%c %c", &memberID, &memberPW);
	for (int i = 0; i < MAX_MEMBER;i++) {
		if (memberlist[i].memberID == memberID && memberlist[i].memberPW == memberPW) {
			printf("%c, %c", memberID, memberPW);
			now_login_member = i;
		}
		else
			printf("\n");
	}
};
void Logout() {
	printf("%c", memberlist[now_login_member].memberID);
	now_login_member = NULL;
}