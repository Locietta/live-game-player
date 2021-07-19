#include "ViewCells.h"
#include <cassert>
#include <iostream>

using namespace std;

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

int ViewCells::handle(int event) {
    int ret = 1;
    int x = 0, y = 0;
    static int prev_x = -1, prev_y = -1;

    switch (event) {
    case FL_PUSH:
        prev_x = x = (Fl::event_x() - XField) / edge;
        prev_y = y = (Fl::event_y() - YField) / edge;
        CellMatrix[y][x]->do_callback(CellMatrix[y][x], this);

        if (CellMatrix[y][x]->color() == (*ColorMapping).back())
            CellMatrix[y][x]->color((*ColorMapping).front());
        else {
            CellMatrix[y][x]->color((*ColorMapping).back());
        }
        CellMatrix[y][x]->redraw();
        break;

    case FL_DRAG:
        x = (Fl::event_x() - XField) / edge;
        y = (Fl::event_y() - YField) / edge;
        if (x < 0 || x >= CellMatrix[0].size() || y < 0 || y >= CellMatrix.size()) break; // offset check
        if (x != prev_x || y != prev_y) {
            prev_x = x;
            prev_y = y;
            CellMatrix[y][x]->do_callback(CellMatrix[y][x], this);
            
            if (CellMatrix[y][x]->color() == ColorMapping->back())
                CellMatrix[y][x]->color(ColorMapping->front());
            else {
                CellMatrix[y][x]->color(ColorMapping->back());
            };
            CellMatrix[y][x]->redraw();
        }
        break;

    default: break;
    } // end of switch

    return ret;
}

void ViewCells::BindColor(ref_ptr<TwoDMat<uint32_t>> OutMatrix) {
    ColorMatrix = move(OutMatrix);
}

void ViewCells::BindColorMapping(ref_ptr<std::vector<Fl_Color>> mapping) {
    ColorMapping = move(mapping);
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
            CellMatrix[i][j]->color((*ColorMapping)[(*ColorMatrix)[i][j]]);
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
}
