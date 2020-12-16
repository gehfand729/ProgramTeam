//오픈소스 - blockDmask

//수정및 작성 - 5팀

#define BLACK 0 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTCYAN 11
#define LIGHTMAGENTA 13


#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<conio.h>
#include<Windows.h>
#include<vector>
#include<fstream>
using namespace std;

void textcolor(int foreground, int background)
{
    int color = foreground + background * 16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

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
    system("title [HangManGame] by.오조라고");
}

//시작화면 draw (*수정*)
void DrawReadyGame()
{
    system("cls");
    textcolor(LIGHTCYAN, BLACK);
    gotoxy(5, 2);
    cout << "==============================";
    gotoxy(5, 3);
    cout << "======= HANG MAN GAME ========";
    gotoxy(5, 4);
    cout << "==============================";
    textcolor(BROWN, BLACK);
    gotoxy(6, 6);
    cout << "Level을 입력하세요(1, 2, 3)";
    gotoxy(5, 7);
    cout << "==============================";
    gotoxy(6, 8);
    cout << "Level1: Easy Mode";
    gotoxy(6, 9);
    cout << "Level2: Normal Mode";
    gotoxy(6, 10);
    cout << "Level3: Hard Mode";
    gotoxy(5, 11);
    cout << "==============================";
    textcolor(MAGENTA, BLACK);
    gotoxy(6, 13);
    cout << "종료하려면 '0'를 눌러주세요";
    gotoxy(6, 14);
    cout << "최고 점수 : " << HighestScore << "점"; // 최고 점수 출력
    gotoxy(6, 15);
    cout << "최근 점수 : " << LastScore << "점"; // 최근 플레이한 점수 출력
    gotoxy(9, 16);
    cout << "by. 오조라고" << endl;
}

//게임화면 Draw
void DrawStartGame(int life, int score, vector<string>& pastWord)
{
    textcolor(LIGHTMAGENTA, BLACK);
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
    gotoxy(5, 4);
    cout << "==============================";
    gotoxy(5, 5);
    cout << "========= Game Over ==========";
    gotoxy(5, 6);
    cout << "==============================";
    gotoxy(7, 10);
    cout << "-메인화면으로 돌아가기-";
    gotoxy(10, 11);
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

class State
{
public:
    virtual void 상태버튼() = 0;
};

class StateManager
{
    State* pState;
public:
    StateManager(State* state) : pState(state) {};
    ~StateManager() { if (pState) delete pState; }

    void 상태변경(State* state) { if (pState)delete pState; pState = state; }
    void 상태실행() { pState->상태버튼(); }
};

class Mode
{
public:
    virtual void 모드버튼() = 0;
};

class ModeManager
{
    Mode* mode;
public:
    ModeManager() : mode(0) {};
    ~ModeManager() { if (mode) delete mode; }

    void 모드변경(Mode* pmode) { if (mode) delete mode; mode = pmode; }
    void 모드실행() { mode->모드버튼(); }
};

class ModeA : public Mode       //ModeA클래스에 PressModeButton인터페이스를 임플리먼트한다
{
public:
    void 모드버튼()                  //override(재정의)
    {
        vector<string> pastWord;            //입력한 영단어 저장
        vector<string> strArreasy;          //맞출 단어장
        SetDictionaryEasy(strArreasy);      //read from file

        static int score = 0;
        static int life;

        while (true)    //하나의 턴을 표현하는 루프
        {
            int num = 0;
            srand((unsigned int)time(NULL));    //랜덤함수 : https://blockdmask.tistory.com/308
            num = rand() % static_cast<int>(strArreasy.size());    //단어장 내에 랜덤한 단어 선택

            string strQuestion;                        // _ _ _ _ _ 로 표현할 변수
            const string strOriginal = strArreasy[num];    //단어가 맞는지 정답확인용으로 저장
            const int originLen = static_cast<int>(strOriginal.length());

            for (int i = 0; i < originLen; ++i)
            {
                strQuestion += "_";    //정답 길이만큼 "_"
            }

            life = originLen + 2;           //생명력은 정답 단어 길이 + 2

            while (true)    //하나의 단어를 맞추는 루프
            {
                class 정답 : public State
                {
                public:
                    void 상태버튼()
                    {
                        cout << "Score : " << ++score << endl;
                    };
                };

                class 오답 : public State
                {
                public:
                    void 상태버튼()
                    {
                        cout << "Life : " << --life << endl;
                    }
                };

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
                    int j = 0;
                    for (int i = 0; i < originLen; ++i)
                    {
                        if (strOriginal[i] == strInput[0])    //오리지널 단어에 입력한 알파벳이 있는경우
                        {
                            strQuestion[i] = strInput[0];    // 해당 위치의 "_" 를 알파벳으로 바꿔줌
                            j++;
                        }
                    }

                    if (j == 0)
                    {
                        StateManager* pStateManager = new StateManager(new 오답());
                        pStateManager->상태실행();
                    }
                }
                else if (strInput.length() > 1)    //입력받은 스트링의 길이가 1보다 큰 경우
                {
                    if (strOriginal == strInput) //오리지널 단어랑 입력 단어가 같을때 (정답)
                    {
                        StateManager* pStateManager = new StateManager(new 정답());
                        pStateManager->상태실행();

                        pastWord.clear();
                        break;    //하나의 단어를 맞추는 루프를 나가게되고 다음 턴으로 넘어가게 됩니다.
                    }

                    if (strOriginal != strInput)  //오답일때
                    {
                        StateManager* pStateManager = new StateManager(new 오답());
                        pStateManager->상태실행();
                    }
                }

                //게임오버 
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
                    return;
                }
            }
        }
    }
};

