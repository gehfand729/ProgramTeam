//작성자 : 20193478 

#include<iostream>
using namespace std;

static int score = 0;
static int life = 5;
class State
{
public:
    virtual void 상태() = 0;
};

class IsStart : public State
{
public:
    void 상태() { cout << "Game Start" << endl; };
};

class 정답 : public State
{
public:
    void 상태() { cout << "Score : " << ++score << endl; };
};

class 오답 : public State
{
public:
    void 상태()
    {
        cout << "Life : " << --life << endl;
        if (life == 0) { cout << "Game Over" << endl; }
    }
};

class 행맨
{
    State* pState;
public:
    행맨(State* state) : pState(state) {};
    ~행맨() { if (pState)delete pState; }
    void 상태변경(State* state) { if (pState)delete pState; pState = state; }
    void 상태() { pState->상태(); }

};

int main()
{
    행맨* p행맨 = new 행맨(new IsStart());
    p행맨->상태();

    p행맨->상태변경(new 정답());
    p행맨->상태();
    p행맨->상태();
    p행맨->상태();
    p행맨->상태();

    p행맨->상태변경(new 오답());
    p행맨->상태();
    p행맨->상태();
    p행맨->상태();
    p행맨->상태();

    delete p행맨;
    return 0;
}
