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
{
	int n = points.size();
	double Sx = 0, Sy = 0, Sxx = 0, Sxy = 0;
	for (const auto& p : points) //why const?
	{
		// Compute all necessary sum
		Sx = points.at(0).x;
		Sy = points.at(0).y;
		Sxx = points.at(0).x * points.at(0).x;
		Sxy = points.at(0).x * points.at(0).y;
	}

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
	Beta1 = ((n * Sxy) - (Sx * Sy)) / ((n * Sxx) - (Sx * Sx));
	Beta0 = (Sy - (Beta1 * Sx)) / n;

}

void ReadFromFile(const std::string& filename)
{
	std::vector<Point> points;
	std::ifstream file(filename);

	double tempDouble, tempX, tempY;

	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line)) 
	{
		Point tempPoint;
		std::vector<std::string> row;
		std::stringstream ss;
		std::string cell;

		std::cout << "current cell is: " << cell << std::endl;

		while (std::getline(ss, cell, ',')) {
			//tempDouble = stod(cell); // how to push this into a point
			//row.push_back(cell);
			std::cout << "curent cell is: " << cell << std::endl;
		}

		//std::cout << row.at(0);

		/*tempX = stod(row.at(0));
		tempY = stod(row.at(1));

		tempPoint = { tempX, tempY };
		points.push_back(tempPoint);*/
	}

	file.close();
	/*for (int i = 0; i < sizeof(points); i++)
	{
		std::cout << points.at(i).x << ", " << points.at(i).y << std::endl;
	}*/
}

int main()
{
	ReadFromFile("game_tech_least_squares_mixed.csv");

	
	/*std::vector<Point> points = { {1, 2}, {2, 2.8}, {3, 3.6}, {4, 4.5}, {5, 5.1} };
	double a, b;
	linearLeastSquares(points, a, b);
	std::cout << "Best fit line: y = " << a << "x + " << b << std::endl;*/
	return 0;

}