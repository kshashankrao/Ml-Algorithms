#include <math.h>    
#include <stdio.h>
#include "../../src/Points.h"

double euclidean_distance(Point p1, Point p2)
{
	float val = ((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y));
	double dist = sqrt(val);
	return dist;
}

int knn_doit(Point data_sequence[], Point data_point, int k, int *class_num)
{
	int class1 = 0, class2 = 0;
	int n = 17;
	for (int i = 0; i < n; i++)
	{
		double d = euclidean_distance(data_sequence[i], data_point);
		if (d < k)
		{
			data_sequence[i].knn = true;
			data_sequence[i].dist = d;
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (data_sequence[i].knn == true)
		{
			printf("%d", data_sequence[i].x);
			if (data_sequence[i].val == 0)
			{
				class1++;
			}
			else if (data_sequence[i].val == 1)
			{
				class2++;
			}
			else
			{
				return 0;
			}
		}
		*class_num = class1 > class2 ? 0 : 1;
		return 1;
	}
	
}