#ifndef _APP_H_
#define _APP_H_

#include "GameGUI.h"
#include "model.h"
#include "viewmodel.h"
#include <memory>

class App {
public:
    App();
    ~App();
    App(const App &) = delete;
    App &operator=(const App &) = delete;

    bool init();
    int run();
private:
    std::shared_ptr<GameGUI> m_GUI;
    std::shared_ptr<ViewModel> m_ViewModel;
    std::shared_ptr<Model> m_Model;
};

#endif // _APP_H_
