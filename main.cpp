#include "app.h"

using namespace std;

int main(int, char **) {
    App a;
    bool t = a.init();
    return a.run();
}
