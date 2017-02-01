#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;

using namespace std;

Mat findMarker(Mat img);
void cvShowManyImages(char* title, int nArgs, ...);


// Mat src, src_gray;
// Mat dst, detected_edges;

// int edgeThresh = 1;
// int lowThreshold;
// int const max_lowThreshold = 100;
// int rat = 3;
// int kernel_size = 3;
// char* window_name = "Edge Map";

// /**
//  * @function CannyThreshold
//  * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
//  */
// void CannyThreshold(int, void*)
// {
//   /// Reduce noise with a kernel 3x3
//   blur( src_gray, detected_edges, Size(3,3) );

//   /// Canny detector
//   Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*rat, kernel_size );

//   /// Using Canny's output as a mask, we display our result
//   dst = Scalar::all(0);

//   src.copyTo( dst, detected_edges);
//   imshow( window_name, dst );
//  }


// * @function main 
// int main( int argc, char** argv )
// {
//   /// Load an image
//   src = imread("water3.jpg");

//   if( !src.data )
//   { return -1; }

//   /// Create a matrix of the same type and size as src (for dst)
//   dst.create( src.size(), src.type() );

//   /// Convert the image to grayscale
//   cvtColor( src, src_gray, CV_BGR2GRAY );

//   /// Create a window
//   namedWindow( window_name, CV_WINDOW_AUTOSIZE );

//   /// Create a Trackbar for user to enter threshold
//   createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );

//   /// Show the image
//   CannyThreshold(0, 0);

//   /// Wait until user exit program by pressing a key
//   waitKey(0);

//   return 0;
//   }



int main( int argc, const char** argv )
{
     Mat imgmat1 = imread("water1.jpg", CV_LOAD_IMAGE_UNCHANGED); //read the image data in the file "test.png" and store it in 'img'
     Mat imgmat2 = imread("water2.jpg", CV_LOAD_IMAGE_UNCHANGED);
     Mat imgmat3 = imread("water3.jpg", CV_LOAD_IMAGE_UNCHANGED);
     // if (img1.empty()) //check whether the image is loaded or not
     // {
     //      cout << "Error : Image cannot be loaded..!!" << endl;
     //      //system("pause"); //wait for a key press
     //      return -1;
     // }
     //find markers
     Mat marker1 = findMarker(imgmat1);
     Mat marker2 = findMarker(imgmat2);
     Mat marker3 = findMarker(imgmat3);

     //display images
     namedWindow("water1", WINDOW_NORMAL); //create a window with the name "MyWindow"
     namedWindow("water2", WINDOW_NORMAL); //create a window with the name "MyWindow"
     namedWindow("water3", WINDOW_NORMAL); //create a window with the name "MyWindow"
     imshow("water1", marker1); //display the image which is stored in the 'img' in the "MyWindow" window
     imshow("water2", marker2); //display the image which is stored in the 'img' in the "MyWindow" window
     imshow("water3", marker3); //display the image which is stored in the 'img' in the "MyWindow" window
     // resizeWindow("Normal pic", 1400, 1200);
     //imshow("Gray pic", gray); //display the image which is stored in the 'img' in the "MyWindow" window

     waitKey(5000); //wait infinite time for a keypress

     // IplImage *img1 = new IplImage(findMarker(imgmat1).clone());
     // IplImage *img2 = new IplImage(findMarker(imgmat2).clone());
     // IplImage *img3 = new IplImage(findMarker(imgmat3).clone());
     // cvShowManyImages("Image", 3, img1, img2, img3);
     //findMarker(img1);
     

     return 0;
}

Mat findMarker(Mat img){
     //initialize necessary Mats
     Mat gray, resize, edges;
     //convert images to grayscale for ease of parsing contours
     cvtColor(img, gray, CV_BGR2GRAY);
     //blur the grayscale to eliminate some random contours
     blur(gray, edges, Size(3,3));
     //get contours of image
     Canny(edges, edges, 35, 160);
     //keep largest contour in image and return it
     Mat *contours;
     // findContours(gray, contours, 0, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
     // Mat maxSizeContour;
     // for( int i = 0; i< contours.size(); i++ )
     // {
     //   Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
     //   drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
     // }
     // Mat c = max(contours, contourArea(contours, false));
     return edges;
     

     // destroyWindow("MyWindow"); //destroy the window with the name, "MyWindow"
}


void cvShowManyImages(char* title, int nArgs, ...) {

    // img - Used for getting the arguments 
    IplImage *img;

    // [[DispImage]] - the image in which input images are to be copied
    IplImage *DispImage;

    int size;
    int i;
    int m, n;
    int x, y;

    // w - Maximum number of images in a row 
    // h - Maximum number of images in a column 
    int w, h;

    // scale - How much we have to resize the image
    float scale;
    int max;

    // If the number of arguments is lesser than 0 or greater than 12
    // return without displaying 
    if(nArgs <= 0) {
        printf("Number of arguments too small....\n");
        return;
    }
    else if(nArgs > 12) {
        printf("Number of arguments too large....\n");
        return;
    }
    // Determine the size of the image, 
    // and the number of rows/cols 
    // from number of arguments 
    else if (nArgs == 1) {
        w = h = 1;
        size = 300;
    }
    else if (nArgs == 2) {
        w = 2; h = 1;
        size = 300;
    }
    else if (nArgs == 3 || nArgs == 4) {
        w = 2; h = 2;
        size = 300;
    }
    else if (nArgs == 5 || nArgs == 6) {
        w = 3; h = 2;
        size = 200;
    }
    else if (nArgs == 7 || nArgs == 8) {
        w = 4; h = 2;
        size = 200;
    }
    else {
        w = 4; h = 3;
        size = 150;
    }

    // Create a new 3 channel image
    DispImage = cvCreateImage( cvSize(100 + size*w, 60 + size*h), 8, 3 );

    // Used to get the arguments passed
    va_list args;
    va_start(args, nArgs);

    // Loop for nArgs number of arguments
    for (i = 0, m = 20, n = 20; i < nArgs; i++, m += (20 + size)) {

        // Get the Pointer to the IplImage
        img = va_arg(args, IplImage*);

        // Check whether it is NULL or not
        // If it is NULL, release the image, and return
        if(img == 0) {
            printf("Invalid arguments");
            cvReleaseImage(&DispImage);
            return;
        }

        // Find the width and height of the image
        x = img->width;
        y = img->height;

        // Find whether height or width is greater in order to resize the image
        max = (x > y)? x: y;

        // Find the scaling factor to resize the image
        scale = (float) ( (float) max / size );

        // Used to Align the images
        if( i % w == 0 && m!= 20) {
            m = 20;
            n+= 20 + size;
        }

        // Set the image ROI to display the current image
        cvSetImageROI(DispImage, cvRect(m, n, (int)( x/scale ), (int)( y/scale )));

        // Resize the input image and copy the it to the Single Big Image
        cvResize(img, DispImage);

        // Reset the ROI in order to display the next image
        cvResetImageROI(DispImage);
    }

    // Create a new window, and show the Single Big Image
    cvNamedWindow( title, 1 );
    cvShowImage( title, DispImage);

    cvWaitKey();
    cvDestroyWindow(title);

    // End the number of arguments
    va_end(args);

    // Release the Image Memory
    cvReleaseImage(&DispImage);
}



