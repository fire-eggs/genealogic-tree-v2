#pragma once
#include <string>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Multiline_Output.H>

class Person
{
public:
    std::string _name;
    std::string _dob;
    std::string _dod;
    int _gen;
        
    Person(std::string name, std::string dob, std::string dod, int gen)
    {
        _name = name;
        _dob = dob;
        _dod = dod;
        _gen = gen;
    }

    Person(Person *orig)
    {
        _name = orig->_name;
        _dob  = orig->_dob;
        _dod  = orig->_dod;
        _gen  = orig->_gen;
    }
    
    void fulltext( std::string& val)
    {
        val = _name + "\n ur. " + _dob;
        if (isDead())
        {
            val += "\n zm. " + _dod;
        }
    }
    
    bool isDead() { return _dod.length() != 0; }
    
    void setup(Fl_Multiline_Output *disp)
    {
        std::string text;
        fulltext(text);
        disp->value(text.c_str());
        disp->textsize( textsize() );
        disp->textfont(FL_HELVETICA);
        disp->readonly(true);
        disp->clear_visible_focus(); // hide the caret/cursor
        
        // Set the widget height to the actual text height [magic +5 appears required]
        disp->size(disp->w(), high() + 5);
    }
    
    // The text size (points) to use for this person's display
    int textsize() { return _gen < 2 ? 15 : 12; }
    
    int high() 
    {
        int tw2 = 0;
        int th2 = 0;
        Fl_Label test;
        memset(&test, 0, sizeof(Fl_Label)); // make sure all fields cleared
        std::string text;
        fulltext(text);
        test.value = text.c_str();
        test.font = FL_HELVETICA;
        test.size = textsize(); 
        test.measure(tw2, th2);
        return th2;
    }
    
    int wide()
    {
        int tw2 = 0;
        int th2 = 0;
        Fl_Label test;
        memset(&test, 0, sizeof(Fl_Label)); // make sure all fields cleared
        std::string text;
        fulltext(text);
        test.value = text.c_str();
        test.font = FL_HELVETICA;
        test.size = textsize(); 
        test.measure(tw2, th2);
        return tw2 + 6; // TODO why is a tweak necessary? or in wrong place?
    }
    
};
