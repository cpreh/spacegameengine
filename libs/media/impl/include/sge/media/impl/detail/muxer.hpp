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
#include <fcppt/noncopyable.hpp>
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
	fcppt::optional::reference<
		System
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

	fcppt::log::object log_;

	plugin_system_pair_container const plugins_;

	sge::media::extension_set const extensions_;
};

}
}
}

#endif
