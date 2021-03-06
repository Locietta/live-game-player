#include "app.h"

using namespace std;

App::App() = default;

App::~App() = default;

//-------------------- default map size -----------------------
const int32_t defaultRowNum = 160;
const int32_t defaultColNum = 160;

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
    m_GUI->Get_ViewCells()->BindColorMapping(m_ViewModel->GetColorMapping());

    // commands
    m_GUI->Set_ClickOnCell_Cmd(m_ViewModel->get_DrawCmd());
    m_GUI->Set_Clear_Cmd(m_ViewModel->get_ClearCmd());
    m_GUI->Set_Random_Cmd(m_ViewModel->get_RandomizeCmd());
    m_GUI->Set_SingleStep_Cmd(m_ViewModel->get_SingleStepCmd());
    return true;
}

int App::run() {
    m_Model->init(0.142857, 7);
    m_GUI->show();
    return Fl::run();
}