/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/audio/file_fwd.hpp>
#include <sge/audio/loader.hpp>
#include <sge/audio/multi_loader_fwd.hpp>
#include <sge/audio/multi_loader_parameters_fwd.hpp>
#include <sge/audio/load_stream_result_fwd.hpp>
#include <sge/audio/detail/symbol.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/muxer.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/media/stream_unique_ptr_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace audio
{

class SGE_CORE_DETAIL_CLASS_SYMBOL multi_loader
:
	public sge::audio::loader
{
	FCPPT_NONCOPYABLE(
		multi_loader
	);
public:
	SGE_AUDIO_DETAIL_SYMBOL
	explicit
	multi_loader(
		sge::audio::multi_loader_parameters const &
	);

	SGE_AUDIO_DETAIL_SYMBOL
	sge::audio::load_stream_result
	load_stream(
		sge::media::stream_unique_ptr &&,
		sge::media::optional_extension const &,
		sge::media::optional_name const &
	)
	override;

	SGE_AUDIO_DETAIL_SYMBOL
	sge::media::extension_set
	extensions() const
	override;

	SGE_AUDIO_DETAIL_SYMBOL
	~multi_loader()
	override;
private:
	typedef
	sge::media::muxer<
		sge::audio::loader,
		sge::audio::file
	>
	muxer;

	muxer muxer_;
};

}
}

#endif
