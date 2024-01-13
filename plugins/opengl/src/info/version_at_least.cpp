//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version.hpp>
#include <sge/opengl/info/version_at_least.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <fcppt/config/external_end.hpp>

bool sge::opengl::info::version_at_least(
    sge::opengl::info::version const _version,
    sge::opengl::info::major_version const _major,
    sge::opengl::info::minor_version const _minor)
{
  return std::make_tuple(_version.major(), _version.minor()) >= std::make_tuple(_major, _minor);
}
