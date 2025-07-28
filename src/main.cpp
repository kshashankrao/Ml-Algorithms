//#include <opencv2/imgcodecs.hpp>
#include "image_processing/best_rect_fit/best_rect_fit.h"
//#include "dsa/string/string_dsa.h"
#include "dsa/data_structures/linked_list.h"

int main(int argc, char** argv)
{
	/*best_rect_fit b;
	cv::Mat image = cv::imread("D:\DeepLearning\Algorithms\Machine_Learning\data\blob_11.png");
	b.process(image);*/
	/*string_dsa dsa;
	dsa.reverse_string("Apple");*/

	// Creating a LinkedList object
	LinkedList<int> list;

	// Inserting nodes
	list.insert(4);
	list.insert(3);
	list.insert(2);
	list.insert(1);

	std::cout << "Elements of the list are: ";

	// Print the list
	list.print();
	

	return 0;
}
