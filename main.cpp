#include <QCoreApplication>
#include <countthreshold.h>
#include <all.h>

class WatershedSegmenter{
private:
    cv::Mat markers;
public:
    void setMarkers(cv::Mat& markerframe)
    {
        markerframe.convertTo(markers, CV_32S);
    }

    cv::Mat process(cv::Mat &frame)
    {
        cv::watershed(frame, markers);
        markers.convertTo(markers,CV_8U);
        return markers;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString filename="/home/alexandra/trash/video_full.avi";
    VideoCapture capture;

    if(! capture.open(filename.toStdString()))
        throw 1;
    Mat frame;
    capture.read(frame);
    do
    {
       Mat binary;
        //cvtColor(frame, binary, CV_BGR2GRAY);
        //threshold(binary,binary,0,255,THRESH_TRUNC|CV_THRESH_OTSU);
        CountThreshold threshold;
        int t=threshold.gradThreshold(frame);
        cout<<t<<endl;
        cv::threshold(frame,frame,t,255,CV_THRESH_TRUNC);
        imshow( "frame", frame );
        cv::threshold(frame, binary, 110, 255, THRESH_BINARY);
        imshow( "binary", binary );
        Mat fg;
        Mat bg;
        erode (binary,fg,Mat(),Point(-1,-1),3);
        imshow( "fg", fg );
        /*dilate(binary,bg,Mat(),Point(-1,-1),3);
        cv::threshold(bg,bg,1,128,THRESH_BINARY_INV);
        Mat markers(binary.size(),CV_8U,cv::Scalar(0));
        markers= fg+bg;
        //imshow( "original", frame );

        //imshow( "bg", bg );

           // Create watershed segmentation object
           WatershedSegmenter segmenter;
           segmenter.setMarkers(markers);

           Mat result = segmenter.process(frame);
           result.convertTo(result,CV_8U);
           Mat mask,dest;
           convertScaleAbs(result, mask, 1, 0);
           threshold(mask, mask, 1, 255, THRESH_BINARY);
           bitwise_and(frame, frame, dest, mask);
           dest.convertTo(dest,CV_8U);
           imshow("final_result", dest);*/


    /*cv::Mat dest;
    imshow("originalframe", frame);

    // Create markers frame
    cv::Mat markers(frame.size(),CV_8U,cv::Scalar(-1));
    //Rect(topleftcornerX, topleftcornerY, width, height);
    //top rectangle
    markers(Rect(0,0,frame.cols, 2)) = Scalar::all(1);
    //bottom rectangle
    markers(Rect(0,frame.rows-2,frame.cols, 2)) = Scalar::all(1);
    //left rectangle
    markers(Rect(0,0,2,frame.rows)) = Scalar::all(1);
    //right rectangle
    markers(Rect(frame.cols-2,0,2,frame.rows)) = Scalar::all(1);
    //centre rectangle
    //int centreW = frame.cols/4;
    //int centreH = frame.rows/4;
    //markers(Rect((frame.cols/2)-(centreW/2),(frame.rows/2)-(centreH/2), centreW, centreH)) = Scalar::all(2);
    markers(Rect(frame.cols/2,frame.rows/2,50, 50)) = Scalar::all(2);
    markers.convertTo(markers,CV_BGR2GRAY);
    imshow("markers", markers);

    //Create watershed segmentation object
    WatershedSegmenter segmenter;
    segmenter.setMarkers(markers);
    cv::Mat wshedMask = segmenter.process(frame);
    cv::Mat mask;
    convertScaleAbs(wshedMask, mask, 1, 0);
    threshold(mask, mask, 1, 255, THRESH_BINARY);
    bitwise_and(frame, frame, dest, mask);
    dest.convertTo(dest,CV_8U);

    imshow("final_result", dest);*/
        break;
    QTest::qWait(40);
    }
    while (capture.read(frame));

    return a.exec();
}
