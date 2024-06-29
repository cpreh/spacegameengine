//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image2d/file.hpp>
#include <sge/image2d/load_stream_result.hpp>
#include <sge/image2d/optional_file_unique_ptr.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/libpng/extension.hpp>
#include <sge/libpng/file.hpp>
#include <sge/libpng/file_rep.hpp>
#include <sge/libpng/file_rep_from_stream.hpp>
#include <sge/libpng/file_rep_from_view.hpp>
#include <sge/libpng/is_png.hpp>
#include <sge/libpng/system.hpp>
#include <sge/log/location.hpp>
#include <sge/media/check_extension.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/media/stream_unique_ptr.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::libpng::system::system(fcppt::log::context_reference const _log_context)
    : sge::image2d::system(),
      log_{_log_context, sge::log::location(), fcppt::log::name{FCPPT_TEXT("libpng")}}
{
}

sge::libpng::system::~system() = default;

sge::image2d::load_stream_result sge::libpng::system::load_stream(
    sge::media::stream_unique_ptr &&_stream,
    sge::media::optional_extension const &_extension,
    sge::media::optional_name const &_name)
{
  return sge::media::check_extension(sge::libpng::extension(), _extension) &&
                 sge::libpng::is_png(*_stream)
             ? fcppt::optional::maybe(
                   sge::libpng::file_rep_from_stream(log_, *_stream, _name),
                   [&_stream] { return sge::image2d::load_stream_result{std::move(_stream)}; },
                   [this](sge::libpng::file_rep &&_rep)
                   {
                     return sge::image2d::load_stream_result{
                         fcppt::unique_ptr_to_base<sge::image2d::file>(
                             fcppt::make_unique_ptr<sge::libpng::file>(
                                 fcppt::make_ref(log_), std::move(_rep)))};
                   })
             : sge::image2d::load_stream_result{std::move(_stream)};
}

sge::image2d::optional_file_unique_ptr sge::libpng::system::create(
    sge::image2d::view::const_object const &_view, sge::media::extension const &_extension)
{
  return _extension == sge::libpng::extension()
             ? fcppt::optional::map(
                   sge::libpng::file_rep_from_view(_view),
                   [this](sge::libpng::file_rep &&_rep)
                   {
                     return fcppt::unique_ptr_to_base<sge::image2d::file>(
                         fcppt::make_unique_ptr<file>(fcppt::make_ref(log_), std::move(_rep)));
                   })
             : sge::image2d::optional_file_unique_ptr();
}

sge::media::extension_set sge::libpng::system::extensions() const
{
  return sge::media::extension_set{sge::libpng::extension()};
}
