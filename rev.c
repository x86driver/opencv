////////////////////////////////////////////////////////////////////////
//
// hello-world.cpp
//
// 該程式從文件中讀入一幅圖像，將之反色，然後顯示出來. 
//
////////////////////////////////////////////////////////////////////////
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
	img=cvLoadImage(argv[1], 1);
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
 
	// create a window
	cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE); 
	cvMoveWindow("mainWin", 100, 100); 
 
	// invert the image
	// 相當於 cvNot(img);
	for(i=0;i<height;i++) for(j=0;j<width;j++) for(k=0;k<channels;k++)
						     data[i*step+j*channels+k]=255-data[i*step+j*channels+k]; 
 
	// show the image
	cvShowImage("mainWin", img ); 
 
	// wait for a key
	cvWaitKey(0); 
 
	// release the image
	cvReleaseImage(&img );
	return 0;
}
