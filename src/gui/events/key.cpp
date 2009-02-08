#include <sge/gui/events/key.hpp>
#include <sge/input/classification.hpp>
#include <sge/assert.hpp>

sge::gui::events::key::key(
	input::key_pair const &kp,
	input::modifier::states const &s,
	bool const repeated_) 
	: kp(kp),
    s(s),
	  repeated_(repeated_)
{
}
