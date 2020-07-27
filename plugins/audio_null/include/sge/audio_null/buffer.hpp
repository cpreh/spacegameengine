//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_AUDIO_NULL_BUFFER_HPP_INCLUDED
#define SGE_AUDIO_NULL_BUFFER_HPP_INCLUDED

#include <sge/audio/buffer.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/nonpositional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace audio_null
{

class buffer
:
	public sge::audio::buffer
{
	FCPPT_NONMOVABLE(
		buffer
	);
public:
	buffer();

	~buffer()
	override;
private:
	[[nodiscard]]
	sge::audio::sound::positional_unique_ptr
	create_positional(
		sge::audio::sound::positional_parameters const &
	)
	override;

	[[nodiscard]]
	sge::audio::sound::base_unique_ptr
	create_nonpositional(
		sge::audio::sound::nonpositional_parameters const &
	)
	override;
};

}
}

#endif
