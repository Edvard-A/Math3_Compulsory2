#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <C:\Libraries\eigen-3.4.0\Eigen\Dense>

std::ifstream filein("dataPoints.txt");
//C:\\Users\\edvar\\Documents\\HINN\\Matematikk III\\Compulsory2\\dataPoints.txt

struct Point {
	double x, y;
};
// Function to compute linear least squares
void linearLeastSquares(std::vector<Point>& points, double& Beta1, double& Beta0)
{
	int n = points.size();
	/*std::cout << "size: " << points.size();
	std::cout << "n: " << n << std::endl;*/
	double Sx = 0, Sy = 0, Sxx = 0, Sxy = 0;
	for (const auto& p : points) //why const?
	{
		// Compute all necessary sum
		/*Sx = points.at(0).x;
		Sy = points.at(0).y;
		Sxx = points.at(0).x * points.at(0).x;
		Sxy = points.at(0).x * points.at(0).y;*/
		//std::cout << p.x << ", " << p.y << std::endl;
		Sx += p.x;
		Sy += p.y;
		Sxx += p.x * p.x;
		Sxy += p.x * p.y;
	}

	Beta1 = ((n * Sxy) - (Sx * Sy)) / ((n * Sxx) - (Sx * Sx));
	Beta0 = (Sy - (Beta1 * Sx)) / n;
}

void quadraticLeastSquares(const std::vector<Point>& points, double& a, double& b, double& c) {
	int n = points.size();
	double Sx = 0, Sy = 0, Sxx = 0, Sxxx = 0, Sxxxx = 0, Sxy = 0, Sxxy = 0;
	for (const auto& p : points) {
		Sx += p.x;
		Sy += p.y;
		Sxx += p.x * p.x;
		Sxxx += p.x * p.x * p.x;
		Sxxxx += p.x * p.x * p.x * p.x;
		Sxy += p.x * p.y;
		Sxxy += p.x * p.x * p.y;
	}
	// Solve using Eigen for Ax = B (Matrix Form)
	Eigen::Matrix3d A;
	Eigen::Vector3d B, X;
	A << Sxxxx, Sxxx, Sxx,
		Sxxx, Sxx, Sx,
		Sxx, Sx, n;
	B << Sxxy, Sxy, Sy;
	X = A.colPivHouseholderQr().solve(B);
	a = X(0);
	b = X(1);
	c = X(2);
}

double sum(const std::vector<std::string>& F, const std::vector<Point>& points) {
	double result = 0.0;

	for (const auto& point : points) {
		double temp = 1.0;

		for (const auto& var : F) {
			if (var == "x") {
				temp = point.x;
			}
			else if (var == "y") {
				temp = point.y;
			}
			else {
				throw std::invalid_argument("whoops " + var);
			}
		}

		result += temp;
	}
	return result;
}

//void chooseLinearOrQuad(const std::vector<Point>& p, double& a, double& b, double& c) {
//	double linearOrQuadThreshold = 0.005;
//	quadraticLeastSquares(p, a, b, c);
//	if (sqrt(a * a) < linearOrQuadThreshold) {
//		a = 0;
//		linearLeastSquares(p, a, b);
//		std::cout << "Best fit line for P1: y = " << a << "x + " << b << std::endl;
//	}
//	else {
//		std::cout << "Best fit curve for P1: y = " << a << "x^2 + " << b << "x + " << c << std::endl;
//	}
//}

