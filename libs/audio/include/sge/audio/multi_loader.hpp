//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_AUDIO_MULTI_LOADER_HPP_INCLUDED
#define SGE_AUDIO_MULTI_LOADER_HPP_INCLUDED

#include <sge/audio/file_fwd.hpp>
#include <sge/audio/load_stream_result_fwd.hpp>
#include <sge/audio/loader.hpp>
#include <sge/audio/multi_loader_fwd.hpp>
#include <sge/audio/multi_loader_parameters_fwd.hpp>
#include <sge/audio/detail/symbol.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/muxer.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/media/stream_unique_ptr_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::audio
{

class SGE_CORE_DETAIL_CLASS_SYMBOL multi_loader
:
	public sge::audio::loader
{
	FCPPT_NONMOVABLE(
		multi_loader
	);
public:
	SGE_AUDIO_DETAIL_SYMBOL
	explicit
	multi_loader(
		sge::audio::multi_loader_parameters const &
	);

	[[nodiscard]]
	SGE_AUDIO_DETAIL_SYMBOL
	sge::audio::load_stream_result
	load_stream(
		sge::media::stream_unique_ptr &&,
		sge::media::optional_extension const &,
		sge::media::optional_name const &
	)
	override;

	[[nodiscard]]
	SGE_AUDIO_DETAIL_SYMBOL
	sge::media::extension_set
	extensions() const
	override;

	SGE_AUDIO_DETAIL_SYMBOL
	~multi_loader()
	override;
private:
	using
	muxer
	=
	sge::media::muxer<
		sge::audio::loader,
		sge::audio::file
	>;

	muxer muxer_;
};

}

#endif
