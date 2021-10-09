//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_OCCLUSION_QUERY_OBJECT_HPP_INCLUDED
#define SGE_D3D9_OCCLUSION_QUERY_OBJECT_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/query/d3d_unique_ptr.hpp>
#include <sge/renderer/occlusion_query/blocking_wait.hpp>
#include <sge/renderer/occlusion_query/object.hpp>
#include <sge/renderer/occlusion_query/optional_pixel_count_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace d3d9
{
namespace occlusion_query
{

class object : public sge::renderer::occlusion_query::object
{
  FCPPT_NONCOPYABLE(object);

public:
  explicit object(IDirect3DDevice9 &);

  ~object() override;

private:
  void begin() override;

  void end() override;

  sge::renderer::occlusion_query::optional_pixel_count
      result(sge::renderer::occlusion_query::blocking_wait) const override;

  sge::d3d9::query::d3d_unique_ptr const query_;
};

}
}
}

#endif
