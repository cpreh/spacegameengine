//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GDIFONT_DEVICE_CONTEXT_HPP_INCLUDED
#define SGE_GDIFONT_DEVICE_CONTEXT_HPP_INCLUDED

#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace gdifont
{

class device_context
{
  FCPPT_NONCOPYABLE(device_context);

public:
  device_context();

  ~device_context();

  HDC get() const;

private:
  HDC const hdc_;
};

}
}

#endif
