#pragma once

#include "Person.h"
#include "Marriage.h"

class GrandFam : public Marriage
{
public:
    GrandFam(Person *gpa, Person *gma, Fl_Color clr, int x, int y)
        : Marriage(gpa, gma, clr, x, y)
        {
            box(FL_BORDER_BOX);
        }
};
