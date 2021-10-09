//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_LOCK_FLAGS_METHOD_HPP_INCLUDED
#define SGE_RENDERER_LOCK_FLAGS_METHOD_HPP_INCLUDED

#include <sge/renderer/lock_flags/method_fwd.hpp>

namespace sge::renderer::lock_flags
{

enum class method
{
  read,
  write,
  readwrite
};

}

#endif
