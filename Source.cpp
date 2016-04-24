/**
* @file BasicLinearTransforms.cpp
* @brief Simple program to change contrast and brightness
* @author OpenCV team
*/

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2\imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

double alpha; /**< Simple contrast control */
int beta;  /**< Simple brightness control */

		   /**
		   * @function main
		   * @brief Main function
		   */
int main(int, char** argv)
{
	/// Read image given by user
	Mat image = imread(argv[1]);
	Mat new_image = Mat::zeros(image.size(), image.type());

	//MyCode
	Size size(512, 512);
	Mat resized_image;
	Mat resized_sampleimage;
	resize(image, resized_image, size, 0, 0, INTER_LINEAR);
	resize(image, resized_sampleimage, size, 0, 0, INTER_NEAREST);
	//Lets practice! Have some fun ^^
	Mat test_image = Mat::zeros(512, 512, image.type());
	int gridSizeX = test_image.rows / image.rows,
		gridSizeY = test_image.cols / image.cols;
	//uchar(*pixel) = test_image.data;
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			//test_image.at<Vec3b>(i, j) = image.at<Vec3b>(i,j);
			test_image.at<Vec3b>(i * gridSizeX, j * gridSizeY).val[0] = image.at<Vec3b>(i, j).val[0];
			test_image.at<Vec3b>(i * gridSizeX, j * gridSizeY).val[1] = image.at<Vec3b>(i, j).val[1];
			test_image.at<Vec3b>(i * gridSizeX, j * gridSizeY).val[2] = image.at<Vec3b>(i, j).val[2];
			/*for (int gx = 0; gx < gridSizeX; gx++) {
				for (int gy = 0; gy < gridSizeY; gy++) {
					test_image.at<Vec3b>(i * gridSizeX + gx, j * gridSizeY + gy).val[0] = 
				}	 
			}*/
			/*int gx = i / test_image.rows * gridSizeX;
			int gy = j / test_image.rows * gridSizeY;
			(*pixel++) = *image.data;*/
		}
	}

	for (int i = 0; i < image.rows - 1; i++) {
		for (int j = 0; j < image.cols - 1; j++) {
			//Get grid vertices
			/*Vec3b c00 = test_image.at<Vec3b>(i * gridSizeX, j * gridSizeY + (gridSizeY - 1));
			Vec3b c10 = test_image.at<Vec3b>(i * gridSizeX + (gridSizeX - 1), j * gridSizeY + (gridSizeY - 1));
			Vec3b c01 = test_image.at<Vec3b>(i * gridSizeX, j * gridSizeY);
			Vec3b c11 = test_image.at<Vec3b>(i * gridSizeX + (gridSizeX - 1), j * gridSizeY);*/
			Vec3b c00 = image.at<Vec3b>(i, j + 1);
			Vec3b c10 = image.at<Vec3b>(i + 1, j + 1);
			Vec3b c01 = image.at<Vec3b>(i, j);
			Vec3b c11 = image.at<Vec3b>(i + 1, j);
			for (int gx = 0; gx <= gridSizeX; gx++) {
				for (int gy = 0; gy <= gridSizeY; gy++) {				
					//cout << "Testing: " << int(c00.val[0]) << " at " << i * gridSizeX << " " << j * gridSizeY + (gridSizeY - 1) << endl;
					//system("pause");
					//Fill grid
					int a_r = c00.val[0] * (1 - 0.05 * gx) + c10.val[0] * 0.05 * gx,
						a_g = c00.val[1] * (1 - 0.05 * gx) + c10.val[1] * 0.05 * gx,
						a_b = c00.val[2] * (1 - 0.05 * gx) + c10.val[2] * 0.05 * gx;
					int b_r = c01.val[0] * (1 - 0.05 * gx) + c11.val[0] * 0.05 * gx,
						b_g = c01.val[1] * (1 - 0.05 * gx) + c11.val[1] * 0.05 * gx,
						b_b = c01.val[2] * (1 - 0.05 * gx) + c11.val[2] * 0.05 * gx;
					int c_r = a_r * (1 - 0.05*gy) + b_r * 0.05*gy,
						c_g = a_g * (1 - 0.05*gy) + b_g * 0.05*gy,
						c_b = a_b * (1 - 0.05*gy) + b_b * 0.05*gy;
					//cout << "Testing value: " << c.val[0] << endl;
					test_image.at<Vec3b>(i * gridSizeX + gx, j * gridSizeY + gy).val[0] = c_r;
					test_image.at<Vec3b>(i * gridSizeX + gx, j * gridSizeY + gy).val[1] = c_g;
					test_image.at<Vec3b>(i * gridSizeX + gx, j * gridSizeY + gy).val[2] = c_b;
				}
			}
		}
	}

	/// Initialize values
	std::cout << " Basic Linear Transforms " << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "* Enter the alpha value [1.0-3.0]: "; std::cin >> alpha;
	std::cout << "* Enter the beta value [0-100]: "; std::cin >> beta;


	/// Do the operation new_image(i,j) = alpha*image(i,j) + beta
	/// Instead of these 'for' loops we could have used simply:
	/// image.convertTo(new_image, -1, alpha, beta);
	/// but we wanted to show you how to access the pixels :)
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
			}
		}
	}

	/// Create Windows
	namedWindow("Original Image", 1);
	namedWindow("New Image", 1);
	namedWindow("Resized Image", 1);
	//namedWindow("Resized sample Image", 1);

	/// Show stuff
	imshow("Original Image", image);
	/*imshow("New Image", new_image);*/
	imshow("New Image", test_image);
	imshow("Resized Image", resized_image);
	//imshow("Resized sample Image", resized_sampleimage);


	/// Wait until user press some key
	waitKey();
	return 0;
}
