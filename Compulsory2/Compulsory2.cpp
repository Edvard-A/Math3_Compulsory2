#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::ifstream filein("dataPoints.txt");
//C:\\Users\\edvar\\Documents\\HINN\\Matematikk III\\Compulsory2\\dataPoints.txt

struct Point {
	double x, y;
};
// Function to compute linear least squares
void linearLeastSquares(std::vector<Point>& points, double& Beta0, double& Beta1) 
{
	int n = points.size();
	double Sx = 0, Sy = 0, Sxx = 0, Sxy = 0;
	//for (const auto& p : points)
	//{
	//	// Compute all necessary sum
	//}

	if (filein.is_open())
	{
		for (int i = 0; /*i < sizeof(points)*/ i < 60; i++)
		{
			std::string tempString;
			//filein.getline(filein, tempString);
			double tempX, tempY;
			Point tempPoint = { 0, 0 };
			//points[i].x;
			points.push_back(tempPoint);
		}
	}

	
}
	//Beta0 = // complete the code
	//	Beta1 = // complete the code
int main()
{
	ReadFromFile("game_tech_least_squares_mixed.csv");

	
	/*std::vector<Point> points = { {1, 2}, {2, 2.8}, {3, 3.6}, {4, 4.5}, {5, 5.1} };
	double a, b;
	linearLeastSquares(points, a, b);
	std::cout << "Best fit line: y = " << a << "x + " << b << std::endl;*/
	return 0;

}