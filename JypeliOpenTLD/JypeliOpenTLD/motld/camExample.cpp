/* Copyright (C) 2012 Christian Lutz, Thorsten Engesser
 * 
 * This file is part of motld
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>


#include "MultiObjectTLD.h"

#define LOADCLASSIFIERATSTART 0
#define CLASSIFIERFILENAME "test.moctld"

//uncomment if you have a high resolution camera and want to speed up tracking
#define FORCE_RESIZING
#define RESOLUTION_X 320
#define RESOLUTION_Y 240

#define MOUSE_MODE_MARKER 0
#define MOUSE_MODE_ADD_BOX 1
#define MOUSE_MODE_IDLE 2
bool ivQuit = false;
int ivWidth, ivHeight;
ObjectBox mouseBox = {0,0,0,0,0};
int mouseMode = MOUSE_MODE_IDLE;
int drawMode = 255;
bool learningEnabled = true, save = false, load = false, reset = false;

void* Run(void*);

/*
int main(int argc, char *argv[])
{
  Init(argc, argv);
  Run(0);
  return 0;
}*/


void* Run(void*)
{
  int size = ivWidth*ivHeight;
    
  // Initialize MultiObjectTLD
  #if LOADCLASSIFIERATSTART
  MultiObjectTLD p = MultiObjectTLD::loadClassifier((char*)CLASSIFIERFILENAME);
  #else
  MOTLDSettings settings(COLOR_MODE_RGB);
  settings.useColor = false;
  MultiObjectTLD p(ivWidth, ivHeight, settings);
  #endif
  
  Matrix maRed;
  Matrix maGreen;
  Matrix maBlue;
  unsigned char img[RESOLUTION_X *RESOLUTION_Y * 3];
  while(!ivQuit)
  {    
    /*
    if(reset){
      p = *(new MultiObjectTLD(ivWidth, ivHeight, COLOR_MODE_RGB));
      reset = false;
    }
    if(load){
      p = MultiObjectTLD::loadClassifier(CLASSIFIERFILENAME);
      load = false;
    }
    */
    
    // Grab an image
    //if(!cvGrabFrame(capture)){

	// convert 
    //for(int j = 0; j<size; j++){
    //  img[j] = frame->imageData[j*3+2];
    //  img[j+size] = frame->imageData[j*3+1];
    //  img[j+2*size] = frame->imageData[j*3];
    //}
    
    // Process it with motld
    p.processFrame(img);
    p.addObject(mouseBox);
    
    // Display result
    p.getDebugImage(img, maRed, maGreen, maBlue, drawMode);    
    //FromRGB(maRed, maGreen, maBlue);
    //cvShowImage("MOCTLD", curImage);
    p.enableLearning(learningEnabled);
    if(save){
      p.saveClassifier((char*)CLASSIFIERFILENAME);
      save = false;
    }
  }
  //delete[] img;
  //cvReleaseCapture(&capture);
  return 0;
}

/*
void FromRGB(Matrix& maRed, Matrix& maGreen, Matrix& maBlue)
{
  for(int i = 0; i < ivWidth*ivHeight; ++i){
    curImage->imageData[3*i+2] = maRed.data()[i];
    curImage->imageData[3*i+1] = maGreen.data()[i];
    curImage->imageData[3*i+0] = maBlue.data()[i];
  }
  //at this place you could save the images using
  //cvSaveImage(filename, curImage);
  if(mouseMode == MOUSE_MODE_MARKER)
  {
    CvPoint pt1; pt1.x = mouseBox.x; pt1.y = mouseBox.y;
    CvPoint pt2; pt2.x = mouseBox.x + mouseBox.width; pt2.y = mouseBox.y + mouseBox.height;  
    cvRectangle(curImage, pt1, pt2, CV_RGB(0,0,255));
  }
}*/
