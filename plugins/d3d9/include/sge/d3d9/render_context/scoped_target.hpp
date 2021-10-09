//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_RENDER_CONTEXT_SCOPED_TARGET_HPP_INCLUDED
#define SGE_D3D9_RENDER_CONTEXT_SCOPED_TARGET_HPP_INCLUDED

#include <sge/d3d9/target/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace d3d9
{
namespace render_context
{

class scoped_target
{
  FCPPT_NONCOPYABLE(scoped_target);

public:
  explicit scoped_target(sge::d3d9::target::base &);

  ~scoped_target();

  sge::d3d9::target::base &target() const;

private:
  sge::d3d9::target::base &target_;
};

}
}
}

#endif
