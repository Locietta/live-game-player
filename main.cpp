<<<<<<< HEAD
#include "Notification.h"
#include "model.h"
#include "view.h"
#include "viewmodel.h"
#include <iostream>
#include <memory>
=======
#include <iostream>
#include <memory>

#include "Notification.h"
#include "model.h"
#include "viewmodel.h"
#include "GameGUI.h"
>>>>>>> pr_5

	using namespace std;

int main(int, char **) {
<<<<<<< HEAD
    unique_ptr<View> ViewPtr = make_unique<View>();
    unique_ptr<ViewModel> ViewModelPtr = make_unique<ViewModel>();
    unique_ptr<Model> ModelPtr = make_unique<Model>();

    ViewPtr->set_xx_command(ViewModelPtr->get_xx_command());
    ViewModelPtr->set_xx_ModelCmd(ModelPtr->get_model_modification());

    ModelPtr->Add(ViewModelPtr->get_Notification());
    ViewModelPtr->Add(ViewPtr->get_Notification());

    cout << "start mouse click" << endl;
    ViewPtr->click_callback();
=======
	//*class members
	shared_ptr<GameGUI> GUIPtr = make_shared<GameGUI>();
	shared_ptr<ViewModel> ViewModelPtr = make_shared<ViewModel>();
	//size_t tmp = 30;
    shared_ptr<Model> ModelPtr = make_shared<Model>(GUIPtr->GetMatrixSize(), GUIPtr->get_Notification_UpdateCell());

	// ViewPtr->set_xx_command( ViewModelPtr->get_xx_command() );
	//ViewModelPtr->set_xx_ModelCmd(ModelPtr->get_model_modification());

	//*link members
	ViewModelPtr->LinkToModel(ModelPtr);
	//*link command
	GUIPtr->set_ClickOnCell_Cmd( ViewModelPtr->get_DrawCmd() );
	//*leave for run cmd

	//*link notification
	// ModelPtr->Add(GUIPtr->get_Notification_UpdateCell());
	//ModelPtr->Set_ChangeColor(GUIPtr->get_Notification_UpdateCell());

	// ModelPtr->Add( ViewModelPtr->get_Notification() );
	// ViewModelPtr->Add( ViewPtr->get_Notification() );

	// cout << "start mouse click" << endl;
	// ViewPtr->click_callback();
	GUIPtr->show();
	return Fl::run();
>>>>>>> pr_5
}
