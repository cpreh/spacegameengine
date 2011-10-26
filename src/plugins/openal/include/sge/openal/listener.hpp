/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_OPENAL_LISTENER_HPP_INCLUDED
#define SGE_OPENAL_LISTENER_HPP_INCLUDED

#include <sge/audio/angle.hpp>
#include <sge/audio/listener.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/vector/basic_impl.hpp>


namespace sge
{
namespace openal
{
class listener
:
	public sge::audio::listener
{
	FCPPT_NONCOPYABLE(
		listener
	);
public:
	explicit
	listener();

	~listener();

	void
	position(
		audio::vector const &);

	audio::vector const
	position() const;

	void
	linear_velocity(
		audio::vector const &);

	audio::vector const
	linear_velocity() const;

	void
	direction(
		audio::angle const &);

	audio::angle const
	direction() const;
private:
	audio::vector position_;
	audio::vector linear_velocity_;
	audio::angle angle_;
};
}
}

#endif
