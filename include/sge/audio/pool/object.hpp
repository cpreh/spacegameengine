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


#ifndef SGE_AUDIO_POOL_OBJECT_HPP_INCLUDED
#define SGE_AUDIO_POOL_OBJECT_HPP_INCLUDED

#include <sge/audio/pool/stop_mode.hpp>
#include <sge/audio/pool/sound_data.hpp>
#include <sge/audio/pool/gain_factor.hpp>
#include <sge/audio/pool/pitch_factor.hpp>
#include <sge/audio/sound/base_ptr.hpp>
#include <sge/audio/symbol.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <vector>
#include <utility>

namespace sge
{
namespace audio
{
namespace pool
{
class SGE_CLASS_SYMBOL object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_AUDIO_SYMBOL explicit 
	object(
		pool::gain_factor const &,
		pool::pitch_factor const &);

	SGE_AUDIO_SYMBOL 
	~object();

	SGE_AUDIO_SYMBOL void 
	add(
		sound::base_ptr,
		pool::stop_mode::type);

	SGE_AUDIO_SYMBOL void 
	update();

	SGE_AUDIO_SYMBOL bool 
	sounds_finished() const;

	SGE_AUDIO_SYMBOL void
	gain_factor(
		pool::gain_factor::value_type);

	SGE_AUDIO_SYMBOL pool::gain_factor::value_type
	gain_factor() const;

	SGE_AUDIO_SYMBOL void
	pitch_factor(
		pool::pitch_factor::value_type);

	SGE_AUDIO_SYMBOL pool::pitch_factor::value_type
	pitch_factor() const;
private:
	typedef 
	std::vector<pool::sound_data> 
	container_type;

	container_type sounds_;
	pool::gain_factor::value_type gain_factor_;
	pool::pitch_factor::value_type pitch_factor_;
};

}
}
}

#endif
