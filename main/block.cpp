#include "block.h"

/**
 * Creates a square Block that is dimension x dimension pixels in size,
 * starting at (x, y) on img. Assumes that the requested
 * Block fits on the image (inputs are feasible)
 */
void Block::Build(PNG& img, unsigned int x, unsigned int y, unsigned int dimension) {
	// complete your implementation below
// for(unsigned int i=x;i<dimension+x;i++){
// 		vector<HSLAPixel> vec;
// 		for(unsigned int j=y;j<dimension+y;j++){
// 			if(i<img.width() && j<img.height()){
// 			HSLAPixel *pixels = img.getPixel(i,j);
// 			HSLAPixel deference = *pixels;
// 			vec.push_back(deference);
// 			}
// 		}
// 		data.push_back(vec);
// 	}

	for(unsigned int j = y;j<dimension+y;j++){
		vector<HSLAPixel> vec;
		for(unsigned int i=x;i<dimension+x;i++){
			if(i<img.width() && j < img.height()){
				HSLAPixel *pixels = img.getPixel(i,j);
				HSLAPixel deference = *pixels;
			    vec.push_back(deference);

			}
		}
		data.push_back(vec);
}


}
	

/**
 * Renders this Block onto img with its upper-left corner at (x, y).
 * Assumes block fits on the image.
 */
void Block::Render(PNG& img, unsigned int x, unsigned int y) const {
	// complete your implementation below
//   for (unsigned int i = 0;i< data.size(); i++) {
//         for (unsigned int j = 0; j < data[i].size(); j++) {

// 				HSLAPixel pixel = data[i][j];
				
// 				if((x+i < img.width()) && (y+j < img.height())){
// 				HSLAPixel *toberendered = img.getPixel(x+i,y+j);

// 				toberendered->h = pixel.h;
// 				toberendered->s = pixel.s;
// 				toberendered->l = pixel.l;
// 				toberendered->a = pixel.a;
// 				}
// 	}
//     } 


		for(unsigned int height =0; height<data.size();height++){

			for(unsigned int width =0;width <data[height].size();width++){

				HSLAPixel pixel = data[height][width];
				if( (x+width)<img.width() && (y+height)<img.height()){
					HSLAPixel *toberendered = img.getPixel(x+width,y+height);
					toberendered->h = pixel.h;
					toberendered->s = pixel.s;
					toberendered->l = pixel.l;
					toberendered->a = pixel.a;
				}
			}
		}



}

/**
 * Flips the Block's pixel data horizontally by a simple reflection
 * across the vertical axis through its middle.
 */
void Block::FlipHorizontal() {
	// complete your implementation below
// 	unsigned elems = static_cast<unsigned int>(data.size() / 2.0);
// 	for (unsigned int i = 0; i < elems; i++){
// 			swap(data[i],data[data.size() - 1 - i]);
// 		}
// }

for (unsigned int i = 0; i < data.size(); i++){
		unsigned elems = static_cast<unsigned int>(data[i].size() / 2.0);
		for(unsigned int j = 0; j < elems;j++){
			swap(data[i][j],data[i][data[i].size() - 1 - j]);
		}
	}
}


/**
 * Rotates the Block's pixel data 90 degrees counter-clockwise.
 */
void Block::RotateCCW() {
	// vector<vector<HSLAPixel>> rotatedData(data[0].size(), vector<HSLAPixel>(data.size()));
    // for (unsigned int i = 0; i < data.size(); i++) {
    //     for (unsigned int j = 0; j < data[i].size(); j++) {
    //         rotatedData[j][data.size() - 1 - i] = data[i][j];
    //     }
    // }

	 vector<vector<HSLAPixel>> rotatedData(data[0].size(), vector<HSLAPixel>(data.size()));
    for (unsigned int i = 0; i < data.size(); i++) {
        for (unsigned int j = 0; j < data[i].size(); j++) {
            rotatedData[data[i].size() - 1 - j][i] = data[i][j];
        }
    }
    data = rotatedData;
}

/**
 * Returns the dimension of the block (its width or height).
 */
unsigned int Block::Dimension() const {
	// replace the statement below with your implementation
	return data.size();
}