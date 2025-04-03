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

/*std::vector<std::string>*/ void ReadFromFile(const std::string& filename)
{
	std::vector<std::vector<std::string>> sPoints;
	std::vector<Point> points;
	std::ifstream file(filename);

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
		std::string rowTest;
		std::string tempCell;
		std::stringstream ss(line);
		std::string cell;
		std::string::size_type sz;

		//std::cout << "current cell is: " << cell << std::endl;

		while (std::getline(ss, cell, ',')) {
			//tempDouble = stod(cell); // how to push this into a point
			row.push_back(cell);
			/*rowTest = cell;
			tempCell = rowTest;
			rowTest = tempCell + " " + cell;*/
			//std::cout << row.at(0) << std::endl;
			//std::cout << "cell was pushed into row\n";
			//std::cout << "curent cell is: " << cell << std::endl;
		}
		//rowTest = row.at(0) + " " + row.at(1);
		//std::cout << rowTest << std::endl;
		//std::cout << std::stod(rowTest, &sz);
		//std::cout << row.at(0) << std::endl;
		//std::cout << std::stod(row.at(0), &sz) << std::endl;;
		//std::cout << row.at(1) << std::endl;;

		//tempX = stod(row.at(0));
		//tempY = stod(row.at(1));

		//tempPoint = { tempX, tempY };
		//points.push_back(tempPoint);

		sPoints.push_back(row);
	}

	file.close();

	std::vector<std::string> testVector;
	std::string testString;
	std::string tempString;
	std::string::size_type SZ;

	//std::cout << (((sizeof(sPoints) - 1) * 2) - 1);

	for (int i = 0; i < (((sizeof(sPoints) - 1) * 2) - 1); i++) {
		for (int j = 0; j < 2; j++) {
			//std::cout << sPoints[1][1] << std::endl;
			if (j < 1) {
				testString = sPoints[i][j] + " " + sPoints[i][j + 1];
				//std::cout << sPoints[i][j] << " " << sPoints[i][j + 1] << std::endl;
				testVector.push_back(testString);
				

				//std::cout << testVector[i] << std::endl;
			}
			
			
		}
	}

	for (int i = 1; i < (((sizeof(testVector) - 1) * 2) - 1); i++) {
		tempX = std::stod(testVector[i], &SZ);
		tempY = std::stod(testVector[i].substr(SZ));
		tempPoint = { tempX, tempY };
		points.push_back(tempPoint);
	}
	std::cout << sizeof(testVector) << std::endl;
	std::cout << sizeof(points);
	for (int i = 0; i < (((sizeof(points) - 2) * 2)); i++) {
		std::cout << points[i].x << ", " << points[i].y << std::endl;
	}
	
	
	/*std::cout << std::stod(testVector.at(1), &SZ) << std::endl;
	std::cout << std::stod(testVector[1].substr(SZ));*/
	//testString = testVector[0];
	//std::cout << testString;

	/*for (const auto& row : sPoints) {
		for (const auto& cell : row) {
			std::cout << cell << '\t';
		}
		std::cout << std::endl;
	}*/
	/*for (int i = 0; i < sizeof(row); i++) {
		return row.at(i)
	}*/
	//return sPoints;
	
	/*for (int i = 0; i < sizeof(points); i++)
	{
		std::cout << points.at(i).x << ", " << points.at(i).y << std::endl;
	}*/
}

int main()
{
	ReadFromFile("game_tech_least_squares_mixed.csv");

	std::string numbers = ("23.2  89.2");
	std::string::size_type sz;

	double num1 = std::stod(numbers, &sz);
	double num2 = std::stod(numbers.substr(sz));

	/*std::cout << num1 << ", " << num2 << std::endl;
	std::cout << std::stod(numbers, &sz);*/

	
	/*std::vector<Point> points = { {1, 2}, {2, 2.8}, {3, 3.6}, {4, 4.5}, {5, 5.1} };
	double a, b;
	linearLeastSquares(points, a, b);
	std::cout << "Best fit line: y = " << a << "x + " << b << std::endl;*/
	return 0;

}