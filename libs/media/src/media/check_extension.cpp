//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/media/check_extension.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/optional_extension.hpp>
#include <fcppt/const.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep
#include <fcppt/optional/maybe.hpp>

bool sge::media::check_extension(
    sge::media::extension const &_extension, sge::media::optional_extension const &_opt_extension)
{
  return fcppt::optional::maybe(
      _opt_extension,
      fcppt::const_(true),
      [&_extension](sge::media::extension const &_other) { return _extension == _other; });
}
