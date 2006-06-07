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
		SGECOREDLLAPI frames_counter();
		SGECOREDLLAPI void update();
		SGECOREDLLAPI std::string get_frames_str() const;
		SGECOREDLLAPI unsigned get_frames() const;
	};
}

#endif
