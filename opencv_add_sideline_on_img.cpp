#include <iostream>
#include <cstring>

#include <opencv2/opencv.hpp>

#define SIDELINE_WIDTH 1

using namespace std;
using namespace cv;

string GetString(const string message);

int main()
{
	//get image name
	string fileIn = GetString("Please Enter the Image File Name: ");

	//load image
	Mat src = imread(fileIn, CV_LOAD_IMAGE_COLOR);
	if(!src.data)
	{
		cout << "Can't Find File!" << endl;
		system("pause");
		return -1;
	}

	//choose sideline color
	int sidelineColor;
	cout << endl;
	cout << "Please Choose the Sideline Color: " << endl;
	cout << " * 1. Black" << endl;
	cout << " * 2. White" << endl;
	cin >> sidelineColor;
	if(sidelineColor != 1 && sidelineColor != 2)
	{
		cout << "Wrong Color!" << endl;
		system("pause");
		return -1;
	}

	//set sideline width
	int sidelineWidth;
	cout << "Please Enter the Sideline Width: ";
	cin >> sidelineWidth;
	if(sidelineWidth <= 0)
	{
		cout << "Wrong Sideline Width!" << endl;
		system("pause");
		return -1;
	}

	cout << endl;
	cout << "Sideline Color: " << (sidelineColor == 1 ? "Black" : "White") << endl;
	cout << "Sideline Width: " << sidelineWidth << endl << endl;

	//add sideline
	int row = src.rows + 2 * sidelineWidth;
	int col = src.cols + 2 * sidelineWidth;
	Mat dst;
	if(sidelineColor == 1)
		dst = Mat(row, col, CV_8UC3, Scalar(0, 0, 0));
	else
		dst = Mat(row, col, CV_8UC3, Scalar(255, 255, 255));
	for(int j = sidelineWidth; j < row - sidelineWidth; ++j)
	{
		for(int i = sidelineWidth; i < col - sidelineWidth; ++i)
		{
			dst.at<Vec3b>(Point(i, j)) = src.at<Vec3b>(Point(i - sidelineWidth, j - sidelineWidth));
		}
	}

	//process output file name
	string fileOut = fileIn;
	fileOut.insert(fileOut.find('.', 0), "_sideline");

	//save image
	imwrite(fileOut, dst);
	cout << "Process Done." << endl;

	//show image
	namedWindow(fileOut, CV_WINDOW_AUTOSIZE);
	imshow(fileOut, dst);
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