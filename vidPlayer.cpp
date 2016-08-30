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
    if (argc != 5) {
        cout << "vidPlayer input-vid-path scale-up-factor"
             << " speed-up-factor parse-to-image[y/n]" << endl;
        exit(-1);
    }

    /* Initialization */
    Mat frame;  // to store video frames
    unsigned int count = 0;
    char countStr [50];
    double scaleFactor = stod(argv[2]);
    double speedFactor = stod(argv[3]);
    string outFramePath = "";  // parse frames under this folder

    /* Basic info */
    cout << "OpenCV version " << CV_VERSION << endl;
    if (string(argv[4]) == "y") {
        cin >> outFramePath;
        cout << "writing under " << outFramePath << endl;
    }
 
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
