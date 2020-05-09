//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MEDIA_IMPL_DETAIL_MUXER_HPP_INCLUDED
#define SGE_MEDIA_IMPL_DETAIL_MUXER_HPP_INCLUDED

#include <sge/media/extension_fwd.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/load_stream_result_fwd.hpp>
#include <sge/media/muxer_parameters_fwd.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/media/stream_unique_ptr_fwd.hpp>
#include <sge/media/detail/muxer_fwd.hpp>
#include <sge/plugin/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/optional/reference_fwd.hpp>
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
	FCPPT_NONMOVABLE(
		muxer
	);
public:
	using
	system
	=
	System;

	using
	file
	=
	File;

	using
	parameters
	=
	sge::media::muxer_parameters<
		system
	>;

	using
	file_unique_ptr
	=
	fcppt::unique_ptr<
		file
	>;

	using
	load_stream_result
	=
	sge::media::load_stream_result<
		File
	>;

	using
	optional_system_ref
	=
	fcppt::optional::reference<
		System
	>;

	explicit
	muxer(
		parameters const &
	);

	~muxer();

	[[nodiscard]]
	load_stream_result
	mux_stream(
		sge::media::stream_unique_ptr &&,
		sge::media::optional_extension const &,
		sge::media::optional_name const &
	) const;

	[[nodiscard]]
	optional_system_ref
	mux_extension(
		sge::media::extension const &
	) const;

	[[nodiscard]]
	sge::media::extension_set
	extensions() const;
private:
	[[nodiscard]]
	load_stream_result
	mux_stream_try_all(
		sge::media::stream_unique_ptr &&,
		sge::media::optional_name const &
	) const;

	using
	plugin_type
	=
	sge::plugin::object<
		system
	>;

	using
	plugin_container
	=
	std::vector<
		plugin_type
	>;

	using
	system_unique_ptr
	=
	fcppt::unique_ptr<
		system
	>;

	using
	plugin_system_pair
	=
	std::pair<
		plugin_type,
		system_unique_ptr
	>;

	using
	plugin_system_pair_container
	=
	std::vector<
		plugin_system_pair
	>;

	fcppt::log::object log_;

	plugin_system_pair_container const plugins_;

	sge::media::extension_set const extensions_;
};

}
}
}

#endif
