#include "CImg.h"
#include <iostream>
#include "blocks\sprite.h"
#include "blocks\display.h"

using namespace cimg_library;
using namespace std;

void main(){

	try{
		Sprite player( "data/smiley.bmp" );
		Display().setTitle( "Blocraft" );

		while ( Display().running() ){

			if ( Display().mouseOver(player) && Display().LMB() ){
				player.move( Display().mouseX()-player.width()/2,
					Display().mouseY()-player.height()/2 );
			}

			Display().clear();
			player.draw();
			Display().present();
		}
	} catch ( const CImgIOException& e ){
		cout << e.what() << endl;
	}  
}
