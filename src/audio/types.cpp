#include <sge/audio/types.hpp>
#include <sge/math/vector.hpp>

sge::audio::angle::angle()
	: forward(no_initialization_tag()),
	  up(no_initialization_tag())
{
}

sge::audio::angle::angle(point const &forward,point const &up)
	: forward(forward),
	  up(up)
{
}
