/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_AUDIO_NULL_LISTENER_HPP_INCLUDED
#define SGE_AUDIO_NULL_LISTENER_HPP_INCLUDED

#include <sge/audio/listener.hpp>
#include <sge/audio/angle.hpp>
#include <sge/math/vector/basic_decl.hpp>

namespace sge
{
namespace audio_null
{

class listener : public audio::listener {
public:
	listener();
	audio::point const pos() const;
	void pos(audio::point const &);
	audio::point const vel() const;
	void vel(audio::point const &);
	audio::angle const direction() const;
	void direction(audio::angle const &);
private:
	audio::point
		pos_,
		vel_;
	audio::angle direction_;
};

}
}

#endif
