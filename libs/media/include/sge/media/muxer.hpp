//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MEDIA_MUXER_HPP_INCLUDED
#define SGE_MEDIA_MUXER_HPP_INCLUDED

#include <sge/media/extension_fwd.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/load_stream_result_fwd.hpp>
#include <sge/media/muxer_fwd.hpp>
#include <sge/media/muxer_parameters_fwd.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/media/stream_unique_ptr_fwd.hpp>
#include <sge/media/detail/muxer_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/optional/reference_fwd.hpp>


namespace sge
{
namespace media
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
	fcppt::optional::reference<
		System
	>
	optional_system_ref;

	typedef
	sge::media::load_stream_result<
		File
	>
	load_stream_result;

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
	typedef
	sge::media::detail::muxer<
		System,
		File
	>
	muxer_impl;

	typedef
	fcppt::unique_ptr<
		muxer_impl
	>
	muxer_impl_unique_ptr;

	muxer_impl_unique_ptr const impl_;
};

}
}

#endif
