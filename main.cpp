#include <iostream>
#include <memory>
#include "Notification.h"
#include "model.h"
#include "viewmodel.h"
//#include "view.h"
#include "GameGUI.h"

using namespace std;

int main(int, char **) {
    unique_ptr<GameGUI> GUIPtr = make_unique<GameGUI>();
    unique_ptr<ViewModel> ViewModelPtr = make_unique<ViewModel>();
    unique_ptr<Model> ModelPtr = make_unique<Model>();

    //ViewPtr->set_xx_command( ViewModelPtr->get_xx_command() );
    ViewModelPtr->set_xx_ModelCmd( ModelPtr->get_model_modification() );
    GUIPtr->set_ClickOnCell_Cmd([](uint32_t a, uint32_t b)->bool {
        cout << "receive row & col " << a << " " << b << endl;
        return true;
    });

    //ModelPtr->Add( ViewModelPtr->get_Notification() );
    //ViewModelPtr->Add( ViewPtr->get_Notification() );


    //cout << "start mouse click" << endl;
    //ViewPtr->click_callback();
    GUIPtr->show();
    return Fl::run();

}
