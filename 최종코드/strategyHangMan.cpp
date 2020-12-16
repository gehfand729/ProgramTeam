// 작성자 : 20193439 김로하
//코드 원본 : blockDmask

#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<conio.h>
#include<Windows.h>
#include<vector> 
#include<fstream>  
using namespace std;

int LastScore = 0;  //게임 종료시 최근 플레이 점수를 저장할 전역변수 할당
int HighestScore = 0;  //최고 점수를 저장할 전역변수 할당

//콘솔 내부의 특정 위치로 커서를 이동시키는 함수
void gotoxy(int x, int y)
{
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//keyboard 입력
int GetKeyDown()
{
    if (_kbhit() != 0)
    {
        return _getch();
    }
    return 0;
}

//콘솔 셋팅
void SetConsoleView()
{
    system("mode con:cols=50 lines=20");
    system("title [HangManGame] by.BlockDMask");
}

//시작화면 draw (*수정*)
void DrawReadyGame()
{
    system("cls");
    gotoxy(5, 2);
    cout << "==============================";
    gotoxy(5, 3);
    cout << "======= HANG MAN GAME ========";
    gotoxy(5, 4);
    cout << "==============================";
    gotoxy(6, 6);
    cout << "Level을 입력하세요(1, 2, 3)";
    gotoxy(5, 7);
    cout << "==============================";
    gotoxy(6, 8);
    cout << "Level1: Easy Mode;";
    gotoxy(6, 9);
    cout << "Level2: Normal Mode";
    gotoxy(6, 10);
    cout << "Level3: Hard Mode";
    gotoxy(5, 11);
    cout << "==============================";
    gotoxy(6, 13);
    cout << "종료하려면 '0'를 눌러주세요";
    gotoxy(6, 14);
    cout << "최고 점수 : " << HighestScore << "점"; // 최고 점수 출력
    gotoxy(6, 15);
    cout << "최근 점수 : " << LastScore << "점"; // 최근 플레이한 점수 출력
    gotoxy(9, 16);
    cout << "by. BlockDMask" << endl;
}

//게임화면 Draw
void DrawStartGame(int life, int score, vector<string>& pastWord)
{
    system("cls");
    gotoxy(5, 1);
    cout << "life = " << life;
    gotoxy(5, 2);
    cout << "score = " << score;
    gotoxy(5, 8);
    cout << "past = ";

    for (int i = 0; i < static_cast<int>(pastWord.size()); ++i)
    {
        cout << pastWord[i] << " ";
    }

    gotoxy(5, 12);
    cout << "input = ";
    gotoxy(13, 14);
    cout << "메인화면 'qq'" << endl;
}

//사전을 셋팅하는 함수(*수정*)
void SetDictionaryEasy(vector<string>& strArreasy)
{
    ifstream readFromFile;  //file -> program
    readFromFile.open("Level1_words.txt");  //Level1 파일 열기

    if (readFromFile.is_open())
    {
        while (!readFromFile.eof())
        {
            string tmp;
            getline(readFromFile, tmp);
            strArreasy.push_back(tmp);
        }
    }
    readFromFile.close();  //읽기 전용 파일 닫음
    return;
}

void SetDictionaryNormal(vector<string>& strArrnormal)
{
    ifstream readFromFile;
    readFromFile.open("Level2_words.txt");  //Level2 파일 열기

    if (readFromFile.is_open())
    {
        while (!readFromFile.eof())
        {
            string tmp;
            getline(readFromFile, tmp);
            strArrnormal.push_back(tmp);
        }
    }
    readFromFile.close();
    return;
}

void SetDictionaryHard(vector<string>& strArrhard)
{
    ifstream readFromFile;
    readFromFile.open("Level3_words.txt");  //Level3 파일 열기

    if (readFromFile.is_open())
    {
        while (!readFromFile.eof())
        {
            string tmp;
            getline(readFromFile, tmp);
            strArrhard.push_back(tmp);
        }
    }
    readFromFile.close();
    return;
}

//시작화면 기능(*수정*)
int ReadyGame()
{
    DrawReadyGame();

    while (true)
    {
        char key = GetKeyDown(); // 자료형 char형으로 변경, 레벨 설정 기능
        if (key == '1')
        {
            return '1';
        }
        else if (key == '2')
        {
            return '2';
        }
        else if (key == '3')
        {
            return '3';
        }
        else if (key == '0') // 끝내기 기능
        {
            return '0';
        }
    }
    return 0;
}

//게임오버 화면 Draw (*추가*)
void DrawGameOver()
{
    system("cls");
    gotoxy(5, 2);
    cout << "==============================";
    gotoxy(5, 3);
    cout << "========= Game Over ==========";
    gotoxy(5, 4);
    cout << "==============================";
    gotoxy(7, 8);
    cout << "다시 시작하겠습니까?";
    gotoxy(10, 9);
    cout << "Y or N";
}

//게임오버 기능 (*추가*)
bool GameOver()
{
    DrawGameOver(); //게임오버 화면 그리기
    while (true)
    {
        int key = GetKeyDown();
        if (key == 'y' || key == 'Y')
        {
            break;
        }
        else if (key == 'n' || key == 'N')
        {
            exit(1);
        }
    }

}

class PressModeButton                  //버튼 역할
{
public:
    virtual void pressmodebutton() = 0;     //순수가상함수(인터페이스로 인식시키려고)
};

class ModeA : public PressModeButton        //ModeA클래스에 PressModeButton인터페이스를 임플리먼트한다
{
public:
    void pressmodebutton()                  //override(재정의)
    {
        int score = 0;
        vector<string> pastWord;    //입력한 영단어 저장
        vector<string> strArreasy;        //맞출 단어장
        SetDictionaryEasy(strArreasy);        //read from file

        while (true)    //하나의 턴을 표현하는 루프
        {
            //1 play
            int num = 0;
            srand((unsigned int)time(NULL));    //랜덤함수 : https://blockdmask.tistory.com/308
            num = rand() % static_cast<int>(strArreasy.size());    //단어장 내에 랜덤한 단어 선택

            string strQuestion;                        // _ _ _ _ _ 로 표현할 변수
            const string strOriginal = strArreasy[num];    //단어가 맞는지 정답확인용으로 저장
            const int originLen = static_cast<int>(strOriginal.length());

            //init
            for (int i = 0; i < originLen; ++i)
            {
                strQuestion += "_";    //정답 길이만큼 "_"
            }

            int life = originLen + 2;    //생명력은 정답 단어 길이 + 2

            //1 question
            while (true)    //하나의 단어를 맞추는 루프
            {
                DrawStartGame(life, score, pastWord);    //사용단어, 생명력, 점수표기

                //draw question
                gotoxy(5, 5);
                for (int i = 0; i < originLen; ++i)
                {
                    cout << strQuestion[i] << " ";    // _ _ _ _ 표기
                }
                cout << endl;

                //input
                gotoxy(9, 12);
                string strInput;
                cin >> strInput;    //입력 받기.
                if (strInput == "qq")
                {
                    return;
                }
                pastWord.push_back(strInput);    //한번 입력한 단어는 pastword에서 표기

                if (strInput.length() == 1)        //입력받은 스트링의 길이가 1인경우
                {
                    //alphabet
                    for (int i = 0; i < originLen; ++i)
                    {
                        if (strOriginal[i] == strInput[0])    //오리지널 단어에 입력한 알파벳이 있는경우
                        {
                            strQuestion[i] = strInput[0];    // 해당 위치의 "_" 를 알파벳으로 바꿔줌 
                        }
                    }
                }
                else if (strInput.length() > 1)    //입력받은 스트링의 길이가 1보다 큰 경우
                {
                    //word
                    if (strOriginal == strInput) //오리지널 단어랑 입력 단어가 같을때 (정답)
                    {
                        //score up !!
                        score += 5;
                        pastWord.clear();
                        break;    //하나의 단어를 맞추는 루프를 나가게되고 다음 탄으로 넘어가게 됩니다.
                    }
                }

                //무조건 깎이는 라이프 -> 게임오버 구현으로 *수정*
                if (life < 1)
                {
                    LastScore = score;  //게임오버시, 최근점수에 현 점수를 카피하여 저장
                    if (LastScore > HighestScore)  //최근점수가 최고점수보다 크면 최근점수를 최고점수에 저장
                    {
                        HighestScore = LastScore;
                    }
                    pastWord.clear();
                    score = 0;

                    GameOver();
                    break;
                }
                else life -= 1; // 단순 위치 이동(코드 정리) ??
            }
        }
    }
};

class ModeB : public PressModeButton    //ModeB클래스에 PressModeButton인터페이스를 임플리먼트한다
{
public:
    void pressmodebutton()            //override(재정의)
    {
        int score = 0;
        vector<string> pastWord;    //입력한 영단어 저장
        vector<string> strArrnormal;        //맞출 단어장
        SetDictionaryNormal(strArrnormal);        //read from file

        while (true)    //하나의 턴을 표현하는 루프
        {
            //1 play
            int num = 0;
            srand((unsigned int)time(NULL));    //랜덤함수 : https://blockdmask.tistory.com/308
            num = rand() % static_cast<int>(strArrnormal.size());    //단어장 내에 랜덤한 단어 선택

            string strQuestion;                        // _ _ _ _ _ 로 표현할 변수
            const string strOriginal = strArrnormal[num];    //단어가 맞는지 정답확인용으로 저장
            const int originLen = static_cast<int>(strOriginal.length());

            //init
            for (int i = 0; i < originLen; ++i)
            {
                strQuestion += "_";    //정답 길이만큼 "_"
            }

            int life = originLen + 2;    //생명력은 정답 단어 길이 + 2

            //1 question
            while (true)    //하나의 단어를 맞추는 루프
            {
                DrawStartGame(life, score, pastWord);    //사용단어, 생명력, 점수표기

                //draw question
                gotoxy(5, 5);
                for (int i = 0; i < originLen; ++i)
                {
                    cout << strQuestion[i] << " ";    // _ _ _ _ 표기
                }
                cout << endl;

                //input
                gotoxy(9, 12);
                string strInput;
                cin >> strInput;    //입력 받기.
                if (strInput == "qq")
                {
                    return;
                }
                pastWord.push_back(strInput);    //한번 입력한 단어는 pastword에서 표기

                if (strInput.length() == 1)        //입력받은 스트링의 길이가 1인경우
                {
                    //alphabet
                    for (int i = 0; i < originLen; ++i)
                    {
                        if (strOriginal[i] == strInput[0])    //오리지널 단어에 입력한 알파벳이 있는경우
                        {
                            strQuestion[i] = strInput[0];    // 해당 위치의 "_" 를 알파벳으로 바꿔줌 
                        }
                    }
                }
                else if (strInput.length() > 1)    //입력받은 스트링의 길이가 1보다 큰 경우
                {
                    //word
                    if (strOriginal == strInput) //오리지널 단어랑 입력 단어가 같을때 (정답)
                    {
                        //score up !!
                        score += 5;
                        pastWord.clear();
                        break;    //하나의 단어를 맞추는 루프를 나가게되고 다음 탄으로 넘어가게 됩니다.
                    }
                }

                //무조건 깎이는 라이프 -> 게임오버 구현으로 수정
                if (life < 1)
                {
                    LastScore = score;  //게임오버시, 최근점수에 현 점수를 카피하여 저장
                    if (LastScore > HighestScore)  //최근점수가 최고점수보다 크면 최근점수를 최고점수에 저장
                    {
                        HighestScore = LastScore;
                    }
                    pastWord.clear();
                    GameOver();
                    break;
                }
                else life -= 1; // 단순 위치 이동(코드 정리)
            }
        }
    }
};

class ModeC : public PressModeButton      //ModeB클래스에 PressModeButton인터페이스를 임플리먼트한다
{
public:
    void pressmodebutton()               //override(재정의)
    {
        int score = 0;
        vector<string> pastWord;    //입력한 영단어 저장
        vector<string> strArrhard;        //맞출 단어장
        SetDictionaryHard(strArrhard);        //read from file

        while (true)    //하나의 턴을 표현하는 루프
        {
            //1 play
            int num = 0;
            srand((unsigned int)time(NULL));    //랜덤함수 : https://blockdmask.tistory.com/308
            num = rand() % static_cast<int>(strArrhard.size());    //단어장 내에 랜덤한 단어 선택

            string strQuestion;                        // _ _ _ _ _ 로 표현할 변수
            const string strOriginal = strArrhard[num];    //단어가 맞는지 정답확인용으로 저장
            const int originLen = static_cast<int>(strOriginal.length());

            //init
            for (int i = 0; i < originLen; ++i)
            {
                strQuestion += "_";    //정답 길이만큼 "_"
            }

            int life = originLen + 2;    //생명력은 정답 단어 길이 + 2

            //1 question
            while (true)    //하나의 단어를 맞추는 루프
            {
                DrawStartGame(life, score, pastWord);    //사용단어, 생명력, 점수표기

                //draw question
                gotoxy(5, 5);
                for (int i = 0; i < originLen; ++i)
                {
                    cout << strQuestion[i] << " ";    // _ _ _ _ 표기
                }
                cout << endl;

                //input
                gotoxy(9, 12);
                string strInput;
                cin >> strInput;    //입력 받기.
                if (strInput == "qq")
                {
                    return;
                }
                pastWord.push_back(strInput);    //한번 입력한 단어는 pastword에서 표기

                if (strInput.length() == 1)        //입력받은 스트링의 길이가 1인경우
                {
                    //alphabet
                    for (int i = 0; i < originLen; ++i)
                    {
                        if (strOriginal[i] == strInput[0])    //오리지널 단어에 입력한 알파벳이 있는경우
                        {
                            strQuestion[i] = strInput[0];    // 해당 위치의 "_" 를 알파벳으로 바꿔줌 
                        }
                    }
                }
                else if (strInput.length() > 1)    //입력받은 스트링의 길이가 1보다 큰 경우
                {
                    //word
                    if (strOriginal == strInput) //오리지널 단어랑 입력 단어가 같을때 (정답)
                    {
                        //score up !!
                        score += 5;
                        pastWord.clear();
                        break;    //하나의 단어를 맞추는 루프를 나가게되고 다음 탄으로 넘어가게 됩니다.
                    }
                }

                //무조건 깎이는 라이프 -> 게임오버 구현으로 수정
                if (life < 1)
                {
                    LastScore = score;  //게임오버시, 최근점수에 현 점수를 카피하여 저장
                    if (LastScore > HighestScore)  //최근점수가 최고점수보다 크면 최근점수를 최고점수에 저장
                    {
                        HighestScore = LastScore;
                    }
                    pastWord.clear();
                    GameOver();
                    break;
                }
                else life -= 1; // 단순 위치 이동(코드 정리)
            }
        }
    }
};

class ModeManager                        //실질적으로 모드 정보를 저장하고 설정하고 실행해준다
{
    PressModeButton* mode;                  //상태를 저장할 수 있는 저장공간

public:
    ModeManager() : mode(0) {};               //생성자
    ~ModeManager() { if (mode) delete mode; }   //저장되어 있는 상태 삭제하는 소멸자

    void ModeChange(PressModeButton* pmode)      //모드를 바꿔주는 함수(바꿔줄 모드 선택)
    {
        if (mode) delete mode;               //mode에 저장되어 있는 값이 있으면 삭제
        mode = pmode;                     //mode에 바꿔줄 모드를 카피하여 저장
    }

    void ModeExcute()                     //모드를 실행해주는 함수
    {
        mode->pressmodebutton();            //저장되어 있는 모드 버튼
    }
};

int main(int argc, char* argv[])
{
    ModeManager* modemanager = new ModeManager;   //동적으로 modemanager 할당
    SetConsoleView();
    char isStart = 5; // isStart 자료형 char형으로 변경
    while (true)
    {
        isStart = ReadyGame();
        if (isStart == '1') // level 1일때
        {
            modemanager->ModeChange(new ModeA());      //easy 모드로 설정
            modemanager->ModeExcute();               //실행
        }
        else if (isStart == '2') //level 1과 같음
        {
            modemanager->ModeChange(new ModeB());      //normal 모드로 설정
            modemanager->ModeExcute();               //실행
        }
        else if (isStart == '3') // level 1과 같음
        {
            modemanager->ModeChange(new ModeC());      //hard 모드로 설정
            modemanager->ModeExcute();               //실행
        }
        else if (isStart == '0') // 끝내기 기능
        {
            break;
        }
    }
    return 0;
}
