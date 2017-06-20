#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>
using namespace cv;


#define video
//#define still_pic
//#define disparity

const char *windowDisparity = "Disparity";

/** Global variables for face detection */
String face_cascade_name = "haarcascade_frontalface_default.xml";
CascadeClassifier face_cascade;
String window_name = "Capture - Face detection";


int main(int, char**)
{
   #ifdef video
   VideoCapture capture;
   Mat frame;

    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };

    //-- 2. Read the video stream
    capture.open( -1 );
    if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }

    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }

        //-- 3. Apply the classifier to the frame
       face_cascade.detectMultiScale( g1, faces2, 1.1, 20, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );


        char c = (char)waitKey(10);
        if( c == 27 ) { break; } // escape
    }

    #endif // video



    #ifdef still_pic
   char pathr[255];
   char pathl[255];

   // For Linux, path to save the captured image
   strcpy(pathr,"/home/mady/Documents/opencv_codes/detect_red/right.jpg");
   strcpy(pathl,"/home/mady/Documents/opencv_codes/detect_red/left.jpg");

        CvCapture* capture1 = cvCaptureFromCAM(1);
        CvCapture* capture2 = cvCaptureFromCAM(2);

    if ( !capture1 ) {
        fprintf( stderr, "ERROR: capture is NULL from right cam \n" );
        getchar();
        return -1;
                     }


     if ( !capture2) {
        fprintf( stderr, "ERROR: capture is NULL from left cam \n" );
        getchar();
        return -1;
                     }

     IplImage *frame_r;
     IplImage *frame_l;
    // Create a window in which the captured images will be presented
    cvNamedWindow( "mywindow_R", CV_WINDOW_AUTOSIZE );
       frame_r = cvQueryFrame( capture1);
       cvShowImage( "mywindow_R", frame_r);
         cvSaveImage(pathr, frame_r);
       waitKey(0);


    cvNamedWindow( "mywindow_L", CV_WINDOW_AUTOSIZE );
      frame_l = cvQueryFrame( capture2 );
       cvShowImage( "mywindow_L", frame_l );
       cvSaveImage(pathl, frame_l);
       waitKey(0);





    // Show the image captured from the camera in the window and repeat



    // Release the capture device housekeeping
    cvReleaseCapture( &capture1 );
    cvReleaseCapture( &capture2 );
    cvDestroyWindow( "mywindow_R" );
    cvDestroyWindow( "mywindow_L" );


    #endif
    // the camera will be deinitialized automatically in VideoCapture destructor

    #ifdef disparity
    Mat img1;
    Mat img2;
    Mat g1, g2;
    Mat disp, disp8;
    std::vector<Rect> faces1,faces2,faces;

     VideoCapture cap2(2); // open the default camera
     VideoCapture cap1(1); // open the default camera

    if(!cap1.isOpened())  // check if we succeeded
        return -1;

    if(!cap2.isOpened())  // check if we succeeded
        return -1;

    for(;;)
    {
        cap1 >> img1; // get a new frame from camera
        cap2 >> img2;

        cvtColor(img1, g1, CV_BGR2GRAY);
		cvtColor(img2, g2, CV_BGR2GRAY);

		 int ndisparities = 16*5;   /**< Range of disparity */
		 int SADWindowSize = 21; /**< Size of the block window. Must be odd */

		  Ptr<StereoBM> sbm = StereoBM::create( ndisparities, SADWindowSize );

		  sbm->compute(g1,g2,disp);

		  //-- Check its extreme values
		    double minVal; double maxVal;

		    minMaxLoc( disp, &minVal, &maxVal );

		    printf("Min disp: %f Max value: %f \n", minVal, maxVal);

		    //-- 4. Display it as a CV_8UC1 image
		    disp.convertTo( disp8, CV_8UC1, 255/(maxVal - minVal));

        //namedWindow( windowDisparity, WINDOW_NORMAL );

		   //-- 3. Apply the classifier to the frame
           equalizeHist( g1,  g1 );
           //-- Detect faces
           face_cascade.detectMultiScale( g1, faces1, 1.1, 20, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
           face_cascade.detectMultiScale( g1, faces2, 1.1, 20, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

           faces[0].x = (faces1[0].x + faces2[0].x)/2;
           faces[0].y = (faces1[0].y + faces2[0].y)/2;
           faces[0].width = (faces1[0].width + faces2[0].width)/2;
           faces[0].height = (faces1[0].height + faces2[0].height)/2;

           Point center( faces[0].x + faces[0].width/2, faces[0].y + faces[0].height/2 );
           ellipse( disp8, center, Size( faces[0].width/2, faces[0].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
		   imshow("edges", disp8);

        if(waitKey(30) == 27) break;

    }
#endif // disparity

    return 0;
}







