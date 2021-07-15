#ifndef _GAMEGUI_H_
#define _GAMEGUI_H_
#include <FL\Fl.H>
#include <FL\Fl_Window.H>
#include <FL\Fl_Box.H>
#include <FL\fl_draw.H>
#include <cstdlib>
#include <vector>
#include "ViewCells.h"

//--------------------size of main window-----------------------
static const int32_t WindowWidth = 500;
static const int32_t WindowHeight = 500;
static const char* WindowTitle = "Conway Life Game";


//-----------------------------------------------------------------
// GUI should include the Field and other buttons
class GameGUI
{
public:
    GameGUI();
    ~GameGUI() = default;
    void show(){ MainWindow->show(); }
    uint32_t GetMatrixSize(){ int ret = ColCellNum; return ret; } // return the size of matrix ( number of cells )
    void set_ClickOnCell_Cmd( std::function< bool (uint32_t, uint32_t)>&& cmd) noexcept;
    std::function<void(uint32_t, uint32_t, bool)> get_Notification_UpdateCell() noexcept;

private:
    ViewCells* UserArea;
    Fl_Window* MainWindow;
};


#endif
