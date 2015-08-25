#include "CImg.h"
#include <iostream>
#include "blocks\sprite.h"
#include "blocks\display.h"

using namespace cimg_library;
using namespace std;

void main(){

	try{

		Display().setTitle( "Collisions test" );
		Display().hideMouse();

		Sprite player( "data/smiley.bmp" );
		player.move( 200, 100 );
		player.setV( 2.0f );
		Sprite wall( "data/wall.bmp" );
		wall.move( 100, 100 );

		while ( Display().running() ){

			Display().clear();		

			switch (Display().key()) {
			  case cimg::keyARROWDOWN:
				player.moveDown();
				if ( player.collidesWith( wall ) ){
					player.moveUp();
				}
				break;
			  case cimg::keyARROWUP:
				player.moveUp();
				if ( player.collidesWith( wall ) ){
					player.moveDown();
				}
				break;
			  case cimg::keyARROWLEFT:
				player.moveLeft();
				if ( player.collidesWith( wall ) ){
					player.moveRight();
				}
				break;
			  case cimg::keyARROWRIGHT:
				player.moveRight();
				if ( player.collidesWith( wall ) ){
					player.moveLeft();
				}
				break;
			}

			wall.draw();
			player.draw();

			Display().present();
		}
	} catch ( const CImgIOException& e ){
		cout << e.what() << endl;
	}  
}
