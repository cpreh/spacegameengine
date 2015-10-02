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


#ifndef SGE_SRC_MEDIA_DETAIL_MUXER_HPP_INCLUDED
#define SGE_SRC_MEDIA_DETAIL_MUXER_HPP_INCLUDED

#include <sge/media/extension_fwd.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/load_stream_result_fwd.hpp>
#include <sge/media/muxer_parameters_fwd.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/media/stream_unique_ptr_fwd.hpp>
#include <sge/media/detail/muxer_fwd.hpp>
#include <sge/plugin/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_fwd.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace media
{
namespace detail
{

template<
	typename System,
	typename File
>
class muxer
{
	FCPPT_NONCOPYABLE(
		muxer
	);
public:
	typedef
	System
	system;

	typedef
	File
	file;

	typedef
	sge::media::muxer_parameters<
		system
	>
	parameters;

	typedef
	fcppt::unique_ptr<
		file
	>
	file_unique_ptr;

	typedef
	sge::media::load_stream_result<
		File
	>
	load_stream_result;

	typedef
	fcppt::optional<
		System &
	>
	optional_system_ref;

	explicit
	muxer(
		parameters const &
	);

	~muxer();

	load_stream_result
	mux_stream(
		sge::media::stream_unique_ptr &&,
		sge::media::optional_extension const &,
		sge::media::optional_name const &
	) const;

	optional_system_ref
	mux_extension(
		sge::media::extension const &
	) const;

	sge::media::extension_set
	extensions() const;
private:
	load_stream_result
	mux_stream_try_all(
		sge::media::stream_unique_ptr &&,
		sge::media::optional_name const &
	) const;

	typedef
	sge::plugin::object<
		system
	>
	plugin_type;

	typedef
	std::vector<
		plugin_type
	>
	plugin_container;

	typedef
	fcppt::unique_ptr<
		system
	>
	system_unique_ptr;

	typedef
	std::pair<
		plugin_type,
		system_unique_ptr
	>
	plugin_system_pair;

	typedef
	std::vector<
		plugin_system_pair
	>
	plugin_system_pair_container;

	plugin_system_pair_container const plugins_;

	sge::media::extension_set const extensions_;
};

}
}
}

#endif
