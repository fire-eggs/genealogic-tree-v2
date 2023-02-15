#pragma once

//#include <FL/Fl_Group.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Box.H>

#include "Person.h"

// TODO can this and UncleFam be generalized?
// TODO more than 3 children

class SibFam : public Fl_Box
{
private:
    Person *_husb;
    Person *_wife;
    
    Fl_Color _clr;
    
    Fl_Multiline_Output *dispHusb;
    Fl_Multiline_Output *dispWife;
    Fl_Box *dispPl;
    
    int childCount;
    Person *_childs[3];
    Person *_childSpo[3];

    int _marriageHigh; // height of husb+wife displays
    
public:
    static const int FAM_WIDTH = 140;
    
    SibFam(Person *husb, Person *wife, Fl_Color clr, int x, int y) 
        : Fl_Box(x, y, FAM_WIDTH, 325) // NOTE: first approximation
    {
        box(FL_BORDER_BOX);
        
        _clr = clr;
        _husb = husb;
        _wife = wife;
        
        int husbH = _husb->high() + 5;
        int wifeH = _wife ? _wife->high() + 5 : 0;
        
        dispHusb = new Fl_Multiline_Output(x+3, y+3, FAM_WIDTH-6, husbH);
        dispHusb->color(clr);
        _husb->setup(dispHusb);
        
        if (_wife)
        {
            dispPl  = new Fl_Box(x+5, y+56, 10, 20, "+");
            dispWife = new Fl_Multiline_Output(x+18, y+husbH+6, FAM_WIDTH-21, wifeH);
            dispWife->color(clr);
            _wife->setup(dispWife);
        }        
        //end();
        
        childCount = 0;

        // Adjust our size for the required display dimensions
        _marriageHigh = husbH + wifeH + 10;
        resize(x,y,FAM_WIDTH, _marriageHigh);
    }

    void AddChild(Person *child, Person *spouse)
    {
        // TODO heights should be calculated from Person
        
        _childs[childCount] = child;
        _childSpo[childCount] = spouse;
        
        int deltaY = _marriageHigh + childCount * 77; 
        
        Fl_Multiline_Output *dispCousin = new Fl_Multiline_Output(x()+25, y()+deltaY, FAM_WIDTH-28, 35);
        dispCousin->color(_clr);
        Fl_Box *dispPl = new Fl_Box(x()+14, y()+deltaY+35+12, 10, 20, "+");
        deltaY += 35 + 3;
        Fl_Multiline_Output *dispSpouse = new Fl_Multiline_Output(x()+25, y()+deltaY, FAM_WIDTH-28, 35);
        dispSpouse->color(_clr);
        
        childCount++;
        
        //add(dispCousin);
        //add(dispPl);
        //add(dispSpouse);
        
        child->setup(dispCousin);
        if (spouse != nullptr)
            spouse->setup(dispSpouse);
        else
            dispSpouse->clear_visible_focus(); // TODO fixme
        
        resize(x(),y(),FAM_WIDTH, _marriageHigh + childCount * 77);
    }
    
};
