/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_AUDIO_ANGLE_HPP_INCLUDED
#define SGE_AUDIO_ANGLE_HPP_INCLUDED

#include <sge/audio/angle_fwd.hpp>
#include <sge/audio/point.hpp>
#include <sge/symbol.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

namespace sge
{
namespace audio
{

class angle
{
public:
	SGE_SYMBOL angle();

	SGE_SYMBOL angle(
		point const &forward,
		point const &up
	);

	SGE_SYMBOL point const &
	forward() const;

	SGE_SYMBOL void
	forward(
		point const &
	);

	SGE_SYMBOL point const
	up() const;

	SGE_SYMBOL void
	up(
		point const &
	);
private:
	point
		forward_,
		up_;
};

}
}

#endif
