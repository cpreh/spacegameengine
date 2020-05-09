//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/file.hpp>
#include <sge/audio/load_stream_result.hpp>
#include <sge/audio/loader.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/audio/multi_loader_parameters.hpp>
#include <sge/audio/loader_plugin/collection.hpp>
#include <sge/audio/loader_plugin/context.hpp>
#include <sge/audio/loader_plugin/iterator.hpp>
#include <sge/audio/loader_plugin/object.hpp>
#include <sge/audio/loader_plugin/traits.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/media/stream_unique_ptr.hpp>
#include <sge/media/impl/muxer_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::audio::multi_loader::multi_loader(
	sge::audio::multi_loader_parameters const &_param
)
:
	sge::audio::loader(),
	muxer_(
		_param
	)
{
}

sge::audio::load_stream_result
sge::audio::multi_loader::load_stream(
	sge::media::stream_unique_ptr &&_stream,
	sge::media::optional_extension const &_extension,
	sge::media::optional_name const &_name
)
{
	return
		muxer_.mux_stream(
			std::move(
				_stream
			),
			_extension,
			_name
		);
}

sge::media::extension_set
sge::audio::multi_loader::extensions() const
{
	return
		muxer_.extensions();
}

sge::audio::multi_loader::~multi_loader()
= default;
