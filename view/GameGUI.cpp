#include "GameGUI.h"


GameGUI::GameGUI(int32_t width, int32_t height, const char *title):
    Fl_Double_Window(width, height, title)
{   
    Fl::set_boxtype(FL_FREE_BOXTYPE, cell_draw, 0, 0, 0, 0);
    begin();
    RandomGenerate = new Fl_Button(xButton, yButtonRG, wButton, hButton, "Randomize");
    Clear = new Fl_Button(xButton, yButtonClear, wButton, hButton, "Clear");
    SingleStep = new Fl_Button(xButton, yButtonSS, wButton, hButton, "Single Step");
    Continue = new Fl_Button(xButton, yButtonConti, wButton, hButton, "Continue");
    Pause = new Fl_Button(xButton, yButtonPa, wButton, hButton, "Pause");
    UserArea = new ViewCells(XField, YField, CellSize, ViewCells_cb);
    end();

    RandomGenerate->labelsize(20);
    Clear->labelsize(20);
    SingleStep->labelsize(20);
    Continue->labelsize(20);
    Pause->labelsize(20);
    RandomGenerate->labelfont(FL_BOLD);
    Clear->labelfont(FL_BOLD);
    SingleStep->labelfont(FL_BOLD);
    Continue->labelfont(FL_BOLD);
    Pause->labelfont(FL_BOLD);
    RandomGenerate->callback(Buttons_cb, &RandomCmd);
    Clear->callback(Buttons_cb, &ClearCmd);
    SingleStep->callback(Buttons_cb, &SingleStepCmd);
    Continue->callback(StartTimer_cb, this);
    Pause->callback(PauseTimer_cb, this);
}


ViewCells *GameGUI::Get_ViewCells(){
    return UserArea;
}


void GameGUI::Set_ClickOnCell_Cmd(std::function<bool(uint32_t, uint32_t)> &&cmd) noexcept {
    ClickCmd = move(cmd);
}


void GameGUI::Set_Random_Cmd(std::function<bool()> &&cmd) noexcept{
    RandomCmd = move(cmd);
}


void GameGUI::Set_Clear_Cmd(std::function<bool()> &&cmd) noexcept{
    ClearCmd = move(cmd);
}


void GameGUI::Set_SingleStep_Cmd(std::function<bool()> &&cmd) noexcept{
    SingleStepCmd = move(cmd);
}


std::function<void(uint32_t)> GameGUI::Get_Notification() noexcept {
    return [this](uint32_t id) {
        if(id == PropID_ColorMatrix)
        {
            UserArea->UpdateCells();
        }
            
    };
}


void GameGUI::ViewCells_cb(Fl_Widget* cell, void* window)
{
    ((GameGUI*)window)->ClickCmd( ((MyCell*)cell)->GetRow(), ((MyCell*)cell)->GetCol() );
}


void GameGUI::Buttons_cb(Fl_Widget* button, void* cmd)
{
    (*static_cast< std::function<bool()>* >(cmd))();
}


void GameGUI::StartTimer_cb(Fl_Widget* button, void* window)
{
    auto* GUIptr = static_cast<GameGUI*>(window);
    if(GUIptr->isIdle)
    {
        GUIptr->isIdle = false;
        Fl::add_timeout(GUIptr->period, Timer, window);
    }
    else
    {
        return;
    }
}


void GameGUI::Timer(void* window)
{
    auto* GUIptr = static_cast<GameGUI*>(window);
    if(GUIptr->isIdle)
    {
        return;
    }
    else
    {
        GUIptr->SingleStepCmd();
        Fl::repeat_timeout(GUIptr->period, Timer, window);
    }
}


void GameGUI::PauseTimer_cb(Fl_Widget* button, void* window)
{
    auto* GUIptr = static_cast<GameGUI*>(window);
    if(GUIptr->isIdle)
    {
        return;
    }
    else
    {
        GUIptr->isIdle = true;
    }
}



