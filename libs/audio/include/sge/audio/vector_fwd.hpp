//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_AUDIO_VECTOR_FWD_HPP_INCLUDED
#define SGE_AUDIO_VECTOR_FWD_HPP_INCLUDED

#include <sge/audio/scalar.hpp>
#include <fcppt/math/vector/static_fwd.hpp>


namespace sge
{
namespace audio
{

typedef
fcppt::math::vector::static_<
	sge::audio::scalar,
	3
>
vector;

}
}

#endif
