#ifndef _VIEWCELLS_H_
#define _VIEWCELLS_H_
#include "Defs.h"
#include "TwoDMat.h"
#include <FL\Fl.H>
#include <FL\Fl_Box.H>
#include <FL\Fl_Window.H>
#include <FL\fl_draw.H>
#include <functional>
#include <memory>
#include <vector>


//--------------------location and size of field----------------
inline const int32_t XField = 0;
inline const int32_t YField = 0;
inline const int32_t CellSize = 15;

//-------------------------------------------------
// MyCell means a little square (white or black)
class MyCell : public Fl_Box
{
public:
    MyCell(uint32_t x, uint32_t y, uint32_t edge, uint32_t row, uint32_t col, Fl_Callback* MyCell_cb );
    MyCell(MyCell&& rhs);
    ~MyCell() override = default;
    int handle(int event) override;
    uint32_t GetRow(){ return coordinate[0]; }
    uint32_t GetCol(){ return coordinate[1]; }
private:
    uint32_t coordinate[2]; // (row, col)
    uint32_t x, y, edge;

};

//-------------------------------------------------
// the Field is a matrix of Cells
class ViewCells : public Fl_Group{
public:
    ViewCells(uint32_t x, uint32_t y, uint32_t edge, Fl_Callback* ViewCell_cb );
    ~ViewCells() = default;

    void BindColor(std::unique_ptr<TwoDMat<bool>> OutMatrix);
    void UpdateCells();

private:
    // data
    std::unique_ptr<TwoDMat<bool>> ColorMatrix;
    uint32_t x, y, edge;

    // sub-widgets
    std::vector<std::vector<MyCell*>> CellMatrix;
    static void MyCell_cb(Fl_Widget* ptr, void* ViewCellPtr);
};

//------------------------------------------------------------------
// a drawing function that defines the type of Cell
void cell_draw(int x, int y, int w, int h, Fl_Color c);



#endif // _VIEWCELLS_H_
