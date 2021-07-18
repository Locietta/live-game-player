#include "GameGUI.h"

GameGUI::GameGUI(uint32_t width, uint32_t height, const char *title)
: MainWindow(new Fl_Window(width, height, title)) {
    //*step1: change to call back
    //*step2: a new FL_BOX and a new call back
    Fl::set_boxtype(FL_FREE_BOXTYPE, cell_draw, 0, 0, 0, 0);
    MainWindow->begin();
    UserArea = new ViewCells(XField, YField, CellSize);
    MainWindow->end();
}

void GameGUI::set_ClickOnCell_Cmd(std::function<bool(uint32_t, uint32_t)> &&cmd) noexcept {
    UserArea->set_ClickOnCell_Cmd(move(cmd));
}

std::function<void(uint32_t)> GameGUI::Get_Notification() noexcept {
    return [this](uint32_t) {
        UserArea->UpdateCells(MainWindow);
    };
}

void GameGUI::BindColor(std::unique_ptr<TwoDMat<bool>> OutMatrix) {
    UserArea->BindColor(move(OutMatrix));
}
