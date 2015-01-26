// motld.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "motld.h"
#include "MultiObjectTLD.h"

class MOTLD_API MultiObjectTLD
{


};
/*

#define RESOLUTION_X 640
#define RESOLUTION_Y 480

static MOTLDSettings* settings;
static MultiObjectTLD* p;
unsigned char img[RESOLUTION_X *RESOLUTION_Y * 3];

// This is an example of an exported variable
//MOTLD_API int nmotld=0;

 This is an example of an exported function.
MOTLD_API void init(void)
{
	settings = new MOTLDSettings(COLOR_MODE_RGB);
	settings->useColor = true;
	p = new MultiObjectTLD(640, 480, settings);
}

MOTLD_API void process_frame(char* data, int len)
{
	p->processFrame(img);
}

MOTLD_API void add_object_box(int x1, int y1, int x2, int y2)
{
	// From the first box
	ObjectBox b = { (float)x1, (float)y1, (float)(x2 - x1), (float)(y2 - y1), 0 };	
	p->addObject(b);
}

// Set learning more on or off
MOTLD_API void set_learning_mode(bool learn)
{
	p->enableLearning(learn);
}

MOTLD_API int is_tracking_ok(bool learn)
{
	p->enableLearning(learn);
}*/


