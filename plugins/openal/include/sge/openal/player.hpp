//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENAL_PLAYER_HPP_INCLUDED
#define SGE_OPENAL_PLAYER_HPP_INCLUDED

#include <sge/audio/buffer_unique_ptr.hpp>
#include <sge/audio/file_fwd.hpp>
#include <sge/audio/listener_fwd.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_unique_ptr.hpp>
#include <sge/openal/context.hpp>
#include <sge/openal/current_context.hpp>
#include <sge/openal/device.hpp>
#include <sge/openal/listener.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/object.hpp>


namespace sge
{
namespace openal
{

class player
:
	public sge::audio::player
{
	FCPPT_NONCOPYABLE(
		player
	);
public:
	explicit
	player(
		fcppt::log::context &
	);

	~player()
	override;

	sge::audio::listener &
	listener()
	override;

	void
	speed_of_sound(
		sge::audio::scalar
	)
	override;

	void
	doppler_factor(
		sge::audio::scalar
	)
	override;

	void
	gain(
		sge::audio::scalar
	)
	override;

	sge::audio::buffer_unique_ptr
	create_buffer(
		sge::audio::file &
	)
	override;

	sge::audio::sound::positional_unique_ptr
	create_positional_stream(
		sge::audio::file &,
		sge::audio::sound::positional_parameters const &
	)
	override;

	sge::audio::sound::base_unique_ptr
	create_nonpositional_stream(
		sge::audio::file &,
		sge::audio::sound::nonpositional_parameters const &
	)
	override;

	bool
	is_null() const
	override;
private:
	fcppt::log::object log_;

	sge::openal::device device_;

	sge::openal::context context_;

	sge::openal::current_context current_context_;

	sge::openal::listener listener_;
};

}
}

#endif
