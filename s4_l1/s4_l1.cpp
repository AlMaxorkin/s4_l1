/* 16. В трехмерном пространстве задана множество точек. Найти разбиение этого множества на два непересекающихся множества,
   чтобы их центры тяжести находились как можно ближе друг к другу.*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct point
{
	int x, y, z;
};

void print_set(vector<point> set)
{
	for (int i = 0; i < set.size(); i++)
	{
		cout << set[i].x <<  ", " << set[i].y << ", " << set[i].z << "; " << "\n";
	}
}

double distance(vector<point> set1, vector<point> set2)
{
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0, z1 = 0, z2 = 0;

	for (int i = 0; i < set1.size(); i++)
	{
		x1 += set1[i].x;
		y1 += set1[i].y;
		z1 += set1[i].z;
	}

	for (int i = 0; i < set2.size(); i++)
	{
		x2 += set2[i].x;
		y2 += set2[i].y;
		z2 += set2[i].z;
	}

	x1 = x1 / set1.size(), y1 = y1 / set1.size(), z1 = z1 / set1.size();
	x2 = x2 / set2.size(), y2 = y2 / set2.size(), z2 = z2 / set2.size();

	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
}

void backtracking(vector<vector<point>> &res, vector<point> main_set, vector<point> set1, vector<point> set2, int index, double & min_dist)
{
	for (int i = index; i < main_set.size(); i++)
	{
		set1.push_back(main_set[i]);
		set2.erase(set2.begin());
		
		if (!set1.empty() && !set2.empty())
		{
			if (distance(set1, set2) < min_dist)
			{
				res.clear();
				res.push_back(set1);
				res.push_back(set2);
			}
		}


		print_set(set1);
		cout << " / " << "\n";
		print_set(set2);
		cout << "\n";

		backtracking(res, main_set, set1, set2, i + 1, min_dist);
		
		set2.push_back(main_set[i]);
		set1.pop_back();
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	vector<vector<point>> res;
	vector<point> set ,set1, set2;
	double min_dist;
	
	point m1, m2, m3, m4;
	m1.x = 1;
	m1.y = 1;
	m1.z = 1;

	m2.x = 2;
	m2.y = 2;
	m2.z = 2;

	m3.x = 3;
	m3.y = 3;
	m3.z = 3;

	m4.x = 4;
	m4.y = 4;
	m4.z = 4;

	set.push_back(m1);
	set.push_back(m2);
	set.push_back(m3);
	set.push_back(m4);

	set1.push_back(set[0]);
	for (int i = 1; i < set.size(); i++)
		set2.push_back(set[i]);
	
	min_dist = distance(set1, set2);

	set1.clear();
	set2 = set;
	backtracking(res, set, set1, set2, 0, min_dist);
	

	cout << "Разбиение с минимальным расстоянием: " << min_dist << endl;
	print_set(res[0]);
	cout << "/" <<endl;
	print_set(res[1]);

	system("pause");
	return 0;
}