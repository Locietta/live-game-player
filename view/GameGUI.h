#ifndef _GAMEGUI_H_
#define _GAMEGUI_H_
#include "TwoDMat.h"
#include "ViewCells.h"
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Button.H>
#include <Fl/Fl_PNG_Image.H>
#include <FL/Fl_Float_Input.H>
#include <cstdlib>
#include <iostream>
#include <vector>

//-----------------------------------------------------------------
// GUI should include the Field and other buttons
class GameGUI : public Fl_Double_Window{
public:
    GameGUI(int32_t width, int32_t height, const char *title);
    ~GameGUI() override = default;

    // bind widget attribute
    ViewCells *Get_ViewCells();

    // set command
    void Set_ClickOnCell_Cmd(std::function<bool(uint32_t, uint32_t)> &&cmd) noexcept;
    void Set_Random_Cmd(std::function<bool()> &&cmd) noexcept;
    void Set_Clear_Cmd(std::function<bool()> &&cmd) noexcept;
    void Set_SingleStep_Cmd(std::function<bool()> &&cmd) noexcept;

    // get notification
    std::function<void(uint32_t)> Get_Notification() noexcept;

private:
    // continue state
    bool isIdle = true;
    static void Timer(void*);
    double period = 0.5;  // seconds

    // click command
    std::function<bool(uint32_t, uint32_t)> ClickCmd;
    std::function<bool()> RandomCmd;
    std::function<bool()> ClearCmd;
    std::function<bool()> SingleStepCmd;


    // sub-widget
    ViewCells *UserArea;
    Fl_Button *RandomGenerate;
    Fl_Button *Clear;
    Fl_Button *SingleStep;
    Fl_Button *Continue;
    Fl_Button *Pause;
    Fl_PNG_Image *Picture;
    Fl_Box *Picbox;
    Fl_Float_Input *Periodinput;
    Fl_Button *Confirm;

    // call back function
    static void ViewCells_cb(Fl_Widget*, void*);
    static void StartTimer_cb(Fl_Widget*, void*);
    static void PauseTimer_cb(Fl_Widget*, void*);
    static void Buttons_cb(Fl_Widget*, void*);
    static void Confirm_cb(Fl_Widget*, void*);
};


static const int32_t xButton = 40;
static const int32_t wButton = 120;
static const int32_t hButton = 50;

static const int32_t yButtonRG = 20;
static const int32_t yButtonClear = 90;
static const int32_t yButtonSS = 160;
static const int32_t yButtonConti = 230;
static const int32_t yButtonPa = 300;
static const int32_t yPeriodInput = 370;
static const int32_t yConfirm = 440;


#endif // _GAMEGUI_H_
