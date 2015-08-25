#ifndef SPRITE_H
#define SPRITE_H


#include <string>
#include "CImg.h"

using namespace std;
using namespace cimg_library;

class Sprite{
public:
	Sprite( const string& );
	Sprite( CImg<unsigned char> );
	Sprite* clone();
	void draw();
	void move(const int&,const int&);
	bool collidesWith( const Sprite& );	
	inline int x() const;
	inline int y() const;
	inline int width() const;
	inline int height() const;
	void setVx( const float& );
	void setVy( const float& );
	void setV( const float& );
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

protected:
	string file_;
	CImg<unsigned char> image_;
	float x_, y_, vx_, vy_;
};


#endif