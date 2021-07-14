#include "GameGUI.h"
std::function< bool (uint32_t, uint32_t)> MyCell::ClickTrigger;


int MyCell::handle(int event)
{
    int ret = 1;    // this return value may be modified to suit the function "DRAG"

    switch(event)
    {
        case FL_PUSH:
            // update matrix in model
            ClickTrigger(row, col);
            // update view
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


LifeField::LifeField(int32_t x, int32_t y, int32_t ColNum, int32_t RowNum, int32_t edge):
    row_n( RowNum ),
    col_n( ColNum ),
    Matrix( RowNum, std::vector<MyCell*>(ColNum, nullptr) )
{
    for(int i=0; i<row_n; i++)
        for(int j=0; j<col_n; j++)
        {
            Matrix[i][j] = new MyCell(x+j*edge, y+i*edge, edge, edge, i, j);
        }
}


GameGUI::GameGUI():
    MainWindow( new Fl_Window(WindowWidth, WindowHeight, WindowTitle) )
{
    Fl::set_boxtype(FL_FREE_BOXTYPE, cell_draw, 0, 0, 0, 0);
    MainWindow->begin();
    UserArea = new LifeField(XField, YField, ColCellNum, RowCellNum, CellSize);
    MainWindow->end();
}


MyCell::MyCell(int x, int y, int w, int h, int row, int col): 
    Fl_Box(FL_FREE_BOXTYPE, x, y, w, h, ""),
    row( row ),
    col( col )
{ 
    color(FL_WHITE);
}

void GameGUI::set_ClickOnCell_Cmd( std::function< bool (uint32_t, uint32_t)>&& cmd ) noexcept
{
    MyCell::ClickTrigger = move(cmd);
}

