#include "ViewCells.h"
#include <cassert>
#include <iostream>

using namespace std;

int MyCell::handle(int event) {
    int ret = 1; // this return value may be modified to suit the function "DRAG"

    switch (event) {
    case FL_PUSH:
        // update matrix in model
        do_callback(this, this->parent());
        // update view
        if (color() == FL_BLACK)
            color(FL_WHITE);
        else
            color(FL_BLACK);
        redraw();
    break;

    default: break;
    }// end of switch

    return ret;
}

//----------------------------------class MyCell-------------------------------
MyCell::MyCell(int32_t x, int32_t y, int32_t edge, uint32_t row, uint32_t col, Fl_Callback *MyCell_cb)
    : Fl_Box(FL_FREE_BOXTYPE, x, y, edge, edge, nullptr), coordinate{row, col}, x{x}, y{y}, edge{edge} {
    color(FL_WHITE);
    callback(MyCell_cb);
}

MyCell::MyCell(MyCell &&rhs) noexcept
    : Fl_Box(FL_FREE_BOXTYPE, rhs.x, rhs.y, rhs.edge, rhs.edge, nullptr), x{rhs.x}, y{rhs.y}, edge{rhs.edge} {
    coordinate[0] = rhs.coordinate[0];
    coordinate[1] = rhs.coordinate[1];
    callback(rhs.callback());
    color(rhs.color());
}
//-----------------------------------------------------------------------------

//----------------------------------class ViewCells-------------------------------
ViewCells::ViewCells(int32_t x, int32_t y, int32_t edge, Fl_Callback *ViewCell_cb)
    : Fl_Group(x, y, edge * defaultColNum, edge * defaultRowNum), x{x}, y{y}, edge{edge} {
    callback(ViewCell_cb);
    CellMatrix.resize(defaultRowNum);

    begin();
    for (int32_t i = 0; i < defaultRowNum; i++) {
        CellMatrix[i].resize(defaultColNum);
        for (int32_t j = 0; j < defaultColNum; j++) {
            CellMatrix[i][j] = new MyCell(x + j * edge, y + i * edge, edge, i, j, (Fl_Callback *) MyCell_cb);
        }
    }
    end();
}


int ViewCells::handle(int event)
{
    int ret = 1;
    int x = 0, y = 0;

    switch(event)
    {
    case FL_PUSH:
        x = (Fl::event_x()-XField)/edge;
        y = (Fl::event_y()-YField)/edge;
    break; 

    case FL_DRAG:
        cout << (Fl::event_x()-XField)/edge << ", " << (Fl::event_y()-YField)/edge << endl;
    break;

    default: break;
    }// end of switch

    return ret;
}


void ViewCells::BindColor(ref_ptr<TwoDMat<bool>> OutMatrix) {
    ColorMatrix = move(OutMatrix);
}


void ViewCells::UpdateCells() {
    const auto &row_n = ColorMatrix->m_height;
    const auto &col_n = ColorMatrix->m_width;
    if ((row_n != CellMatrix.size()) || (col_n != CellMatrix[0].size())) {
        begin();
        CellMatrix.clear();
        CellMatrix.resize(row_n);
        for (int i = 0; i < row_n; i++) {
            CellMatrix[i].resize(col_n);
            for (int j = 0; j < col_n; j++) {
                CellMatrix[i][j] = new MyCell(x + j * edge, y + i * edge, edge, i, j, (Fl_Callback *) MyCell_cb);
            }
        }
        end();
    }

    for (int i = 0; i < row_n; i++)
        for (int j = 0; j < col_n; j++) {
            if ((*ColorMatrix)[i][j] == true)
                CellMatrix[i][j]->color(FL_BLACK);
            else
                CellMatrix[i][j]->color(FL_WHITE);
            CellMatrix[i][j]->redraw();
        }
}

void ViewCells::MyCell_cb(Fl_Widget *ptr, void *ViewCellPtr) {
    ((ViewCells *) ViewCellPtr)->do_callback(ptr, ((ViewCells *) ViewCellPtr)->parent());
}

//--------------------------------------------------------------------------------

// draw a box type with white edge
void cell_draw(int x, int y, int w, int h, Fl_Color c) {
    fl_color(c);
    fl_rectf(x, y, w, h);
    fl_color(FL_WHITE);
    fl_rect(x, y, w, h);
}
