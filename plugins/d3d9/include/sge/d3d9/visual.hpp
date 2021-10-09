//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_VISUAL_HPP_INCLUDED
#define SGE_D3D9_VISUAL_HPP_INCLUDED

#include <sge/renderer/visual_base.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/windows/visual/null_object.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace d3d9
{

class visual : public awl::backends::windows::visual::null_object, public sge::renderer::visual_base
{
  FCPPT_NONCOPYABLE(visual);

public:
  explicit visual(sge::renderer::pixel_format::object const &);

  ~visual();
};

}
}

#endif
