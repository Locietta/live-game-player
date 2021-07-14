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




class MyCell: public Fl_Box
{
public:
    MyCell(int x, int y, int w, int h): Fl_Box(FL_FREE_BOXTYPE, x, y, w, h, "") { color(FL_WHITE); }
    ~MyCell() override = default;
    int handle(int event) override;
};



class LifeField
{
public:
    LifeField(int32_t x, int32_t y, int32_t size, int32_t edge);
    ~LifeField() = default;

private:
    std::vector< std::vector<MyCell*> > Matrix;
    int32_t size;
};



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


void cell_draw(int x, int y, int w, int h, Fl_Color c);

#endif
