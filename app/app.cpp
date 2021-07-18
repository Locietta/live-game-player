#include "app.h"

using namespace std;

App::App() = default;

App::~App() = default;

//-------------------- main window info -----------------------
static const uint32_t WindowWidth = 1000;
static const uint32_t WindowHeight = 800;
static const char *WindowTitle = "Conway Life Game";

bool App::init() {
    m_GUI = make_shared<GameGUI>(WindowWidth, WindowHeight, WindowTitle);
    
    m_ViewModel = make_shared<ViewModel>();
    m_Model = make_shared<Model>();
    m_ViewModel->LinkToModel(m_Model);
    
    // Notification
    m_ViewModel->add(m_GUI->Get_Notification());
    m_Model->add(m_ViewModel->get_Notification());
    
    // binding
    m_GUI->Get_ViewCells()->BindColor(m_ViewModel->Get2DBoolMat());
    
    // commands
    m_GUI->Set_ClickOnCell_Cmd(m_ViewModel->get_DrawCmd());
    return true;

}

int App::run() {
    m_Model->init();
    m_GUI->show();
    return Fl::run();
}