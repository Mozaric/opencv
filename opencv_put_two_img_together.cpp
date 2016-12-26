#include <iostream>
#include <cstring>

#include <opencv2/opencv.hpp>

#define SIDELINE_WIDTH 1

using namespace std;
using namespace cv;

string GetString(const string message);

int main()
{
	char* input = new char[256];
	string fileIn1, fileIn2;

	//load 1st image
	fileIn1 = GetString("Please Enter the 1st Image File Name: ");
	Mat img1 = imread(fileIn1, CV_LOAD_IMAGE_COLOR);
	if(!img1.data)
	{
		cout << "Can't Find image!!" << endl;
		system("pause");
		return -1;
	}

	//load 2nd image
	fileIn2 = GetString("Please Enter the 2nd Image File Name: ");
	Mat img2 = imread(fileIn2, CV_LOAD_IMAGE_UNCHANGED);
	if(!img2.data)
	{
		cout << "Can't Find image!!" << endl;
		system("pause");
		return -1;
	}

	//check two images' row
	if(img1.rows != img2.rows)
	{
		cout << "Two Images Need to Have Same Row." << endl;
		return -1;
	}

	//put two image together
	int col = img1.cols + img2.cols + 3 * SIDELINE_WIDTH;
	int row = img1.rows + 2 * SIDELINE_WIDTH;
	Mat img3 = Mat::zeros(row, col, CV_8UC3);

	for(int j = SIDELINE_WIDTH; j < row - SIDELINE_WIDTH; ++j)
	{
		for(int i = SIDELINE_WIDTH; i <col - SIDELINE_WIDTH; ++i)
		{
			if(i < img1.cols + SIDELINE_WIDTH)
			{
				img3.at<Vec3b>(Point(i, j)) = img1.at<Vec3b>(Point(i - SIDELINE_WIDTH, j - SIDELINE_WIDTH));
			}
			else if(i >= img1.cols + 2 * SIDELINE_WIDTH)
			{
				img3.at<Vec3b>(Point(i, j)) = img2.at<Vec3b>(Point(i - img1.cols - 2 * SIDELINE_WIDTH, j - SIDELINE_WIDTH));
			}
		}
	}
	
	//save image
	string fileOut = fileIn1;
	fileOut.insert(fileIn1.find('.'), "_two");
	imwrite(fileOut, img3);
	cout << "Done." << endl;

	//show image
	namedWindow(fileOut, CV_WINDOW_AUTOSIZE);
	imshow(fileOut, img3);
	waitKey(0);

	return 0;
}

string GetString(const string message)
{
	char* input = new char[256];
	
	cout << message;
	
	cin.getline(input, 256, '\n');
	string fileIn = input;
	
	delete [] input;
	
	return fileIn;
}