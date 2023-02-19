#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Button.H>

#include "NoChildFam.h"
#include "ChildFam.h"

class GenWin : public Fl_Box
{
public:
	GenWin(int x, int y, int w, int h) : Fl_Box(x, y, w, h)
	{
        box(FL_FLAT_BOX);
        color(FL_DARK_YELLOW);
	}
};

int main() 
{
    
    Fl_Double_Window window(1100, 600, "Drzewo genealogiczne");
    window.color(FL_GRAY);

    // Maternal grandparents
    Person gpa("Clarence Bauer","26.09.1926","28.12.1997",0);
    Person gma("Loretta Bauer", "15.05.1901","13.06.1953",0);
    
    // Maternal sibling + spouse - #1
    Person unc1("Carmie Bare","22.09.1903","23.08.1996",1);
    Person aun1("Ima Bare","04.04.1926","??.01.1993",1);
    
    // Maternal cousins
    Person cous1_1("Sam Bare","14.09.1904","??.01.1986",2);
    Person cous1_2("Brucie Bare","??.??.1907","?",2);
    Person spCous1_2("Dicey Lyall","?","",2);
    Person cous1_3("Hillery Bare","11.03.1913","31.12.1996",2);

    // Maternal sibling - #2
    Person unc2("Reed Bare","15.02.1903","23.04.1973",1);
    
    // Paternal sibling
    Person uncP1("Joseph Hardesty","19.06.1890","10.12.1962",1);
    Person aunP1("Mary Nalley","12.06.1892","25.10.1918",1);
    
    // Paternal cousins
    Person cousP1_1("William Hardesty","29.07.1853","25.03.1899",2);
    Person cousP1_2("Nancy Hagan","03.03.1861","12.06.1947",2);
    Person spCousP1_2("Eric Hagan","19.08.1859","10.11.1940",2);

    // "You"
    Person you("Pauline Sirosky","27.11.1933","27.07.1990",2);
    // "Spouse"
    Person youSp("Ruby Lawson","?","",2);
    
    // Sibling
    Person sib1("Karen Harlan","16.07.1952","18.07.1952",2);
    Person sib1sp("Luther Harlan","04.11.1911","04.02.1984",2);
    Person sib2("John Lawson","?","",2);
    
    Person sib1_c1("Random Harlan","?","",3);

    // Parents
    Person dad("Daddy", "1.1.1950", "1.1.2000", 1);
    Person mom("Mommy", "1.1.1950", "", 1);
    
    // Paternal grandparents
    Person gpa2(gpa);
    Person gma2(gma);
    
    // ******************* Display widgets.

    int H = window.h();
    int W = window.w();
    
    GenWin gw(2, 2, W - 4, H - 4);
    
    NoChildFam gfam1(&gpa, &gma, FL_YELLOW, 5, 5);
    NoChildFam gfam2(&gpa, &gma, FL_YELLOW, W - 5, 5);
    gfam2.position(W - gfam2.realW() - 5, 5);
    
    int gen1Y = 10 + gfam1.realH();
    int famX = 5;
    
    // Maternal-sibling family 1.
    ChildFam ufam1(&unc1, &aun1, FL_CYAN, famX, gen1Y);
    famX += ufam1.realW() + 5;
    
    ufam1.AddChild(&cous1_1, nullptr);
    ufam1.AddChild(&cous1_2, &spCous1_2);
    ufam1.AddChild(&cous1_3, nullptr);
    
    // Maternal-sibling family display 2.
    ChildFam ufam2(&unc2, nullptr, FL_MAGENTA, famX , gen1Y);
    famX += ufam2.realW() + 5;

    // a sibling of yours   
    int gen2Y = gen1Y + 50; 
    ChildFam sFam1(&sib1, &sib1sp, FL_GREEN, famX, gen2Y);
    sFam1.AddChild(&sib1_c1, nullptr);

    // you
    famX += sFam1.realW() + 5;
    ChildFam sFam2(&you, &youSp, FL_RED, famX, gen2Y);
    int youX = famX;
    
    // Another sibling of yours
    famX += sFam2.realW() + 5;
    ChildFam sFam3(&sib1, nullptr, FL_MAGENTA, famX, gen2Y);

    // Your parents
    int parX = youX + sFam2.realW() / 2 - 100; //GrandFam::FAM_WIDTH / 2;
    int parY = gen2Y - 50; // - GrandFam::FAM_HIGH;
    NoChildFam parents(&dad, &mom, FL_GREEN, parX, parY);
    parents.position(youX + sFam2.realW() / 2 - parents.realW() / 2, gen2Y - parents.realH() - 10);

    // Paternal siblings' X position determined by your and your siblings' sizes
    
    // Paternal-sibling family 1.
    int famX2 = famX + sFam3.realW() + 5;

    ChildFam ufamd1(&uncP1, &aunP1, FL_MAGENTA, famX2, gen1Y);
    ufamd1.AddChild(&cousP1_1, nullptr);
    ufamd1.AddChild(&cousP1_2, &spCousP1_2);
    famX2 += ufamd1.realW() + 5;
    
    // Paternal-sibling family 2.
    ChildFam ufamd2(&unc1, &aun1, FL_WHITE, famX2, gen1Y);
    ufamd2.AddChild(&cous1_1, &spCous1_2);

    // TODO Scrollable
    // TODO resizable while not moving GenWin
    
    Fl_Box b(W, H, 1, 1);
    window.resizable(b);

    window.end();
	window.show();
	return Fl::run();
}
