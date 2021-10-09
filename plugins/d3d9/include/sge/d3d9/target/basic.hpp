//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_TARGET_BASIC_HPP_INCLUDED
#define SGE_D3D9_TARGET_BASIC_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/target/base.hpp>
#include <sge/renderer/caps/target_surface_indices.hpp>
#include <sge/renderer/clear/parameters_fwd.hpp>
#include <sge/renderer/target/scissor_area.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace d3d9
{
namespace target
{

template <typename Base>
class basic : public Base, public sge::d3d9::target::base
{
  FCPPT_NONCOPYABLE(basic);

protected:
  basic(
      IDirect3DDevice9 &,
      sge::renderer::target::viewport const &,
      sge::renderer::caps::target_surface_indices);

public:
  ~basic() override;

private:
  void viewport(sge::renderer::target::viewport const &) override;

  sge::renderer::target::viewport viewport() const override;

  void scissor_area(sge::renderer::target::scissor_area const &) override;

  sge::renderer::target::scissor_area scissor_area() const override;

  void clear(sge::renderer::clear::parameters const &) override;

  void active(bool) override;

protected:
  IDirect3DDevice9 &device() const;

private:
  void check_viewport();

  void check_scissor_area();

  virtual void on_activate() = 0;

  virtual void on_deactivate() = 0;

  IDirect3DDevice9 &device_;

  sge::renderer::caps::target_surface_indices const max_surfaces_;

  bool active_;

  sge::renderer::target::viewport viewport_;

  sge::renderer::target::scissor_area scissor_area_;
};

}
}
}

#endif
