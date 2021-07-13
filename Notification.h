#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <functional>
#include <vector>
using namespace std;

class Notification
{
public:
    Notification(){}
    ~Notification(){}

    void Clear(void);
    void Add(void);
    void Remove(void);

    void Trigger(unsigned int ID);

private:
    vector< function<void(unsigned int)> > FuncVec;

};




#endif