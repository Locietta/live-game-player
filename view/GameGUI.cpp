#include "GameGUI.h"

GameGUI::GameGUI() : MainWindow(new Fl_Window(WindowWidth, WindowHeight, WindowTitle)) {
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
