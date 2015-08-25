#include "sprite.h"
#include "display.h"
#include <iostream>

Sprite::Sprite( const string& s ):
file_( s ),
image_( file_.c_str() ),
x_( .0f ),
y_( .0f ),
vx_( 5.0f ),
vy_( 5.0f ){}

Sprite::Sprite( CImg<unsigned char> img ):
image_( img ),
x_( .0f ),
y_( .0f ),
vx_( 5.0f ),
vy_( 5.0f ){}

Sprite* Sprite::clone(){
	return new Sprite(file_);
}

void Sprite::draw(){
	Display().draw_image( (int)x_, (int)y_, image_ );
}

void Sprite::move(const int& x,const int& y){
	x_ = (float)x;
	y_ = (float)y;
}

bool Sprite::collidesWith( const Sprite& rhs){
	if ( this == &rhs ){
		return false;
	}

	return !( x() + width() < rhs.x() ||
		x() > rhs.x() + rhs.width() ||
		y() + height() < rhs.y() ||
		y() > rhs.y() + rhs.height() );

}

int Sprite::x() const{
	return (int)x_;
}
	
int Sprite::y() const{
	return (int)y_;
}

int Sprite::width() const{
	return image_.width();
}

int Sprite::height() const{
	return image_.height();
}

void Sprite::setVx( const float& vx ){
	vx_ = vx;
}

void Sprite::setVy( const float& vy ){
	vy_ = vy;
}

void Sprite::setV( const float& v ){
	vx_ = vy_ = v;
}

void Sprite::moveLeft(){
	x_ -= vx_;
}

void Sprite::moveRight(){
	x_ += vx_;
}

void Sprite::moveUp(){
	y_ -= vy_;
}

void Sprite::moveDown(){
	y_ += vy_;
}