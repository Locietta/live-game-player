#ifndef _VIEW_CELL_H_
#define _VIEW_CELL_H_
#include <FL\Fl.H>
#include <FL\Fl_Window.H>
#include <FL\Fl_Box.H>
#include <FL\fl_draw.H>
#include <functional>
#include <vector>

//--------------------location and size of field----------------
const int32_t XField = 0;
const int32_t YField = 0;
const int32_t RowCellNum = 30;
const int32_t ColCellNum = 30;
const int32_t CellSize = 15;


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
    static std::function< bool (uint32_t, uint32_t)> ClickTrigger;
    friend class ViewCells;
};


//-------------------------------------------------
// the Field is a matrix of Cells
class ViewCells
{
public:
    ViewCells(int32_t x, int32_t y, int32_t ColNum, int32_t RowNum, int32_t edge);
    ~ViewCells() = default;

    void set_ClickOnCell_Cmd( std::function< bool (uint32_t, uint32_t)>&& cmd) noexcept;

    // viewmodel notifies view to redraw
    //std::function<void(uint32_t)> get_Notification() noexcept;  
    std::function<void(uint32_t, uint32_t, bool)> get_Notification_UpdateCell() noexcept;

private:
    std::vector< std::vector<MyCell*> > Matrix;
    int32_t row_n;
    int32_t col_n;
};

//------------------------------------------------------------------
// a drawing function that defines the type of Cell
void cell_draw(int x, int y, int w, int h, Fl_Color c);





#endif