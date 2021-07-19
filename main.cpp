#include "app.h"
using namespace std;

#ifdef WIN32
#include <windows.h>

int main(int argc, char* argv[]) {
    FreeConsole();
    App a;
    bool t = a.init();
    return a.run();
}

#else

int main(int argc, char* argv[]) {
    App a;
    bool t = a.init();
    return a.run();
}

#endif
