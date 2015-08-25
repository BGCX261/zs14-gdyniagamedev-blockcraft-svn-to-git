#ifndef DISPLAY_H
#define DISPLAY_H

#include "CImg.h"

using namespace cimg_library;

class Sprite;

class DisplaySingleton{
public:
	static DisplaySingleton& instance();
	bool running() const;
	void present();
	void clear();
	void draw_image( const int& x, const int& y, CImg<unsigned char>& img );
	void draw_line( const int& x1, const int& y1, const int& x2, const int& y2,
		const unsigned char* color );
	int width() const;
	int height() const;
	const unsigned int key() const;
	void setTitle( const char* title );
	bool LMB();
	bool RMB();
	int mouseX() const;
	int mouseY() const;
	bool mouseOver( const Sprite& );
	void hideMouse();
private:
	DisplaySingleton();
	CImgDisplay disp_;
	CImg<unsigned char> background_;
};

inline DisplaySingleton& Display(){
	return DisplaySingleton::instance();
}

#endif
