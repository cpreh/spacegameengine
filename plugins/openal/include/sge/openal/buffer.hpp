//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENAL_BUFFER_HPP_INCLUDED
#define SGE_OPENAL_BUFFER_HPP_INCLUDED

#include <sge/audio/buffer.hpp>
#include <sge/audio/file_fwd.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/nonpositional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_unique_ptr.hpp>
#include <sge/openal/buffer_holder.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace openal
{

class buffer
:
	public sge::audio::buffer
{
	FCPPT_NONCOPYABLE(
		buffer
	);
public:
	buffer(
		fcppt::log::object &,
		sge::audio::file &
	);

	sge::audio::sound::positional_unique_ptr
	create_positional(
		sge::audio::sound::positional_parameters const &
	)
	override;

	sge::audio::sound::base_unique_ptr
	create_nonpositional(
		sge::audio::sound::nonpositional_parameters const &
	)
	override;

	~buffer()
	override;
private:
	fcppt::log::object &log_;

	sge::openal::buffer_holder const holder_;
};

}
}

#endif
