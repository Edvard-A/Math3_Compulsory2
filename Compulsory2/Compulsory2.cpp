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
	for (const auto& p : points) //why const?
	{
		// Compute all necessary sum
		Sx = points.at(0).x;
		Sy = points.at(0).y;
		Sxx = points.at(0).x * points.at(0).x;
		Sxy = points.at(0).x * points.at(0).y;
	}

	Beta1 = ((n * Sxy) - (Sx * Sy)) / ((n * Sxx) - (Sx * Sx));
	Beta0 = (Sy - (Beta1 * Sx)) / n;

}

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
	
	for (int i = 0; i < (((sizeof(points) - 2) * 2)); i++) 
	{
		std::cout << points[i].x << ", " << points[i].y << std::endl;
	}
}

int main()
{
	ReadFromFile("game_tech_least_squares_mixed.csv");

	return 0;
	/*std::vector<Point> points = { {1, 2}, {2, 2.8}, {3, 3.6}, {4, 4.5}, {5, 5.1} };
	double a, b;
	linearLeastSquares(points, a, b);
	std::cout << "Best fit line: y = " << a << "x + " << b << std::endl;*/
}