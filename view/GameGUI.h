#ifndef _GAMEGUI_H_
#define _GAMEGUI_H_
#include "TwoDMat.h"
#include "ViewCells.h"
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <cstdlib>
#include <vector>

//-----------------------------------------------------------------
// GUI should include the Field and other buttons
class GameGUI {
public:
    GameGUI(uint32_t width, uint32_t height, const char *title);
    ~GameGUI() = default;
    void show() { MainWindow->show(); }
    void BindColor(std::unique_ptr<TwoDMat<bool>> OutMatrix);
    void set_ClickOnCell_Cmd(std::function<bool(uint32_t, uint32_t)> &&cmd) noexcept;
    std::function<void(uint32_t)> Get_Notification() noexcept;

private:
    ViewCells *UserArea;
    Fl_Window *MainWindow;
};

#endif // _GAMEGUI_H_
