#include <iostream>
using namespace std;

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
        cout << "Easy mode" << endl;
    }
};

class ModeB : public PressModeButton      //ModeB클래스에 PressModeButton인터페이스를 임플리먼트한다
{
public:
    void pressmodebutton()               //override(재정의)
    {
        cout << "Normal mode" << endl;
    }
};

class ModeC : public PressModeButton      //ModeB클래스에 PressModeButton인터페이스를 임플리먼트한다
{
public:
    void pressmodebutton()               //override(재정의)
    {
        cout << "Hard mode" << endl;
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

int main()
{
    ModeManager* modemanager = new ModeManager;   //동적으로 modemanager 할당

    modemanager->ModeChange(new ModeA());      //easy 모드로 설정
    modemanager->ModeExcute();               //실행

    modemanager->ModeChange(new ModeB());      //normal 모드로 설정
    modemanager->ModeExcute();               //실행

    modemanager->ModeChange(new ModeC());      //hard 모드로 설정
    modemanager->ModeExcute();               //실행
}
