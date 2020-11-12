#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>

 
using namespace cv;
using namespace std;
 

int Photo_Combiner_Color(){
    cout << "Started the process" << endl;
      
    Mat image1,image2,image2_resized,image3;
    image1 = imread("img1.jpg",IMREAD_COLOR);
    if( !image1.data ) { cout << "Image 1 not found " <<endl; return -1;}
    
    image2 = imread("img2.jpg",IMREAD_COLOR);
    if( !image2.data ) {cout << "Image 2 not found " <<endl; return -1;}
    
    int img1_height = image1.size().height;
    int img1_width = image1.size().width;
    
    if (image2.size().height != img1_height || image2.size().width != img1_width){ //if the images aren't the same size, second image gets resized to the same size as the first
        resize(image2, image2_resized, Size(img1_width, img1_height));
        absdiff(image1, image2_resized, image3);
        imwrite("output.jpg", image3);
        cout << "The images were resized to the same size" << endl;
        return 0;
    }
             
    absdiff( image1,  image2,  image3);
    imwrite("output.jpg",image3);
    cout << "Ended. Your new combined file is called: output.jpg" << endl;
    return 0;
}

int Photo_Combiner_GrayScale(){
    cout << "Started" << endl;
    Mat image1, image2, image2_resized, image3;
    
    image1 = imread("img1.jpg", IMREAD_GRAYSCALE);
    if(!image1.data) { cout << "Image 1 not found " <<endl; return -1;}
 
    image2 = imread("img2.jpg",IMREAD_GRAYSCALE);
    if(!image2.data) {cout << "Image 2 not found " <<endl; return -1;}
    
    int img1_height = image1.size().height;
    int img1_width = image1.size().width;
    
    if (image2.size().height != img1_height || image2.size().width != img1_width){ //if the images aren't the same size, second image gets resized to the same size as the first
        resize(image2, image2_resized, Size(img1_width, img1_height));
        absdiff(image1, image2_resized, image3);
        imwrite("output.jpg", image3);
        cout << "The images were resized to the same size" << endl;
        return 0;
    }
             
    absdiff( image1,  image2,  image3);
    imwrite("output.jpg",image3);
    cout << "Ended. Your new combined file is called: output.jpg" << endl;
    return 0;
    
}

int Photo_brightner() {
    
    cout << "Started brightening photo process" << endl;
    
    Mat img = imread("img.jpg", IMREAD_COLOR);
    if (!img.data) {cout << "Image not found " <<endl; return -1;}
    
    Mat brght_img = Mat::zeros(img.size(), img.type());
    double alpha = 1.0;
    int beta = 0;
    
    //brightness and contrast are changed according to equation g(x) = αf(x)+β
    cout << "Enter the alpha value you want. Recommended between [1.0-3.0] "; cin >> alpha;
    cout << "Enter beta value. Recommended between [0-100] "; cin >> beta;
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            for (int k = 0; k < img.channels(); k++) { //each pixel has 3 values, each for red, blue and green
                brght_img.at<Vec3b>(i,j)[k] = saturate_cast<uchar>(alpha * img.at<Vec3b>(i,j)[k] + beta); //(row, column)[channel]
            } //saturate_cast is used to ensure the value doesn't go out of bounds of RGB
        }
    }
    imwrite("output.jpg", brght_img);
    return 0;
}

int main( )
{
    Photo_Combiner_Color();
    //Photo_Combiner_GrayScale();
    //Photo_brightner();
    return 0;
    
}
