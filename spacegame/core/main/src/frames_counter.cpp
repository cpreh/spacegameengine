#include <sstream>
#include "../frames_counter.hpp"

sge::frames_counter::frames_counter()
: t(1000),
  current_frames(0),
  display_frames(0)
{}

void sge::frames_counter::update()
{
	++current_frames;
	if(t.update())
	{
		display_frames = current_frames;
		current_frames = 0;
	}
}

std::string sge::frames_counter::get_frames_str() const
{
	std::ostringstream oss;
	oss << get_frames();
	return oss.str();
}
unsigned sge::frames_counter::get_frames() const { return display_frames; }
