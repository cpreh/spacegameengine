/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/audio/vector.hpp>
#include <sge/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

namespace sge
{
namespace audio
{

class SGE_CLASS_SYMBOL angle
{
public:
	SGE_SYMBOL angle();

	SGE_SYMBOL angle(
		vector const &forward,
		vector const &up
	);

	SGE_SYMBOL vector const &
	forward() const;

	SGE_SYMBOL void
	forward(
		vector const &
	);

	SGE_SYMBOL vector const
	up() const;

	SGE_SYMBOL void
	up(
		vector const &
	);
private:
	vector
		forward_,
		up_;
};

}
}

#endif
