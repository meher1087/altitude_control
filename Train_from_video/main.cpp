/*
 * main.cpp
 *
 *  Created on: 25-Mar-2017
 *      Author: mady
 *      Program aims to train classifier with video feed and then detect the trained object
 *
 *
 */



#include <stdio.h>
#include "get_data/get_data.h"
#include <iostream>
#include "create_samples/utility.hpp"
using namespace std;

int main(){


	int cam_status =  get_data(); // captures some images from cam and returns -1 if cam cant be opened.

	if(cam_status == -1)
		cout << "cam cant be opened" << endl;

	//cvCreateTrainingSamples("-img","postives.txt",0,1.1,"negatives.txt",1500);


	/*
	 * void cvCreateTrainingSamples( const char* filename,
                              const char* imgfilename, int bgcolor, int bgthreshold,
                              const char* bgfilename, int count,
                              int invert = 0, int maxintensitydev = 40,
                              double maxxangle = 1.1,
                              double maxyangle = 1.1,
                              double maxzangle = 0.5,
                              int showsamples = 0,
                              int winwidth = 24, int winheight = 24 );
	 *
	 */

return 0;
}


