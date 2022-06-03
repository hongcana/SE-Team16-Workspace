// 헤더 선언
#include <iostream>
#include <cstdio>
#include <string>

#define _CRT_SECURE_NO_WARNINGS

// 상수 선언
#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

// 함수 선언
void doTask();
void join();

// 변수 선언
FILE* in_fp;
FILE* out_fp;
int menu_level_1 = 0, menu_level_2 = 0;


//
class Product {
private:
    std::string seller_id;
    std::string product_id;
    std::string maker_id;
    int p_price;
    int p_remaining;
    int p_mean_score;

public:
    Product(std::string sellername, std::string productname, std::string makername, int price)
    {
        seller_id = sellername;
        product_id = productname;
        maker_id = makername;
        p_price = price;
        p_remaining = 0;
        p_mean_score = 0;
    }

    void getBuyrecords()
    {
        std::cout << seller_id << " " << product_id << " " << maker_id << " " << p_price << " " << p_remaining << " " << p_mean_score << std::endl;

    }
    void setMeanScore(int newScore)
    {
        p_mean_score = newScore;
    }
};

//sample
Product sample("mbc", "hat", "chulsoo", 2000);

int main()
{
    // 파일 입출력을 위한 초기화
    in_fp = fopen(INPUT_FILE_NAME, "r+");
    out_fp = fopen(OUTPUT_FILE_NAME, "w+");
    int is_program_exit = 0;

    while (!is_program_exit)
    {
        // 입력파일에서 메뉴 숫자 2개를 읽기
        fscanf(in_fp, "%d %d", &menu_level_1, &menu_level_2);
        std::cout << "read " << menu_level_1 << " and " << menu_level_2 << std::endl;

        // 메뉴 구분 및 해당 연산 수행
        switch (menu_level_1)
        {
            case 1:
            {
                switch (menu_level_2)
                {
                case 1:
                {
                    break;
                }
                case 2:
                {
                    break;
                }
                }
                break;
            }
            case 2:
            {
                switch (menu_level_2)
                {
                case 1:
                {
                    break;
                }
                case 2:
                {
                    break;
                }
                }
                break;
            }
            case 3:
            {
                switch (menu_level_2)
                {
                case 1:
                {
                    break;
                }
                case 2:
                {
                    break;
                }
                case 3:
                {
                    break;
                }
                }
                break;
            }
        case 4:
        {
            switch (menu_level_2)
            {
            case 1:   // "1.1. 회원가입“ 메뉴 부분
            {
                // join() 함수에서 해당 기능 수행 
                join();

                break;
            }
            case 2:
            {
                break;
            }
            case 3:
            {
                sample.getBuyrecords();
                break;
            }
            case 4:
            {
                sample.setMeanScore(3);
                break;
            }
            }
            break;
        }
        case 5:
            switch (menu_level_2)
            {
            case 1:
            {
                break;
            }
            }
        case 6:
        {
            switch (menu_level_2)
            {
            case 1:   // "6.1. 종료“ 메뉴 부분
            {
                is_program_exit = 1;
                break;
            }
            }
            break;
        }
        }
    }
    return 0;
}

void doTask() {}

void join()
{
    char user_type[MAX_STRING], name[MAX_STRING], SSN [MAX_STRING],
        address[MAX_STRING], ID[MAX_STRING], password[MAX_STRING];

    // 입력 형식 : 이름, 주민번호, ID, Password를 파일로부터 읽음
    fscanf(in_fp, "%s %s %s %s", name, SSN, ID, password);

    // 해당 기능 수행  

    // 출력 형식
    fprintf(out_fp, "1.1. 회원가입\n");
    fprintf(out_fp, "%s %s %s %s\n", name, SSN, ID, password);
}