// this function should definitely be split up into multiple processes
void ReadFromFile(const std::string& filename)
{
	std::vector<std::vector<std::string>> sPoints;  //vector of vectors of points as strings
	std::vector<Point> points;						// vector of points
	std::vector<std::string> tempVector;			// temporary vector to store single strings of points
	std::string tempString;
	std::string::size_type SZ;
	
	double tempX, tempY;
	Point tempPoint;

	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line)) 
	{
		std::vector<std::string> row;
		std::stringstream ss(line);
		std::string cell;

		while (std::getline(ss, cell, ',')) 
		{
			row.push_back(cell);
		}

		sPoints.push_back(row);
	}

	file.close();

	for (int i = 0; i < (((sizeof(sPoints) - 1) * 2) - 1); i++) 
	{
		for (int j = 0; j < 2; j++) 
		{
			if (j < 1) // when we get to the X point
			{
				tempString = sPoints[i][j] + " " + sPoints[i][j + 1]; // adds both points as one string
				tempVector.push_back(tempString);
			}
			
			
		}
	}

	

	// this loop could be its own function for a cleaner structure
	/// <summary> 
	///		loop that converts each element of the stringvector to doubles, storing them as temorary X and Y values, then creating a point with those coordinates and pushing it into the points vector
	/// </summary>
	for (int i = 1; i < (((sizeof(tempVector) - 1) * 2) - 1); i++)
	{
		tempX = std::stod(tempVector[i], &SZ);
		tempY = std::stod(tempVector[i].substr(SZ));
		tempPoint = { tempX, tempY };
		points.push_back(tempPoint);
	}

	std::cout << "points output: " << std::endl;
	for (int i = 0; i < points.size(); i++)
	{
		std::cout << points[i].x << ", " << points[i].y << std::endl;
	}

	
	
	/*for (int i = 0; i < points.size(); i++) 
	{
		std::cout << points[i].x << ", " << points[i].y << std::endl;
	}*/
	//std::cout << points.size() << std::endl;

	int maxY; // = findLargestYPoint(points)
	//double yThreshold = (maxY / 100) * 20; // 20% of max y value

	/// ERROR CALCULATION AND SEGMENTING

	const int errMargin = 30;

	double a, b, c;
	double y0, y1, deltaY;
	int breakpoint = 0;;

	int counter = 1;

	/*for (int i = 1; i < points.size(); i++) 
	{		
		y0 = points[i].y;
		y1 = points[i - 1].y;
		deltaY = y0 - y1;
		if (errMargin < deltaY) {

		}

		
	}*/
	
	std::cout << "\ndifferences: \n";
	while (counter < points.size())
	{
		y0 = points[counter].y;
		y1 = points[counter - 1].y;
		deltaY = y0 - y1;
		std::cout << deltaY << std::endl;
		if (errMargin < sqrt(deltaY * deltaY)) {
			std::cout << "breakpoint was met!" << std::endl;
			breakpoint = counter;

			break;
		}
		
		counter++;
	}

	std::cout << "\nbreakpoint is: " << breakpoint << std::endl;
	std::vector<Point> pointsS2;

	while (breakpoint < points.size()) {
		//pointsS2[i].push_back(points[i])
		tempX = points[breakpoint].x;
		tempY = points[breakpoint].y;
		tempPoint = { tempX, tempY };

		pointsS2.push_back(tempPoint);

		points.erase(points.begin() + breakpoint); // erases the current element from the vector
	}

	double linearOrQuadThreshold = 0.005;
	quadraticLeastSquares(points, a, b, c);
	if (sqrt(a * a) < linearOrQuadThreshold) {
		a = 0;
		linearLeastSquares(points, a, b);
		std::cout << "\nBest fit line for P1: y = " << a << "x + " << b << std::endl;
	}
	else {
		std::cout << "\nBest fit curve for P1: y = " << a << "x^2 + " << b << "x + " << c << std::endl;
	}

	quadraticLeastSquares(pointsS2, a, b, c);
	if (sqrt(a * a) < linearOrQuadThreshold) {
		a = 0;
		linearLeastSquares(pointsS2, a, b);
		std::cout << "\nBest fit line for P2: y = " << a << "x + " << b << std::endl;
	}
	else {
		std::cout << "\nBest fit curve for P2: y = " << a << "x^2 + " << b << "x + " << c << std::endl;
	}	
}

int main()
{
	ReadFromFile("game_tech_least_squares_mixed.csv");

	return 0;
}