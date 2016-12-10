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
    /* Basic checking */
    if (argc != 2) {
        cout << "vidPlayer input-video-path " << endl;
        exit(-1);
    }

    /* Initialization */
    Mat frame;  // to store video frames
    unsigned int count = 0;
    char countStr [50];
    double scaleFactor;
    double speedFactor;
    string ifParse2img;
    string outFramePath = "";  // parse frames under this folder

    /* Basic info */
    cout << "OpenCV version " << CV_VERSION << endl;
 
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
    
    /* Read user configuration */
    cout << "scale-up-factor [double]:" << endl;
    cin >> scaleFactor;
    
    cout << "speed-up-factor [double]:" << endl;
    cin >> speedFactor;

    cout << "parse-to-image [y/n]:" << endl;
    cin >> ifParse2img;
    if (ifParse2img == "y") {
        cout << "to which folder [for example, /home/gengshan/aa will give\
                 /home/gengshan/aa00001.jpg ...]:" << endl;
        cin >> outFramePath;
        cout << "writing under " << outFramePath << endl;
    }

   /* read in and show frames */
    for(;;) {
        count++;
        targetVid >> frame;
        if(frame.empty()) {
            break;
        }

        /* basic process */
        resize(frame, frame, Size(frameWid * scaleFactor, 
                                  frameHgt * scaleFactor));
    
        /* display */
        sprintf(countStr, "%04d", count);  // padding with zeros
        cout << "frame\t" << countStr << "/" << totalFrame << endl;
        imshow("vid", frame);
        if (outFramePath.length() != 0) {
            imwrite(outFramePath + countStr + ".jpg", frame);
            continue;
        }
        char key = (char)waitKey(1/vidFPS *  // adjust wait time wrt. FPS
                                     1000 / speedFactor);
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
