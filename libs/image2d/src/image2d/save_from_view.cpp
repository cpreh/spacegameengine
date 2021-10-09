//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image2d/create_exn.hpp>
#include <sge/image2d/exception.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/save_from_view.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/media/path_to_extension.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

void sge::image2d::save_from_view(
    sge::image2d::system &_system,
    sge::image2d::view::const_object const &_view,
    std::filesystem::path const &_path)
{
  sge::image2d::create_exn(
      fcppt::make_ref(_system),
      _view,
      fcppt::optional::to_exception(
          sge::media::path_to_extension(_path),
          [&_path]
          {
            return sge::image2d::exception{
                FCPPT_TEXT("Path has no extension ") + fcppt::filesystem::path_to_string(_path)};
          }))
      ->save(_path);
}
