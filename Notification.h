#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <functional>
#include <vector>
#include <cstdint>
using namespace std;

class Notification
{
public:
    Notification()= default;
    ~Notification()= default;

    void Clear();
    void Add( function<void(uint32_t)>&& f ){ FuncVec.push_back(move(f)); }
    void Remove();

    void Trigger(uint32_t id);

private:
    vector< function<void(uint32_t)> > FuncVec;

};




#endif