class ModeB : public Mode    //ModeB클래스에 PressModeButton인터페이스를 임플리먼트한다
{
public:
    void 모드버튼()            //override(재정의)
    {
        vector<string> pastWord;            //입력한 영단어 저장
        vector<string> strArrnormal;          //맞출 단어장
        SetDictionaryNormal(strArrnormal);      //read from file

        static int score = 0;
        static int life;

        while (true)    //하나의 턴을 표현하는 루프
        {
            int num = 0;
            srand((unsigned int)time(NULL));    //랜덤함수 : https://blockdmask.tistory.com/308
            num = rand() % static_cast<int>(strArrnormal.size());    //단어장 내에 랜덤한 단어 선택

            string strQuestion;                        // _ _ _ _ _ 로 표현할 변수
            const string strOriginal = strArrnormal[num];    //단어가 맞는지 정답확인용으로 저장
            const int originLen = static_cast<int>(strOriginal.length());

            for (int i = 0; i < originLen; ++i)
            {
                strQuestion += "_";    //정답 길이만큼 "_"
            }

            life = originLen + 2;           //생명력은 정답 단어 길이 + 2

            while (true)    //하나의 단어를 맞추는 루프
            {
                class 정답 : public State
                {
                public:
                    void 상태버튼()
                    {
                        cout << "Score : " << ++score << endl;
                    };
                };

                class 오답 : public State
                {
                public:
                    void 상태버튼()
                    {
                        cout << "Life : " << --life << endl;
                    }
                };

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
                    int j = 0;
                    for (int i = 0; i < originLen; ++i)
                    {
                        if (strOriginal[i] == strInput[0])    //오리지널 단어에 입력한 알파벳이 있는경우
                        {
                            strQuestion[i] = strInput[0];    // 해당 위치의 "_" 를 알파벳으로 바꿔줌
                            j++;
                        }
                    }

                    if (j == 0)
                    {
                        StateManager* pStateManager = new StateManager(new 오답());
                        pStateManager->상태실행();
                    }
                }
                else if (strInput.length() > 1)    //입력받은 스트링의 길이가 1보다 큰 경우
                {
                    if (strOriginal == strInput) //오리지널 단어랑 입력 단어가 같을때 (정답)
                    {
                        StateManager* pStateManager = new StateManager(new 정답());
                        pStateManager->상태실행();

                        pastWord.clear();
                        break;    //하나의 단어를 맞추는 루프를 나가게되고 다음 턴으로 넘어가게 됩니다.
                    }

                    if (strOriginal != strInput)  //오답일때
                    {
                        StateManager* pStateManager = new StateManager(new 오답());
                        pStateManager->상태실행();
                    }
                }

                //게임오버 
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
                    return;
                }
            }
        }
    }
};

