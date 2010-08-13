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


#ifndef SGE_AUDIO_POOL_HPP_INCLUDED
#define SGE_AUDIO_POOL_HPP_INCLUDED

#include <sge/audio/stop_mode.hpp>
#include <sge/audio/sound/base_ptr.hpp>
#include <sge/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <vector>
#include <utility>

namespace sge
{
namespace audio
{
class SGE_CLASS_SYMBOL pool
{
	FCPPT_NONCOPYABLE(pool)
public:
	SGE_SYMBOL explicit 
	pool();

	SGE_SYMBOL void 
	add(
		sound::base_ptr,
		stop_mode::type);

	SGE_SYMBOL void 
	update();

	SGE_SYMBOL bool 
	sounds_finished() const;
private:
	typedef 
	std::pair<sound::base_ptr,stop_mode::type> 
	value_type;

	typedef 
	std::vector<value_type> 
	container_type;

	container_type sounds;
};

}
}

#endif
