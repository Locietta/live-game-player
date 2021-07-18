#include "GameGUI.h"

GameGUI::GameGUI(uint32_t width, uint32_t height, const char *title):
    Fl_Window(width, height, title)
{   
    Fl::set_boxtype(FL_FREE_BOXTYPE, cell_draw, 0, 0, 0, 0);
    begin();
    UserArea = new ViewCells(XField, YField, CellSize, ViewCells_cb);
    end();
}

ViewCells *GameGUI::Get_ViewCells(){
    return UserArea;
}

void GameGUI::Set_ClickOnCell_Cmd(std::function<bool(uint32_t, uint32_t)> &&cmd) noexcept {
    ClickCmd = move(cmd);
}

std::function<void(uint32_t)> GameGUI::Get_Notification() noexcept {
    return [this](uint32_t id) {
        if(id == PropID_ColorMatrix)
            UserArea->UpdateCells();
    };
}


void GameGUI::ViewCells_cb(Fl_Widget* cell, void* window)
{
    ((GameGUI*)window)->ClickCmd( ((MyCell*)cell)->GetRow(), ((MyCell*)cell)->GetCol() );
}
