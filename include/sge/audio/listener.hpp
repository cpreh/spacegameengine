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


#ifndef SGE_AUDIO_LISTENER_HPP_INCLUDED
#define SGE_AUDIO_LISTENER_HPP_INCLUDED

#include <sge/audio/point.hpp>
#include <sge/export.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace audio
{

class angle;

class SGE_CLASS_SYMBOL listener
{
	FCPPT_NONCOPYABLE(listener)
protected:
	SGE_SYMBOL listener();
public:
	virtual point const pos() const = 0;
	virtual void pos(point const &) = 0;
	virtual point const vel() const = 0;
	virtual void vel(point const &) = 0;
	virtual angle const direction() const = 0;
	virtual void direction(angle const &) = 0;
	SGE_SYMBOL virtual ~listener();
};

}
}

#endif
