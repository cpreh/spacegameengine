//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_AUDIO_DIRECTION_OBJECT_HPP_INCLUDED
#define SGE_AUDIO_DIRECTION_OBJECT_HPP_INCLUDED

#include <sge/audio/vector.hpp>
#include <sge/audio/detail/symbol.hpp>
#include <sge/audio/direction/forward.hpp>
#include <sge/audio/direction/up.hpp>


namespace sge
{
namespace audio
{
namespace direction
{

class object
{
public:
	SGE_AUDIO_DETAIL_SYMBOL
	object(
		sge::audio::direction::forward const &,
		sge::audio::direction::up const &
	);

	SGE_AUDIO_DETAIL_SYMBOL
	sge::audio::vector
	forward() const;

	SGE_AUDIO_DETAIL_SYMBOL
	void
	forward(
		sge::audio::vector const &
	);

	SGE_AUDIO_DETAIL_SYMBOL
	sge::audio::vector
	up() const;

	SGE_AUDIO_DETAIL_SYMBOL
	void
	up(
		sge::audio::vector const &
	);
private:
	sge::audio::vector
		forward_,
		up_;
};

}
}
}

#endif
