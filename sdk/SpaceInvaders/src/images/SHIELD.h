/*  GIMP header image file format (INDEXED): C:\Users\julia\Downloads\Game\Game\Game.sdk\SpaceInvaders\src\images\SHIELD.h  */

static unsigned int width = 22;
static unsigned int height = 16;

/*  Call this macro repeatedly.  After each use, the pixel data can be extracted  */

#define HEADER_PIXEL(data,pixel) {\
pixel[0] = header_data_cmap[(unsigned char)data[0]][0]; \
pixel[1] = header_data_cmap[(unsigned char)data[0]][1]; \
pixel[2] = header_data_cmap[(unsigned char)data[0]][2]; \
data ++; }

static char header_data_cmap[256][3] = {
	{  0,  0,  0},
	{255,255,255},
	{255,255,255}
	};
static char header_data[] = {
	0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,0,0,0,0,
	0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,0,0,0,
	0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,0,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,
	1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,
	1,1,1,1,1,1,
	1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,
	1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,
	1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1
	};
