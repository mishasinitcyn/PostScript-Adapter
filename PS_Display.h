#pragma once
#include <iostream>
#include "Display.h"
#include "PS_Adaptee.h"

class PS_Display: public Display {
	public:
		PS_Display(std::ostream& o);
		void start();
		void color(Color col);
		void shape(Shape s);
		void width(int w);
		void edge(double x1, double y1, double x2, double y2);
		void vertex(double x, double y);
		void end();
		~PS_Display();
		
	private:
		std::ostream& out;
		PS_adaptee* Adaptee;
		double curWidth; //Saves the current width to work with
		//Also create defaults for shape, color etc
		Color curColor;	//Current Color, BLACK by default;
		Shape curShape; //Current Shape, CIRCLE by default
};
