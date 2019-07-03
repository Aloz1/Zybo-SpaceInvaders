/*  GIMP header image file format (INDEXED): C:\Users\julia\Downloads\Game\Game\Game.sdk\SpaceInvaders\src\images\INV_MED_1.h  */

// Width and height of image.
static unsigned int width = 11;
static unsigned int height = 8;

// Not used by us, simply a residual macro added by gimp.
#define HEADER_PIXEL(data,pixel) {\
pixel[0] = header_data_cmap[(unsigned char)data[0]][0]; \
pixel[1] = header_data_cmap[(unsigned char)data[0]][1]; \
pixel[2] = header_data_cmap[(unsigned char)data[0]][2]; \
data ++; }

// Not used by us, simply a residual data structure added
// by gimp for RGB pixel decoding. We aren't using RGB
// pixels, just the pixel indicies.
static char header_data_cmap[256][3] = {
	{  0,  0,  0},
	{255,255,255},
	{255,255,255}//,
    //...
    // Continues on for another 253 lines. Not used by
    // us, simply a residual from Gimp export.
};

// Image pixel data in a colour indexed format. Used for sprites.
static char header_data[] = {
	0,0,1,0,0,0,0,0,1,0,0,
	0,0,0,1,0,0,0,1,0,0,0,
	0,0,1,1,1,1,1,1,1,0,0,
	0,1,1,0,1,1,1,0,1,1,0,
	1,1,1,1,1,1,1,1,1,1,1,
	1,0,1,1,1,1,1,1,1,0,1,
	1,0,1,0,0,0,0,0,1,0,1,
	0,0,0,1,1,0,1,1,0,0,0
};
