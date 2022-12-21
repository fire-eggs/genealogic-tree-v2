#pragma once

//#include <FL/Fl_Group.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Box.H>

#include "Person.h"

class GrandFam : public Fl_Box
{
private:
    Person *_gPa;
    Person *_gMa;
    
    Fl_Color _clr;
    
    Fl_Multiline_Output *dispGPa;
    Fl_Multiline_Output *dispGMa;
    Fl_Box *dispPl;
    int _realH; // The "real" height of the family [takes font size, data into account]
    
public:
    static const int FAM_WIDTH = 190;
    static const int FAM_HIGH  = 135;
        
    int realH() { return _realH; }
    
    GrandFam(Person *gpa, Person *gma, Fl_Color clr, int x, int y) 
        : Fl_Box(x, y, FAM_WIDTH, FAM_HIGH) // NOTE: first approximation
    {
        box(FL_BORDER_BOX);
        
        _clr = clr;
        _gPa = gpa;
        _gMa = gma;
        
        int gpaH = _gPa->isDead() ? 58 : 40;  // TODO calculate by Person
        
        dispGPa = new Fl_Multiline_Output(x+3, y+3, FAM_WIDTH-6, gpaH);
        dispGPa->color(clr);
        dispPl  = new Fl_Box(x+5, y+gpaH + gpaH/2, 10, 20, "+");
        dispGMa = new Fl_Multiline_Output(x+18, y+gpaH+6, FAM_WIDTH-21, gpaH);
        dispGMa->color(clr);
        
        _gPa->setup(dispGPa); // TODO have setup return actual height
        _gMa->setup(dispGMa);

        _realH = gpaH * 2 + 10; // NOTE this assumes both are dead
        
        resize(x, y, FAM_WIDTH, _realH);  
    }
    
};
