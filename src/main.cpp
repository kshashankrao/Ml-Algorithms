#include "image_processing_algorithms/rectangle_fitting/rect_fitting.h"
#include <memory>

int main()
{
	std::unique_ptr<RectFitting> rectFitting;
	
	rectFitting->process();
	
	return 0;
}