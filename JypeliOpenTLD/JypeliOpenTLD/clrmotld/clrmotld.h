// clrmotld.h

#pragma once

#include "motld.h"
#include "MultiObjectTLD.h"

#define RESOLUTION_X 640
#define RESOLUTION_Y 480

using namespace System;
using namespace System::Runtime::InteropServices;

namespace clrmotld {

	public ref class MOTLD
	{
	private:
		MOTLDSettings* settings;
		MultiObjectTLD* p;
		int frameCounter;
		int width;
		int height;
	public:
		void Init(int width, int height);
		void ProcessFrame(array<System::Byte>^ data, bool writeDebugImage);
		void AddObjectBox(int x1, int y1, int x2, int y2);
		void SetLearningMode(bool learn);
		bool IsTrackingOk();
		void GetObjectPosition([Out] int% x, [Out] int% y);
	};
}
