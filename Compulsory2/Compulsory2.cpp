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
	std::vector<std::vector<std::string>> sPoints;
	std::vector<Point> points;
	std::vector<std::string> testVector;
	std::ifstream file(filename);
	std::string testString;
	std::string::size_type SZ;

	double tempDouble, tempX, tempY;
	Point tempPoint;

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
				testString = sPoints[i][j] + " " + sPoints[i][j + 1]; // adds both points as one string
				testVector.push_back(testString);
			}
			
			
		}
	}

	// this loop could be its own function for a cleaner structure
	/// <summary> 
	///		loop that converts each element of the stringvector to doubles, storing them as temorary X and Y values, then creating a point with those coordinates and pushing it into the points vector
	/// </summary>
	for (int i = 1; i < (((sizeof(testVector) - 1) * 2) - 1); i++) 
	{
		tempX = std::stod(testVector[i], &SZ);
		tempY = std::stod(testVector[i].substr(SZ));
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

}