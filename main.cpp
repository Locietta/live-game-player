#include <iostream>
#include <memory>
#include "Notification.h"
#include "total.h"
using namespace std;

int main(int, char **) {
    unique_ptr<View> ViewPtr = make_unique<View>();
    unique_ptr<ViewModel> ViewModelPtr = make_unique<ViewModel>();
    unique_ptr<Model> ModelPtr = make_unique<Model>();

    ViewPtr->set_xx_command( ViewModelPtr->get_xx_command() );
    ViewModelPtr->set_xx_ModelCmd( ModelPtr->get_model_modification() );

    ModelPtr->Add( ViewModelPtr->get_Notification() );
    ViewModelPtr->Add( ViewPtr->get_Notification() );


    cout << "start mouse click" << endl;
    ViewPtr->callback();

    




}
