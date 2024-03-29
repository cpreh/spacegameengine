//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_XRANDR_VERSION_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_VERSION_HPP_INCLUDED

#include <sge/opengl/xrandr/version_fwd.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep
#include <fcppt/io/ostream_fwd.hpp>

#undef major
#undef minor

namespace sge::opengl::xrandr
{

class version
{
public:
  FCPPT_DECLARE_STRONG_TYPEDEF(int, major_type);
  FCPPT_DECLARE_STRONG_TYPEDEF(int, minor_type);

  version(major_type, minor_type);

  [[nodiscard]] int major() const;

  [[nodiscard]] int minor() const;

private:
  int major_;

  int minor_;
};

bool operator<(sge::opengl::xrandr::version const &, sge::opengl::xrandr::version const &);

fcppt::io::ostream &operator<<(fcppt::io::ostream &, sge::opengl::xrandr::version const &);

}

#endif
