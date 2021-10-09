//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_DINPUT_JOYPAD_FF_SCOPED_DOWNLOAD_HPP_INCLUDED
#define SGE_DINPUT_JOYPAD_FF_SCOPED_DOWNLOAD_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/joypad/ff/scoped_download_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace dinput
{
namespace joypad
{
namespace ff
{

class scoped_download
{
  FCPPT_NONCOPYABLE(scoped_download);

public:
  explicit scoped_download(IDirectInputEffect &);

  ~scoped_download();

private:
  IDirectInputEffect &effect_;
};

}
}
}
}

#endif
