#include "PS_Display.h"
#include "PS_adaptee.cpp"
using namespace std;


PS_Display::PS_Display(ostream& o) : out(o) {
	cout <<"%!PS-Adobe-2.0" <<endl << "%constructor" << endl;

	this->Adaptee = new PS_adaptee(o); 
	this->curWidth = 1;
	this->curColor = BLACK;
	this->curShape = CIRCLE;
}


void PS_Display::start() {
	cout <<"%start" <<endl;

	Adaptee->setrgbcolor(0.8, 0.8, 0.8);
	Adaptee->newpath();
	Adaptee->moveto(0, 0);
	Adaptee->rlineto(0, 10); Adaptee->rlineto(10, 0); 
	Adaptee->rlineto(0, -10); Adaptee->rlineto(-10, 0);
	Adaptee->fill();
	Adaptee->closepath();
}


void PS_Display::color(Color col) {
	cout <<"%color" <<endl;
	switch(col){
		case 0: //Red
			Adaptee->setrgbcolor(1, 0, 0);
			break;
		case 1: //Green
			Adaptee->setrgbcolor(0, 1, 0);
			break;
		case 2: // Blue
			Adaptee->setrgbcolor(0, 0, 1);
			break;
		case 3: //Cyan
			Adaptee->setrgbcolor(0, 1, 1);
			break;
		case 4: // Magenta
			Adaptee->setrgbcolor(1, 0, 1);
			break;
		case 5: //Yellow
			Adaptee->setrgbcolor(1, 1, 0);
			break;
		case 6: //White
			Adaptee->setrgbcolor(1, 1, 1);
			break;
		case 7:	//Black
			Adaptee->setrgbcolor(0, 0, 0);
			break;
	}
	this->curColor = col;
}


void PS_Display::shape(Shape s) {
	cout <<"%shape set as " << s << endl;
	this->curShape = s;
}


void PS_Display::width(int w) {
	this->curWidth = w*.03;
	Adaptee->setlinewidth(curWidth);
}


void PS_Display::edge(double x1, double y1, double x2, double y2) {	
	cout<<"%edge"<<endl;

	//Multiply input by 10, for scaling conversion
	x1 = x1*10; y1 = y1*10; x2 = x2*10; y2 = y2*10;
	
	//Draw Edge
	Adaptee->newpath();
	Adaptee->moveto(x1, y1);
	Adaptee->lineto(x2, y2);

	this->color(this->curColor);
	Adaptee->stroke();
	Adaptee->closepath();
}


void PS_Display::vertex(double x, double y) { 
	cout<<"%vertex"<<endl;
	double w = curWidth; //w value for readability

	//Multiply input by 10, for scaling conversion
	x = x*10;	y = y*10;

	switch(curShape){
		case 0: //Circle
			cout <<"%printing circle " << endl;
			Adaptee->arc(x, y, 2*w, 0, 360);
			break;

		case 1: //Triangle
			cout <<"%printing triangle " << endl;
			Adaptee->newpath();
			Adaptee->moveto(x,y);

			Adaptee->rlineto(0, 2*w); 
			Adaptee->rlineto(2*w, -4*w); 
			Adaptee->rlineto(-4*w, 0); 
			Adaptee->rlineto(2*w, 4*w); 
			break;

		case 2: //Square
			cout <<"%printing square " << endl;
			Adaptee->newpath();
			Adaptee->moveto(x,y);

			Adaptee->moveto(x-2*w, y-2*w);
			Adaptee->rlineto(0, 4*w); 
			Adaptee->rlineto(4*w, 0);
			Adaptee->rlineto(0, -4*w);
			Adaptee->rlineto(-4*w, 0);
			break;
	}
	Adaptee->closepath();
	Adaptee->fill();
}

//Calls the PostScripts showpage 
void PS_Display::end() {
	cout<<"%end"<<endl;
	cout<<"showpage"<<endl;
}

PS_Display::~PS_Display(){
	delete Adaptee;
	Adaptee = NULL;
	this->curWidth = 0;
	this->curColor = BLACK;
}