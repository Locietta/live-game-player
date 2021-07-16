#include "GameGUI.h"
#include "Notification.h"
#include "model.h"
#include "viewmodel.h"
#include <iostream>
#include <memory>

using namespace std;

int main(int, char **) {
    //*class members
    auto GUIPtr = make_shared<GameGUI>();
    auto ViewModelPtr = make_shared<ViewModel>();
    auto ModelPtr = make_shared<Model>();

    ViewModelPtr->Add(GUIPtr->Get_Notification());
    ModelPtr->Add(ViewModelPtr->get_Notification());

    //*link members
    ViewModelPtr->LinkToModel(ModelPtr);
    GUIPtr->BindColor(ViewModelPtr->Get2DBoolMat());
    
    //*link command
    GUIPtr->set_ClickOnCell_Cmd(ViewModelPtr->get_DrawCmd());

    ModelPtr->init();
    GUIPtr->show();
    return Fl::run();
}