class ModeC : public Mode      //ModeB클래스에 PressModeButton인터페이스를 임플리먼트한다
{
public:
    void 모드버튼()               //override(재정의)
    {
        vector<string> pastWord;            //입력한 영단어 저장
        vector<string> strArrhard;          //맞출 단어장
        SetDictionaryHard(strArrhard);      //read from file

        static int score = 0;
        static int life;

        while (true)    //하나의 턴을 표현하는 루프
        {
            int num = 0;
            srand((unsigned int)time(NULL));    //랜덤함수 : https://blockdmask.tistory.com/308
            num = rand() % static_cast<int>(strArrhard.size());    //단어장 내에 랜덤한 단어 선택

            string strQuestion;                        // _ _ _ _ _ 로 표현할 변수
            const string strOriginal = strArrhard[num];    //단어가 맞는지 정답확인용으로 저장
            const int originLen = static_cast<int>(strOriginal.length());

            for (int i = 0; i < originLen; ++i)
            {
                strQuestion += "_";    //정답 길이만큼 "_"
            }

            life = originLen + 2;           //생명력은 정답 단어 길이 + 2

            while (true)    //하나의 단어를 맞추는 루프
            {
                class 정답 : public State
                {
                public:
                    void 상태버튼()
                    {
                        cout << "Score : " << ++score << endl;
                    };
                };

                class 오답 : public State
                {
                public:
                    void 상태버튼()
                    {
                        cout << "Life : " << --life << endl;
                    }
                };

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
                    int j = 0;
                    for (int i = 0; i < originLen; ++i)
                    {
                        if (strOriginal[i] == strInput[0])    //오리지널 단어에 입력한 알파벳이 있는경우
                        {
                            strQuestion[i] = strInput[0];    // 해당 위치의 "_" 를 알파벳으로 바꿔줌
                            j++;
                        }
                    }

                    if (j == 0)
                    {
                        StateManager* pStateManager = new StateManager(new 오답());
                        pStateManager->상태실행();
                    }
                }
                else if (strInput.length() > 1)    //입력받은 스트링의 길이가 1보다 큰 경우
                {
                    if (strOriginal == strInput) //오리지널 단어랑 입력 단어가 같을때 (정답)
                    {
                        StateManager* pStateManager = new StateManager(new 정답());
                        pStateManager->상태실행();

                        pastWord.clear();
                        break;    //하나의 단어를 맞추는 루프를 나가게되고 다음 턴으로 넘어가게 됩니다.
                    }

                    if (strOriginal != strInput)  //오답일때
                    {
                        StateManager* pStateManager = new StateManager(new 오답());
                        pStateManager->상태실행();
                    }
                }

                //게임오버 
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
                    return;
                }
            }
        }
    }
};

int main(int argc, char* argv[])
{
    SetConsoleView();
    ModeManager* modemanager = new ModeManager;   //동적으로 modemanager 할당

    char isStart = 5; // isStart 자료형 char형으로 변경
    while (true)
    {
        isStart = ReadyGame();
        if (isStart == '1')
        {
            modemanager->모드변경(new ModeA());       //easy 모드로 설정
            modemanager->모드실행();                  //실행
        }
        else if (isStart == '2')
        {
            modemanager->모드변경(new ModeB());       //normal 모드로 설정
            modemanager->모드실행();                  //실행
        }
        else if (isStart == '3')
        {
            modemanager->모드변경(new ModeC());       //hard 모드로 설정
            modemanager->모드실행();                  //실행
        }
        else if (isStart == '0')                        //끝내기 기능
        {
            break;
        }
    }
    return 0;
}
