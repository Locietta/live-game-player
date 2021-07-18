#include "ViewCells.h"
#include <cassert>
std::function<bool(uint32_t, uint32_t)> MyCell::ClickTrigger;

/* std::function<void(uint32_t, uint32_t, bool)> ViewCells::get_Notification_UpdateCell() noexcept
{
    return [this](uint32_t row, uint32_t col, bool state)
    {
        Matrix[row][col]->color( (state==true)? FL_BLACK: FL_WHITE );
    };
    //return SetColor;
} */

// unused in this project
void ViewCells::set_ClickOnCell_Cmd(std::function<bool(uint32_t, uint32_t)> &&cmd) noexcept {
    MyCell::ClickTrigger = move(cmd);
}

int MyCell::handle(int event) {
    int ret = 1; // this return value may be modified to suit the function "DRAG"

    switch (event) {
    case FL_PUSH:
        // update matrix in model
        ClickTrigger(row, col);
        // update view
        if (color() == FL_BLACK)
            color(FL_WHITE);
        else
            color(FL_BLACK);
        redraw();
        break;

    default: break;
    }

    return ret;
}

// draw a box type with white edge
void cell_draw(int x, int y, int w, int h, Fl_Color c) {
    fl_color(c);
    fl_rectf(x, y, w, h);
    fl_color(FL_WHITE);
    fl_rect(x, y, w, h);
}

// ViewCells::ViewCells(int32_t x, int32_t y, int32_t ColNum, int32_t RowNum, int32_t edge)
//     : row_n(RowNum), col_n(ColNum), Matrix(RowNum, std::vector<MyCell *>(ColNum, nullptr)) {
//     for (int i = 0; i < row_n; i++)
//         for (int j = 0; j < col_n; j++) {
//             Matrix[i][j] = new MyCell(x + j * edge, y + i * edge, edge, edge, i, j);
//         }
// }

ViewCells::ViewCells(int32_t x, int32_t y, int32_t edge) : x{x}, y{y}, edge{edge} {
}

MyCell::MyCell(int x, int y, int w, int h, int row, int col)
    : Fl_Box(FL_FREE_BOXTYPE, x, y, w, h, ""), row(row), col(col), x{x}, y{y}, w{w}, h{h} {
    color(FL_WHITE);
}

MyCell::MyCell(MyCell &&rhs) noexcept
    : Fl_Box(FL_FREE_BOXTYPE, rhs.x, rhs.y, rhs.w, rhs.h, nullptr), row(rhs.row),
      col(rhs.col), x{rhs.x}, y{rhs.y}, w{rhs.w}, h{rhs.h} {}

void ViewCells::BindColor(std::unique_ptr<TwoDMat<bool>> OutMatrix) {
    ColorMatrix = move(OutMatrix);
}

void ViewCells::UpdateCells(Fl_Window *MainWindow) {
    const auto &row_n = ColorMatrix->m_height;
    const auto &col_n = ColorMatrix->m_width;
    if ((row_n != Matrix.size()) || (col_n != Matrix[0].size())) {
        MainWindow->begin();
        Matrix.clear();
        Matrix.resize(row_n);
        for (int i = 0; i < row_n; i++)
            for (int j = 0; j < col_n; j++) {
                // Matrix[i].push_back({x + j * edge, y + i * edge, edge, edge, i, j});
                Matrix[i].emplace_back(x + j * edge, y + i * edge, edge, edge, i, j);
            }
        MainWindow->end();
    }

    for (int i = 0; i < row_n; i++)
        for (int j = 0; j < col_n; j++) {
            if ((*ColorMatrix)[i][j] == true)
                Matrix[i][j].color(FL_BLACK);
            else
                Matrix[i][j].color(FL_WHITE);
            Matrix[i][j].redraw();
        }
}
