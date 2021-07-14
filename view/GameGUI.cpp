#include "GameGUI.h"

int MyCell::handle(int event)
{
    //int ret = Fl_Box::handle(event);
    int ret = 1;    // return non zero to receive drag

    switch(event)
    {
        case FL_PUSH:
            if(color() == FL_BLACK) color(FL_WHITE);
            else    color(FL_BLACK);
            redraw(); 
        break;

        default:
        break;
    }

    return ret;
}


// draw a box type with white edge
void cell_draw(int x, int y, int w, int h, Fl_Color c)
{
    fl_color(c);
    fl_rectf(x, y, w, h);
    fl_color(FL_WHITE);
    fl_rect(x, y, w, h);
}


LifeField::LifeField(int32_t x, int32_t y, int32_t size, int32_t edge):
    size( size ),
    Matrix( size, std::vector<MyCell*>(size, nullptr) )
{
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
        {
            Matrix[i][j] = new MyCell(x+j*edge, y+i*edge, edge, edge);
        }
}

GameGUI::GameGUI():
    MainWindow( new Fl_Window(WindowWidth, WindowHeight, WindowTitle) )
{
    Fl::set_boxtype(FL_FREE_BOXTYPE, cell_draw, 0, 0, 0, 0);
    MainWindow->begin();
    UserArea = new LifeField(XField, YField, CellSize, CellNum);
    MainWindow->end();
}
