#include <sge/audio/types.hpp>

sge::audio::angle::angle()
{
}

sge::audio::angle::angle(point const &forward,point const &up)
	: forward(forward),
	  up(up)
{
}
