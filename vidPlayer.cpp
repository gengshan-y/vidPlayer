/***
 * Filename:        vidPlayer.cpp
 * Date:            Aug 24 2016
 * Last Edited by:  Gengshan Yang
 * Description:     A personalized OpenCV-based video player.
 ***/

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
    /* Basic info */
    if (argc != 3) {
        cout << "vidPlayer input-vid-path down-scale-factor" << endl;
        exit(-1);
    }
    cout << "OpenCV version " << CV_VERSION << endl;

    /* Initialization */
    Mat frame;  // to store video frames
    unsigned int count = 0;
    char countStr [50];
    unsigned int scaleFactor = stoi(argv[2]);

    /* Read video information */
    VideoCapture targetVid(argv[1]);
    if(!targetVid.isOpened()) {
        cout << "open failed." << endl;
        exit(-1);
    }
    unsigned int totalFrame = targetVid.get(CV_CAP_PROP_FRAME_COUNT);
    unsigned int frameWid = targetVid.get(CV_CAP_PROP_FRAME_WIDTH);
    unsigned int frameHgt = targetVid.get(CV_CAP_PROP_FRAME_HEIGHT);
    double vidFPS = targetVid.get(CV_CAP_PROP_FPS);

    /* read in and show frames */
    for(;;) {
        count++;
        targetVid >> frame;
        if(frame.empty()) {
            break;
        }

        /* basic process */
        resize(frame, frame, Size(frameWid/scaleFactor, frameHgt/scaleFactor));
    
        /* display */     
        sprintf(countStr, "%04d", count);  // padding with zeros
        cout << "frame\t" << countStr << "/" << totalFrame << endl;
        imshow("vid", frame);
        char key = (char)waitKey(1/vidFPS*1000);  // adjust wait time wrt. FPS
        switch (key) {
        case 'q':
        case 'Q':
        case 27:
            return 0;  // stop program
        default:
            continue;
        }
    }
    
    return 0;
}
