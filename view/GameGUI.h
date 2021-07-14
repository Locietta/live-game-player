#ifndef _GAMEGUI_H_
#define _GAMEGUI_H_
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <cstdlib>
#include <vector>

//--------------------size of main window-----------------------
static const int32_t WindowWidth = 500;
static const int32_t WindowHeight = 500;
static const char* WindowTitle = "Conway's Life Game";

//--------------------location and size of field----------------
static const int32_t XField = 0;
static const int32_t YField = 0;
static const int32_t CellNum = 30;
static const int32_t CellSize = 15;



//-------------------------------------------------
// MyCell means a little square (white or black)
class MyCell: public Fl_Box
{
public:
    MyCell(int x, int y, int w, int h, int row, int col);
    ~MyCell() override = default;
    int handle(int event) override;
private:
    int32_t row;
    int32_t col;
};


//-------------------------------------------------
// the Field is a matrix of Cells
class LifeField
{
public:
    LifeField(int32_t x, int32_t y, int32_t size, int32_t edge);
    ~LifeField() = default;

private:
    std::vector< std::vector<MyCell*> > Matrix;
    int32_t size;
};


//-----------------------------------------------------------------
// GUI should include the Field and other buttons
class GameGUI
{
public:
    GameGUI();
    ~GameGUI() = default;
    void show(){ MainWindow->show(); }

private:
    LifeField* UserArea;
    Fl_Window* MainWindow;
};

//------------------------------------------------------------------
// a drawing function that defines the type of Cell
void cell_draw(int x, int y, int w, int h, Fl_Color c);

#endif
