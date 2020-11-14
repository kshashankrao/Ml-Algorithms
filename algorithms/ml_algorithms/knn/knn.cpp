#include <math.h>    
#include <stdio.h>
#include <assert.h>
#include "../../../src/Points.h"

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

void get_input_point_data(Point* arr)
{
	arr[0].x = 1;
	arr[0].y = 12;
	arr[0].val = 0;

	arr[1].x = 2;
	arr[1].y = 5;
	arr[1].val = 0;

	arr[2].x = 5;
	arr[2].y = 3;
	arr[2].val = 1;

	arr[3].x = 3;
	arr[3].y = 2;
	arr[3].val = 1;

	arr[4].x = 3;
	arr[4].y = 6;
	arr[4].val = 0;

	arr[5].x = 1.5;
	arr[5].y = 9;
	arr[5].val = 1;

	arr[6].x = 7;
	arr[6].y = 2;
	arr[6].val = 1;

	arr[7].x = 6;
	arr[7].y = 1;
	arr[7].val = 1;

	arr[8].x = 3.8;
	arr[8].y = 3;
	arr[8].val = 1;

	arr[9].x = 3;
	arr[9].y = 10;
	arr[9].val = 0;

	arr[10].x = 5.6;
	arr[10].y = 4;
	arr[10].val = 1;

	arr[11].x = 4;
	arr[11].y = 2;
	arr[11].val = 1;

	arr[12].x = 3.5;
	arr[12].y = 8;
	arr[12].val = 0;

	arr[13].x = 2;
	arr[13].y = 11;
	arr[13].val = 0;

	arr[14].x = 2;
	arr[14].y = 5;
	arr[14].val = 1;

	arr[15].x = 2;
	arr[15].y = 9;
	arr[15].val = 0;

	arr[16].x = 1;
	arr[16].y = 7;
	arr[16].val = 0;
}

/* Example main fn*/
int knn_main()
{
	Point input_points[17]; /* Data sample*/
	Point p; /* Test point to be classified*/
	int ret;
	int class_num = 2; /* Total number of classes*/
	int class_name = class_num;
	get_input_point_data(input_points);
	p.x = 2.5;
	p.y = 7;
	ret = knn_doit(input_points, p, 3, &class_name);
	assert(class_name < class_num);
	printf("%d", class_name);
	return 0;
}