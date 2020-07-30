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
#include <sge/media/stream_unique_ptr.hpp>
#include <sge/wave/file.hpp>
#include <sge/wave/info_fwd.hpp>
#include <sge/wave/loader.hpp>
#include <sge/wave/read_info.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_reference.hpp>
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
				FCPPT_TEXT("wav")
			}
		};
}

}

sge::wave::loader::loader(
	fcppt::log::context_reference const _log_context
)
:
	sge::audio::loader(),
	log_{
		_log_context,
		sge::log::location(),
		sge::log::default_parameters(
			fcppt::log::name{
				FCPPT_TEXT("wave")
			}
		)
	}
{
}

sge::wave::loader::~loader()
= default;

sge::audio::load_stream_result
sge::wave::loader::load_stream(
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
				sge::wave::read_info(
					log_,
					*_stream,
					_name
				),
				[
					&_stream
				]{
					return
						sge::audio::load_stream_result{
							std::move(
								_stream
							)
						};
				},
				[
					this,
					&_stream,
					&_name
				](
					sge::wave::info const &_info
				)
				{
					return
						sge::audio::load_stream_result{
							fcppt::unique_ptr_to_base<
								sge::audio::file
							>(
								fcppt::make_unique_ptr<
									sge::wave::file
								>(
									fcppt::make_ref(
										log_
									),
									std::move(
										_stream
									),
									_info,
									sge::media::optional_name{
										_name
									}
								)
							)
						};
				}
			)
		:
			sge::audio::load_stream_result{
				std::move(
					_stream
				)
			}
		;
}

sge::media::extension_set
sge::wave::loader::extensions() const
{
	return
		sge::media::extension_set{
			extension()
		};
}
