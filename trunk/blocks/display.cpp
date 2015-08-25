#include "display.h"
#include "sprite.h"

DisplaySingleton::DisplaySingleton(){
	disp_ = CImgDisplay(640, 640,"Blocks test");
	background_ = CImg<unsigned char>( 640, 640, 1, 3, 0 );
}

DisplaySingleton& DisplaySingleton::instance(){
	static DisplaySingleton inst;
	return inst;
}

bool DisplaySingleton::running() const{
	return !disp_.is_closed() && !disp_.is_keyESC();
}

void DisplaySingleton::present(){
	disp_.display( background_ );
}

void DisplaySingleton::clear(){
	background_.fill( 0 );
}

void DisplaySingleton::draw_image( const int& x, const int& y, CImg<unsigned char>& img ){
	background_.draw_image(x, y, img);
}

void DisplaySingleton::draw_line( const int& x1, const int& y1, const int& x2, const int& y2,
								 const unsigned char* color){
	background_.draw_line( x1, y1, x2, y2, color );
}

int DisplaySingleton::width() const {
	return background_.width();
}

int DisplaySingleton::height() const { 
	return background_.height();
}

const unsigned int DisplaySingleton::key() const{
	return disp_.key();
}

void DisplaySingleton::setTitle( const char* title ){
	disp_.set_title( title );
}

bool DisplaySingleton::LMB(){
	return disp_.button() & 1;
}

bool DisplaySingleton::RMB(){
	return disp_.button() & 2;
}

int DisplaySingleton::mouseX() const{
	return disp_.mouse_x();
}

int DisplaySingleton::mouseY() const{
	return disp_.mouse_y();
}

bool DisplaySingleton::mouseOver( const Sprite& sprite ){
	return !(disp_.mouse_x() < sprite.x() ||
		disp_.mouse_x() > sprite.x() + sprite.width() ||
		disp_.mouse_y() < sprite.y() ||
		disp_.mouse_y() > sprite.y() + sprite.height() );
}

void DisplaySingleton::hideMouse(){
	disp_.hide_mouse();
}