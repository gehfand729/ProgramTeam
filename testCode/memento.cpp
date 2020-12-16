//작성자 : 20183487 이승찬

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Memento
{
    int life;
public:
    Memento(int nLife) :
        life(nLife) {}
    friend class NState;

};

class NState
{
    vector<shared_ptr<Memento>>changes;
    int current;
public:
    int life = 0;
    explicit NState(const int nLife) :life(nLife)
    {
        changes.emplace_back(make_shared<Memento>(nLife));
        current = 0;
    }
    shared_ptr<Memento>save(int sLife)
    {
        life = sLife;
        auto m = make_shared<Memento>(life);
        changes.push_back(m);
        ++current;
        return m;
    }
    void restore(const shared_ptr<Memento>& m)
    {
        if (m)
        {
            life = m->life;
            changes.push_back(m);
            current = changes.size() - 1;
        }
    }

    shared_ptr<Memento> undo()
    {
        if (current > 0)
        {
            --current;
            auto m = changes[current];
            life = m->life;
            return m;
        }
        return {};
    }
};

int main()
{
    NState test{ 100 };
    cout << test.life << endl;
    test.save(20);
    cout << test.life << endl;
    test.undo();
    cout << test.life << endl;

}
