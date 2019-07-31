//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_AUDIO_LOADER_HPP_INCLUDED
#define SGE_AUDIO_LOADER_HPP_INCLUDED

#include <sge/audio/load_stream_result_fwd.hpp>
#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/detail/symbol.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/media/stream_unique_ptr_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace audio
{

/**
\brief Interface class for loaders

For a short introduction to loading an audio file, see \ref audio_example.
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL loader
{
	FCPPT_NONCOPYABLE(
		loader
	);
protected:
	SGE_AUDIO_DETAIL_SYMBOL
	loader();
public:
	virtual
	sge::audio::load_stream_result
	load_stream(
		sge::media::stream_unique_ptr &&,
		sge::media::optional_extension const &,
		sge::media::optional_name const &
	) = 0;

	virtual
	sge::media::extension_set
	extensions() const = 0;

	SGE_AUDIO_DETAIL_SYMBOL
	virtual
	~loader();
};

}
}

#endif
