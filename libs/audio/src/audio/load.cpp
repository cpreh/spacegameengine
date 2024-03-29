//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/exception.hpp>
#include <sge/audio/file.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/file_exception.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/file_unique_ptr.hpp>
#include <sge/audio/load.hpp>
#include <sge/audio/loader.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/loader_ref.hpp>
#include <sge/audio/optional_file_unique_ptr.hpp>
#include <sge/media/impl/load.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

sge::audio::optional_file_unique_ptr
sge::audio::load(sge::audio::loader_ref const _loader, std::filesystem::path const &_path)
{
  return sge::media::impl::load<sge::audio::file_unique_ptr, sge::audio::exception>(_loader, _path);
}
