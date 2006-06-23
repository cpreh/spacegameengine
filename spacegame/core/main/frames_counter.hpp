#ifndef SGE_FRAMES_COUNTER_HPP_INCLUDED
#define SGE_FRAMES_COUNTER_HPP_INCLUDED

#include "./timer.hpp"
#include <string>

namespace sge
{

class frames_counter {
private:
	timer t;
	unsigned current_frames;
	unsigned display_frames;
public:
	frames_counter();
	void update();
	std::string frames_str() const;
	unsigned frames() const;
};

}

#endif
