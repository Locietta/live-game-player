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
class MyCell : public Fl_Box {
public:
    MyCell(int x, int y, int w, int h, int row, int col);
    // MyCell(const MyCell&) = default;
    MyCell(MyCell&& rhs);
    ~MyCell() override = default;
    int handle(int event) override;

private:
    int32_t row;
    int32_t col;
    int32_t x, y, w, h;
    static std::function<bool(uint32_t, uint32_t)> ClickTrigger;
    friend class ViewCells;
};

//-------------------------------------------------
// the Field is a matrix of Cells
class ViewCells {
public:
    ViewCells(int32_t x, int32_t y, int32_t edge);
    ~ViewCells() = default;

    void set_ClickOnCell_Cmd(std::function<bool(uint32_t, uint32_t)> &&cmd) noexcept;

    void BindColor(std::unique_ptr<TwoDMat<bool>> OutMatrix);
    std::function<void(uint32_t)> Get_Notification() noexcept;

private:
    std::vector<std::vector<MyCell>> Matrix;
    std::unique_ptr<TwoDMat<bool>> ColorMatrix;
    int32_t x, y, edge;
    void UpdateCells();
};

//------------------------------------------------------------------
// a drawing function that defines the type of Cell
void cell_draw(int x, int y, int w, int h, Fl_Color c);

#endif // _VIEWCELLS_H_
