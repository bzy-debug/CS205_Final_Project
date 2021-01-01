#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cout << "usage: FaceDetection <Image_Path>" << endl;
        return -1;
    }
    
    Mat image;
    float imagef[128][128][3];
    image = imread( argv[1], 1 );
    int row = image.rows;
    int col = image.cols;
    for (int i=0; i<row; i++)
        for (int j=0; j<col; j++)
            for (int k=0; k<3; k++)
                imagef[i][j][2 - k] = (int) image.ptr<Vec3b>(i)[j][k] / 255.0f;

    for (int i=0; i<row; i++)
        for (int j=0; j<col; j++)
        {
            for (int k=0; k<3; k++)
                cout << imagef[i][j][k] << ' ';
            cout << endl;
        }
                
    
}