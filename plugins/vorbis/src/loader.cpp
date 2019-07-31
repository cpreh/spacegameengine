//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/file.hpp>
#include <sge/audio/load_stream_result.hpp>
#include <sge/audio/loader.hpp>
#include <sge/log/default_parameters.hpp>
#include <sge/log/location.hpp>
#include <sge/media/check_extension.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/vorbis/file.hpp>
#include <sge/vorbis/loader.hpp>
#include <sge/vorbis/open.hpp>
#include <sge/vorbis/stream.hpp>
#include <sge/vorbis/stream_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::media::extension
extension()
{
	return
		sge::media::extension{
			fcppt::string{
				FCPPT_TEXT("ogg")
			}
		};
}

}

sge::vorbis::loader::loader(
	fcppt::log::context &_log_context
)
:
	sge::audio::loader(),
	log_{
		_log_context,
		sge::log::location(),
		sge::log::default_parameters(
			fcppt::log::name{
				FCPPT_TEXT("vorbis")
			}
		)
	}
{
}

sge::vorbis::loader::~loader()
{
}

sge::audio::load_stream_result
sge::vorbis::loader::load_stream(
	sge::media::stream_unique_ptr &&_stream,
	sge::media::optional_extension const &_extension,
	sge::media::optional_name const &_name
)
{
	return
		sge::media::check_extension(
			extension(),
			_extension
		)
		?
			fcppt::optional::maybe(
				sge::vorbis::open(
					*_stream
				),
				[
					&_stream
				]{
					return
						sge::audio::load_stream_result(
							std::move(
								_stream
							)
						);
				},
				[
					this,
					&_stream,
					&_name
				](
					sge::vorbis::stream_unique_ptr &&_vorbis_stream
				)
				{
					return
						sge::audio::load_stream_result{
							fcppt::unique_ptr_to_base<
								sge::audio::file
							>(
								fcppt::make_unique_ptr<
									sge::vorbis::file
								>(
									log_,
									std::move(
										_stream
									),
									std::move(
										_vorbis_stream
									),
									_name
								)
							)
						};
				}
			)
		:
			sge::audio::load_stream_result(
				std::move(
					_stream
				)
			)
		;
}

sge::media::extension_set
sge::vorbis::loader::extensions() const
{
	return
		sge::media::extension_set{
			extension()
		};
}
