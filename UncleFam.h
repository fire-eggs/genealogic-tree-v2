#pragma once

#include <FL/Fl_Group.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Box.H>

#include "Person.h"

class UncleFam : public Fl_Group
{
private:
    Person *_unc;
    Person *_aun;
    
    Fl_Color _clr;
    
    Fl_Multiline_Output *dispUnc;
    Fl_Multiline_Output *dispAun;
    Fl_Box *dispPl;
    
    int cousinCount;
    Person *_cousins[3];
    Person *_cousSpo[3];

    int _famBottom; // bottom of aunt box,used to position _cousins
    
public:
    static const int FAM_WIDTH = 160; // TODO should be determined dynamically
    
    UncleFam(Person *unc, Person *aun, Fl_Color clr, int x, int y) 
        : Fl_Group(x, y, FAM_WIDTH, 325)
    {
        box(FL_BORDER_BOX);
        
        _clr = clr;
        _unc = unc;
        _aun = aun;
        
        // TODO dimensions of output need to be determined by Person [taking generation and birth/death into account]
        
        int uncH = _unc->high();
        int aunH = _aun ? _aun->high() : 0;
        dispUnc = new Fl_Multiline_Output(x+3, y+3, FAM_WIDTH-6, uncH);
        dispUnc->color(clr);
        _unc->setup(dispUnc);
        
        if (_aun)
        {
            dispPl  = new Fl_Box(x+5, y+5+uncH+aunH/2, 10, 20, "+");
            
            //dispAun = new Fl_Multiline_Output(x+18, y+46, FAM_WIDTH-21, 40);
            dispAun = new Fl_Multiline_Output(x+18, y+uncH+10, FAM_WIDTH-21, aunH);
            dispAun->color(clr);
            _aun->setup(dispAun);
        }
        
        _famBottom = y+uncH+10+aunH;
                
        end();

        //int realH = dispUnc->h() + dispAun->h() + 6;
        //size(w(), realH);
        
        cousinCount = 0;
    }

    void AddCousin(Person *cous, Person *spouse)
    {
        // TODO heights should be calculated from Person
        
        _cousins[cousinCount] = cous;
        _cousSpo[cousinCount] = spouse;

        
        // marriage-height + 77 per cousin -> needs to be dynamic
        //int deltaY = 90 + cousinCount * 77;
        int deltaY = _famBottom + 5;
        
        //Fl_Multiline_Output *dispCousin = new Fl_Multiline_Output(x()+25, y()+deltaY, FAM_WIDTH-28, 35);
        Fl_Multiline_Output *dispCousin = new Fl_Multiline_Output(x()+25, deltaY, FAM_WIDTH-28, cous->high());
        dispCousin->color(_clr);
        
        
        Fl_Box *dispPl = new Fl_Box(x()+19, deltaY+cous->high()+12, 10, 20, "+");
        //deltaY += 35 + 3;
        deltaY += cous->high() + 6;
        
        // TODO if no spouse, should spouse box just not be displayed?
        int spH = 30;
        if (spouse)
            spH = spouse->high();
        //Fl_Multiline_Output *dispSpouse = new Fl_Multiline_Output(x()+25, y()+deltaY, FAM_WIDTH-28, 35);
        Fl_Multiline_Output *dispSpouse = new Fl_Multiline_Output(x()+30, deltaY, FAM_WIDTH-33, spH);
        dispSpouse->color(_clr);

        // TODO need to update _auntBottom and rename it
        _famBottom += cous->high() + spH + 8;
        
        cousinCount++;
        
        add(dispCousin);
        add(dispPl);
        add(dispSpouse);
        
        cous->setup(dispCousin);
        if (spouse != nullptr)
            spouse->setup(dispSpouse);
        else
            dispSpouse->clear_visible_focus(); // TODO need static method in Person to do config stuff
    }
    
};
