//#include <opencv2/imgcodecs.hpp>
#include "image_processing/best_rect_fit/best_rect_fit.h"
//#include "dsa/string/string_dsa.h"
#include "dsa/dijkstra/dijkstra.h"
#include "dsa/dfs_bfs/dfs_bfs.h"

int main(int argc, char** argv)
{
	/*best_rect_fit b;
	cv::Mat image = cv::imread("D:\DeepLearning\Algorithms\Machine_Learning\data\blob_11.png");
	b.process(image);*/
	/*string_dsa dsa;
	dsa.reverse_string("Apple");*/

	// Creating a LinkedList object
	// Dijkstra d;
	// d.process();
	Dfs_Bfs dfs_bfs;
	dfs_bfs.process();
	
	
	
	

	return 0;
}
