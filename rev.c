#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>

int main(int argc, char *argv[])
{
	IplImage* img = 0;
	int height,width,step,channels;
	uchar *data;
	int i,j,k;

	if(argc<2){
		printf("Usage: main <image-file-name>\n\7");
		exit(0);
	}

	// load an image
	img=cvLoadImage(argv[1], 0);
	if(!img){
		printf("Could not load image file: %s\n",argv[1]);
		exit(0);
	}

	// get the image data
	height    = img->height;
	width     = img->width;
	step      = img->widthStep;
	channels  = img->nChannels;
	data      = (uchar *)img->imageData;
	printf("Processing a %dx%d image with %d channels\n",height,width,channels);

	IplImage *smoothImg = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	IplImage *sobelImg = cvCreateImage(cvSize(width, height), IPL_DEPTH_16S, 1);
	IplImage *binaryImg = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	IplImage *adThresImg = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);

	cvSmooth(img, smoothImg, CV_MEDIAN, 3, 0, 0, 0);
	cvThreshold(smoothImg, binaryImg, atoi(argv[4]), 255, CV_THRESH_BINARY);
	double max_value = 255;
	int adpative_method=CV_ADAPTIVE_THRESH_GAUSSIAN_C;//CV_ADAPTIVE_THRESH_MEAN_C
	int threshold_type=CV_THRESH_BINARY;
	int block_size=atoi(argv[2]);
	int offset=atoi(argv[3]);
	cvAdaptiveThreshold(smoothImg,adThresImg,max_value,adpative_method,threshold_type,block_size,offset);
	cvSobel(smoothImg, sobelImg, 1, 1, 3);

	// create a window

//	cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE);
//	cvMoveWindow("mainWin", 100, 100);
//	cvShowImage("mainWin", smoothImg);

//	cvNamedWindow("sobel", CV_WINDOW_AUTOSIZE);
//	cvShowImage("sobel", sobelImg);

        cvNamedWindow("thres", CV_WINDOW_AUTOSIZE);
        cvShowImage("thres", adThresImg);

//        cvNamedWindow("binary", CV_WINDOW_AUTOSIZE);
//        cvShowImage("binary", binaryImg);

	// wait for a key
	cvWaitKey(0);

	cvSaveImage("a.jpg", adThresImg, 0);

	// release the image
	cvReleaseImage(&img );
	return 0;
}
