#ifndef _GAMEGUI_H_
#define _GAMEGUI_H_
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <cstdlib>
#include <vector>
#include "view.h"

//--------------------size of main window-----------------------
static const int32_t WindowWidth = 500;
static const int32_t WindowHeight = 500;
static const char* WindowTitle = "Conway Life Game";

//--------------------location and size of field----------------
static const int32_t XField = 0;
static const int32_t YField = 0;
static const int32_t RowCellNum = 30;
static const int32_t ColCellNum = 30;
static const int32_t CellSize = 15;



//-------------------------------------------------
// MyCell means a little square (white or black)
class MyCell: public Fl_Box
{
public:
    MyCell(int x, int y, int w, int h, int row, int col);
    ~MyCell() override = default;
    int handle(int event) override;
    static std::function< bool (uint32_t, uint32_t)> ClickTrigger;
private:
    int32_t row;
    int32_t col;
};


//-------------------------------------------------
// the Field is a matrix of Cells
class LifeField
{
public:
    LifeField(int32_t x, int32_t y, int32_t ColNum, int32_t RowNum, int32_t edge);
    ~LifeField() = default;

private:
    std::vector< std::vector<MyCell*> > Matrix;
    int32_t row_n;
    int32_t col_n;
};


//-----------------------------------------------------------------
// GUI should include the Field and other buttons
class GameGUI: public View
{
public:
    GameGUI();
    ~GameGUI() = default;
    void show(){ MainWindow->show(); }
    uint32_t GetMatrixSize(){ return ColCellNum; } // return the size of matrix ( number of cells )
    void set_ClickOnCell_Cmd( std::function< bool (uint32_t, uint32_t)>&& cmd) noexcept;

private:
    LifeField* UserArea;
    Fl_Window* MainWindow;
};

//------------------------------------------------------------------
// a drawing function that defines the type of Cell
void cell_draw(int x, int y, int w, int h, Fl_Color c);

#endif
