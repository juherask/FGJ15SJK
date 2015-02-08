// This is the main DLL file.
// Offer motld as clr (C#/.NET) dll.
// (c) Jussi Rasku

#include "stdafx.h"

#include "clrmotld.h"

namespace clrmotld {

	void MOTLD::Init(int width, int height)
	{
		this->width = width;
		this->height = height;
		settings = new MOTLDSettings(COLOR_MODE_GRAY);
		settings->useColor = false;
		p = new MultiObjectTLD(width, height, *settings);
		frameCounter = 0;
	}

	void MOTLD::ProcessFrame(array<System::Byte>^ data, bool writeDebugImage)
	{
		cli::pin_ptr<System::Byte> dataptr = &data[0];
		unsigned char* img = dataptr;
		p->processFrame(img);
		frameCounter++;

		if (writeDebugImage)
		{
			char filename[255];
			sprintf(filename, "out/debug%d.ppm", frameCounter);
			p->writeDebugImage(img, filename, DEBUG_DRAW_DETECTIONS & DEBUG_DRAW_CROSSES & DEBUG_DRAW_PATCHES);	
		}
	}

	void MOTLD::AddObjectBox(int x1, int y1, int x2, int y2)
	{
		ObjectBox b = { (float)x1, (float)y1, (float)(x2 - x1), (float)(y2 - y1), 0 };
		p->addObject(b);
	}

	// Set learning more on or off
	void MOTLD::SetLearningMode(bool learn)
	{
		p->enableLearning(learn);
	}

	bool MOTLD::IsTrackingOk()
	{
		return p->getStatus() != STATUS_LOST;
	}

	void MOTLD::GetObjectPosition([Out] int% x, [Out] int% y)
	{
		x = p->getObjectBox().x + p->getObjectBox().width/2;
		y = p->getObjectBox().y + p->getObjectBox().height/2;
	}

};