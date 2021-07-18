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
class GameGUI : public Fl_Window{
public:
    GameGUI(uint32_t width, uint32_t height, const char *title);
    ~GameGUI() = default;

    // bind widget attribute
    ViewCells *Get_ViewCells();

    // set command
    void Set_ClickOnCell_Cmd(std::function<bool(uint32_t, uint32_t)> &&cmd) noexcept;

    // get notification
    std::function<void(uint32_t)> Get_Notification() noexcept;

private:
    // click command
    std::function<bool(uint32_t, uint32_t)> ClickCmd;

    // data
    ViewCells *UserArea;
    static void ViewCells_cb(Fl_Widget*, void*);
};



#endif // _GAMEGUI_H_
