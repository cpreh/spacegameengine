/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_AUDIO_MULTI_LOADER_HPP_INCLUDED
#define SGE_AUDIO_MULTI_LOADER_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/audio/file_ptr.hpp>
#include <sge/audio/loader.hpp>
#include <sge/audio/loader_capabilities_field.hpp>
#include <sge/audio/multi_loader_fwd.hpp>
#include <sge/audio/multi_loader_parameters_fwd.hpp>
#include <sge/audio/symbol.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/muxer.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/filesystem/path.hpp>


namespace sge
{
namespace audio
{

class SGE_CLASS_SYMBOL multi_loader
:
	public sge::audio::loader
{
	FCPPT_NONCOPYABLE(
		multi_loader
	);
public:
	SGE_AUDIO_SYMBOL
	explicit
	multi_loader(
		sge::audio::multi_loader_parameters const &
	);

	SGE_AUDIO_SYMBOL
	audio::file_ptr const
	load(
		fcppt::filesystem::path const &
	);

	SGE_AUDIO_SYMBOL
	audio::file_ptr const
	load_raw(
		sge::media::const_raw_range const &,
		sge::media::optional_extension const &
	);

	SGE_AUDIO_SYMBOL
	audio::loader_capabilities_field const
	capabilities() const;

	SGE_AUDIO_SYMBOL
	sge::media::extension_set const
	extensions() const;

	SGE_AUDIO_SYMBOL
	~multi_loader();
private:
	typedef sge::media::muxer<
		audio::loader,
		audio::loader_capabilities_field
	> muxer;

	muxer muxer_;
};

}
}

#endif
