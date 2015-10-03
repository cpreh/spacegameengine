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


#ifndef SGE_VORBIS_FILE_HPP_INCLUDED
#define SGE_VORBIS_FILE_HPP_INCLUDED

#include <sge/audio/channel_type.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/sample_container_fwd.hpp>
#include <sge/audio/sample_count.hpp>
#include <sge/media/optional_name.hpp>
#include <sge/media/stream_unique_ptr.hpp>
#include <sge/vorbis/stream_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vorbis/codec.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace vorbis
{

class file
:
	public sge::audio::file
{
	FCPPT_NONCOPYABLE(
		file
	);
public:
	file(
		sge::media::stream_unique_ptr &&,
		sge::vorbis::stream_unique_ptr &&,
		sge::media::optional_name const &
	);

	sge::audio::sample_count
	read(
		sge::audio::sample_count,
		sge::audio::sample_container &
	)
	override;

	sge::audio::sample_count
	read_all(
		sge::audio::sample_container &
	)
	override;

	sge::audio::channel_type
	channels() const
	override;

	sge::audio::sample_count
	sample_rate() const
	override;

	sge::audio::sample_count
	bits_per_sample() const
	override;

	sge::audio::sample_count
	expected_package_size() const
	override;

	void
	reset()
	override;

	~file()
	override;
private:
	sge::media::optional_name const name_;

	sge::media::stream_unique_ptr const stdstream_;

	sge::vorbis::stream_unique_ptr const stream_;

	vorbis_info const info_;
};

}
}

#endif
