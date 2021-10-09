//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_WININPUT_CURSOR_PIXMAP_HPP_INCLUDED
#define SGE_WININPUT_CURSOR_PIXMAP_HPP_INCLUDED

#include <awl/backends/windows/windows.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace wininput
{
namespace cursor
{

class pixmap
{
  FCPPT_NONCOPYABLE(pixmap);

public:
  pixmap();

  ~pixmap();

  HCURSOR
  get() const;

private:
  HCURSOR cursor_;
};

}
}
}

#endif
