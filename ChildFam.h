#pragma once

#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Box.H>

#include "Person.h"
#include "Marriage.h"

// TODO more than 3 children

class ChildFam : public Fl_Box
{
private:    
    Fl_Color _clr;
    
    int childCount;

    Marriage *_parents;
    Marriage *children[3];
    
    int _realW;
    int _realH;
       
public:
    ChildFam (Person *husb, Person *wife, Fl_Color clr, int x, int y) 
        : Fl_Box(x, y, 140, 325) // NOTE: first approximation
    {
        box(FL_BORDER_BOX);
        
        _clr = clr;

        _parents = new Marriage(husb, wife, clr, x+3, y+3);

        childCount = 0;

        _realW = _parents->realW()+4;
        _realH = _parents->realH()+6;
        // Adjust our size for the required display dimensions
        resize(x,y, _realW, _realH);
    }

    void AddChild(Person *child, Person *spouse)
    {
        int marriageHigh = _parents->realH();

        int deltaY = marriageHigh + 2;
        for (int i=0; i < childCount; i++)
            deltaY += children[i]->realH();
        
        Marriage *childM = new Marriage(child, spouse, _clr, x()+24, y()+deltaY);
        children[childCount] = childM;

        _realW = Marriage::max(_realW, children[childCount]->realW()+25);
        _realH = deltaY + children[childCount]->realH() + 4;
        
        resize(x(),y(),_realW, _realH);
        
        childCount++;
    }

    int realW() { return _realW; }
    int realH() { return _realH; }
};
