/* v4l2loopback module should be loaded before running binary of this program*/
#include <opencv2/highgui/highgui_c.h>
#include<stdio.h>
#include <linux/videodev2.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <sys/ioctl.h>
#define VIDEO_DEVICE "/dev/video1"
#define FRAME_WIDTH  640
#define FRAME_HEIGHT 480
#define FRAME_SIZE (FRAME_WIDTH * FRAME_HEIGHT * 3)
#define FPS 20
#define DEBUG 1
struct process{
	CvCapture* capture;
	IplImage *img;
	int fdwr;
};


int main(int argc, char** argv) 
{
        struct v4l2_capability vid_caps;
        struct v4l2_format vid_format;
	/*-----------------------------------------
	              v4l2loopback
	------------------------------------------*/
        __u8 buffer[FRAME_SIZE];
        __u8 check_buffer[FRAME_SIZE];
        int i;
        for (i = 0; i < FRAME_SIZE; ++i)
	{
                buffer[i] = i % 2;
                check_buffer[i] = 0;
        }

        int fdwr = open(VIDEO_DEVICE, O_RDWR);
        assert(fdwr >= 0);

        int ret_code = ioctl(fdwr, VIDIOC_QUERYCAP, &vid_caps);
        assert(ret_code != -1);
        memset(&vid_format, 0, sizeof(vid_format));
        vid_format.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
        vid_format.fmt.pix.width = FRAME_WIDTH;
        vid_format.fmt.pix.height = FRAME_HEIGHT;
        vid_format.fmt.pix.pixelformat =V4L2_PIX_FMT_BGR24;//V4L2_PIX_FMT_YUYV;//V4L2_PIX_FMT_RGB32; //V4L2_PIX_FMT_YUYV;
        vid_format.fmt.pix.sizeimage = FRAME_WIDTH * FRAME_HEIGHT*3  ;
        vid_format.fmt.pix.field = V4L2_FIELD_NONE;
        vid_format.fmt.pix.bytesperline = FRAME_WIDTH * 3;
        vid_format.fmt.pix.colorspace = V4L2_COLORSPACE_SRGB ;//V4L2_COLORSPACE_JPEG;
        ret_code = ioctl(fdwr, VIDIOC_S_FMT, &vid_format);
        assert(ret_code != -1);


#ifdef DEBUG

    	cvNamedWindow("VIDEO0", CV_WINDOW_AUTOSIZE);
    	cvNamedWindow("VIDEO1", CV_WINDOW_AUTOSIZE);
    	cvNamedWindow("VIDEO_IMG", CV_WINDOW_AUTOSIZE);
#endif  	
	/*--------------------------------------------------
		opencv-Image combining
	-------------------------------------------------*/
	CvCapture* capture1 = cvCreateFileCapture(argv[1]);
    	CvCapture* capture2 = cvCreateFileCapture(argv[2]);
	CvCapture* capture3 = cvCreateFileCapture(argv[3]);
    	CvCapture* capture4 = cvCreateFileCapture(argv[4]);
	printf("vid1=%s \n vid2 =%s \n vid3=%s \n vid4 =%s \n", argv[1], argv[2] , argv[3], argv[4]); 

 
    	
    	char c;
	uchar *data;
	int height,width,step,channels, depth, j, k;;
	IplImage *img1 = 0,*img2 = 0,*img3 = 0,*img4 = 0,*main_img = 0; 
    	

	img1 = cvQueryFrame(capture1);      

  	height    = img1->height;
  	width     = img1->width;
  	step      = img1->widthStep;
  	channels  = img1->nChannels;
  	data      = (uchar *)img1->imageData;
	depth 	  = img1->depth;
  	printf("Processing a %dx%d image with %d channels\n",height,width,channels); 
  	main_img = cvCreateImage(cvSize(width*2,height*2), depth ,channels);

  	while(1) 
  	{
		img1=img2=img3=img4=0;
		img1 = cvQueryFrame(capture1);
		img2 = cvQueryFrame(capture2);
		img3 = cvQueryFrame(capture3);
		img4 = cvQueryFrame(capture4);
		
		if(!img4) 
		{printf("image 4 failed\n");}
		if(!img1) 
		break;

#ifdef DEBUG		
		cvShowImage("VIDEO0", img1);
		cvShowImage("VIDEO1", img2);
#endif
		if(img1) 
		{
		cvSetImageROI(main_img, cvRect(0, 0, width, height));
		cvCopy(img1,main_img,NULL);
		}
		if(img2) 
		{
		cvSetImageROI(main_img, cvRect(width,0, width, height));
		cvCopy(img2,main_img,NULL);
		}
		if(img3) 
		{
		cvSetImageROI(main_img, cvRect(0, height, width, height));
		cvCopy(img3,main_img,NULL);
		}
		if(img4) 
		{
		cvSetImageROI(main_img, cvRect(width,height, width, height)); 
		cvCopy(img4,main_img,NULL);
		}
		

		if(img1 || img2 || img3 || img4) 
		{
			cvResetImageROI(main_img);
			cvShowImage("VIDEO_IMG", main_img);
		
		printf("h=%d  w=%d \n",img2->height,img2->width);
		printf("Processing a %dx%d image with %d channels\n",height,width,channels);

                write(fdwr, main_img->imageData, FRAME_SIZE); /* copy Image to v4l2loopback device buffer */
		}
		c = cvWaitKey(33);
		if(c == 27);
	//	break;
    	}

	
	cvReleaseCapture(&capture1);
	cvReleaseCapture(&capture2);
	cvReleaseCapture(&capture3);
	cvReleaseCapture(&capture4);
		
#ifdef DEBUG    
	cvDestroyWindow("VIDEO");
	cvDestroyWindow("VIDEO1");
	cvDestroyWindow("VIDEO_IMG");
#endif
	close(fdwr);
	return 0;
}




