#pragma once

#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Box.H>

#include "Person.h"

// Draws a marriage. Two spouses, the second drawn below and slightly
// indented. A plus sign shown to the left of the second. If no second
// spouse is provided, a smaller, empty box is drawn.
//
class Marriage : public Fl_Box
{
private:
    Person *_sp1;
    Person *_sp2;
    
    Fl_Color _clr;
    
    Fl_Multiline_Output *dispSp1;
    Fl_Multiline_Output *dispSp2;
    Fl_Box *dispPl;

    int _realW;
    int _realH;
    
public:
    Marriage(Person *sp1, Person *sp2, Fl_Color clr, int x, int y)
        : Fl_Box(x, y, 190, 135) // NOTE: first approximation
    {
        // TODO font?
        // TODO should background color be set? can it be transparent?
        
        _clr = clr;
        _sp1 = sp1;
        _sp2 = sp2;
        
        int sp1H = _sp1->high();
        int sp1W = _sp1->wide();
        int sp2H = _sp2 ? _sp2->high() : 20;
        int sp2W = _sp2 ? _sp2->wide() : sp1W - 12;
        
        dispSp1 = new Fl_Multiline_Output(x+3, y+3, sp1W, sp1H);
        _sp1->setup(dispSp1);
        dispSp1->color(clr);
        dispSp1->clear_visible_focus();
        
        dispPl = new Fl_Box(x+5, y+sp1H+sp2H / 2, 7, 20, "+");

        dispSp2 = new Fl_Multiline_Output(x+15, y+sp1H+10, sp2W, sp2H);
        dispSp2->color(clr);
        dispSp2->clear_visible_focus();
        
        if (_sp2)
            _sp2->setup(dispSp2);

        _realW = max(20 + sp2W, sp1W+5);
        _realH = sp1H + sp2H + (_sp2 ? 17 : 11); // TODO why is a tweak required for an empty Fl_Multiline_Output?
        resize(x, y, _realW, _realH);
    }

    int realH() { return _realH; }
    int realW() { return _realW; }

    void position(int x, int y)
    {
        resize(x, y, w(), h());
        dispSp1->resize(x+3, y+3, dispSp1->w(), dispSp1->h());
        dispSp2->resize(x+18, y+_sp1->high()+10, dispSp2->w(), dispSp2->h());
        dispPl->resize(x+5, y+_sp1->high()+dispSp2->h()/2, dispPl->w(), dispPl->h());
    }

    static int max(int a, int b) { return a > b ? a : b; }

};

