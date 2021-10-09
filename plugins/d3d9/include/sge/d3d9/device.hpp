//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_DEVICE_HPP_INCLUDED
#define SGE_D3D9_DEVICE_HPP_INCLUDED

#include <sge/d3d9/d3d_device_unique_ptr.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/device_index.hpp>
#include <sge/d3d9/resource_manager.hpp>
#include <sge/d3d9/state/core/defaults_fwd.hpp>
#include <sge/d3d9/state/ffp/defaults_fwd.hpp>
#include <sge/d3d9/swapchain/d3d_unique_ptr.hpp>
#include <sge/d3d9/target/onscreen_fwd.hpp>
#include <sge/renderer/config.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/context/core_unique_ptr.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/context/ffp_unique_ptr.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_parameters_fwd.hpp>
#include <sge/renderer/depth_stencil_buffer/surface_unique_ptr.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/parameters_fwd.hpp>
#include <sge/renderer/display_mode/optional_fullscreen_fwd.hpp>
#include <sge/renderer/display_mode/optional_object_fwd.hpp>
#include <sge/renderer/index/buffer_parameters_fwd.hpp>
#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <sge/renderer/occlusion_query/object_unique_ptr.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/state/core/blend/object_unique_ptr.hpp>
#include <sge/renderer/state/core/blend/parameters_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/object_unique_ptr.hpp>
#include <sge/renderer/state/core/depth_stencil/parameters_fwd.hpp>
#include <sge/renderer/state/core/rasterizer/object_unique_ptr.hpp>
#include <sge/renderer/state/core/rasterizer/parameters_fwd.hpp>
#include <sge/renderer/state/core/sampler/object_unique_ptr.hpp>
#include <sge/renderer/state/core/sampler/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/alpha_test/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/alpha_test/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/clip_plane/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/clip_plane/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/fog/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/fog/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/light/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/material/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/material/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/misc/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/misc/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/sampler/parameters_fwd.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters_fwd.hpp>
#include <sge/renderer/target/base_ref.hpp>
#include <sge/renderer/target/offscreen_unique_ptr.hpp>
#include <sge/renderer/target/onscreen_fwd.hpp>
#include <sge/renderer/texture/cube_parameters_fwd.hpp>
#include <sge/renderer/texture/cube_unique_ptr.hpp>
#include <sge/renderer/texture/depth_stencil_parameters_fwd.hpp>
#include <sge/renderer/texture/depth_stencil_unique_ptr.hpp>
#include <sge/renderer/texture/planar_parameters_fwd.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>
#include <sge/renderer/texture/volume_unique_ptr.hpp>
#include <sge/renderer/vertex/buffer_parameters_fwd.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/declaration_parameters_fwd.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/event/base_fwd.hpp>
#include <awl/event/container.hpp>
#include <awl/timer/unique_ptr.hpp>
#include <awl/window/event/base_fwd.hpp>
#include <awl/window/event/resize_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/signal/auto_connection.hpp>

#if defined(SGE_RENDERER_HAVE_CG)
#include <sge/cg/context/object_fwd.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/profile/object_fwd.hpp>
#include <sge/cg/profile/shader_type_fwd.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/cg/program/object_ref.hpp>
#include <sge/cg/program/source.hpp>
#include <sge/renderer/cg/loaded_program_unique_ptr.hpp>
#include <sge/renderer/cg/loaded_texture_unique_ptr.hpp>
#include <sge/renderer/texture/base_ref.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#endif

namespace sge
{
namespace d3d9
{

class device : public sge::renderer::device::ffp
{
  FCPPT_NONCOPYABLE(device);

public:
  device(IDirect3D9 &, fcppt::log::object &, sge::renderer::device::parameters const &);

  ~device() override;

private:
  sge::renderer::context::core_unique_ptr begin_rendering(sge::renderer::target::base_ref) override;

  void end_rendering(sge::renderer::context::core &) override;

  sge::renderer::target::offscreen_unique_ptr create_target() override;

  sge::renderer::texture::planar_unique_ptr
  create_planar_texture(sge::renderer::texture::planar_parameters const &) override;

  sge::renderer::texture::depth_stencil_unique_ptr
  create_depth_stencil_texture(sge::renderer::texture::depth_stencil_parameters const &) override;

  sge::renderer::depth_stencil_buffer::surface_unique_ptr create_depth_stencil_surface(
      sge::renderer::depth_stencil_buffer::surface_parameters const &) override;

  sge::renderer::texture::volume_unique_ptr
  create_volume_texture(sge::renderer::texture::volume_parameters const &) override;

  sge::renderer::texture::cube_unique_ptr
  create_cube_texture(sge::renderer::texture::cube_parameters const &) override;

  sge::renderer::vertex::declaration_unique_ptr
  create_vertex_declaration(sge::renderer::vertex::declaration_parameters const &) override;

  sge::renderer::vertex::buffer_unique_ptr
  create_vertex_buffer(sge::renderer::vertex::buffer_parameters const &) override;

  sge::renderer::index::buffer_unique_ptr
  create_index_buffer(sge::renderer::index::buffer_parameters const &) override;

  sge::renderer::occlusion_query::object_unique_ptr create_occlusion_query() override;

  sge::renderer::state::core::blend::object_unique_ptr
  create_blend_state(sge::renderer::state::core::blend::parameters const &) override;

  sge::renderer::state::core::depth_stencil::object_unique_ptr create_depth_stencil_state(
      sge::renderer::state::core::depth_stencil::parameters const &) override;

  sge::renderer::state::core::rasterizer::object_unique_ptr
  create_rasterizer_state(sge::renderer::state::core::rasterizer::parameters const &) override;

  sge::renderer::state::core::sampler::object_unique_ptr
  create_sampler_state(sge::renderer::state::core::sampler::parameters const &) override;

#if defined(SGE_RENDERER_HAVE_CG)
  sge::cg::profile::object create_cg_profile(sge::cg::profile::shader_type) override;

  sge::cg::program::compile_options
  cg_compile_options(sge::cg::context::object const &, sge::cg::profile::object const &) override;

  sge::renderer::cg::loaded_program_unique_ptr
      load_cg_program(sge::cg::program::object_ref) override;

  sge::renderer::cg::loaded_texture_unique_ptr
  load_cg_texture(sge::cg::parameter::object const &, sge::renderer::texture::base_ref) override;

  sge::cg::program::source transform_cg_vertex_program(
      sge::renderer::vertex::declaration const &, sge::cg::program::source const &) override;
#endif

  sge::renderer::target::onscreen &onscreen_target() const override;

  sge::renderer::caps::device const &caps() const override;

  sge::renderer::display_mode::optional_object display_mode() const override;

  void fullscreen(sge::renderer::display_mode::optional_fullscreen const &) override;

  sge::renderer::display_mode::container display_modes() const override;

  sge::renderer::context::ffp_unique_ptr
      begin_rendering_ffp(sge::renderer::target::base_ref) override;

  void end_rendering_ffp(sge::renderer::context::ffp &) override;

  sge::renderer::state::ffp::alpha_test::object_unique_ptr
  create_alpha_test_state(sge::renderer::state::ffp::alpha_test::parameters const &) override;

  sge::renderer::state::ffp::clip_plane::object_unique_ptr
  create_clip_plane_state(sge::renderer::state::ffp::clip_plane::parameters const &) override;

  sge::renderer::state::ffp::fog::object_unique_ptr
  create_fog_state(sge::renderer::state::ffp::fog::parameters const &) override;

  sge::renderer::state::ffp::lighting::object_unique_ptr
  create_lighting_state(sge::renderer::state::ffp::lighting::parameters const &) override;

  sge::renderer::state::ffp::lighting::light::object_unique_ptr
  create_light_state(sge::renderer::state::ffp::lighting::light::parameters const &) override;

  sge::renderer::state::ffp::lighting::material::object_unique_ptr
  create_material_state(sge::renderer::state::ffp::lighting::material::parameters const &) override;

  sge::renderer::state::ffp::misc::object_unique_ptr
  create_misc_state(sge::renderer::state::ffp::misc::parameters const &) override;

  sge::renderer::state::ffp::sampler::object_unique_ptr
  create_ffp_sampler_state(sge::renderer::state::ffp::sampler::parameters const &) override;

  sge::renderer::state::ffp::transform::object_unique_ptr
  create_transform_state(sge::renderer::state::ffp::transform::parameters const &) override;

  template <typename Ptr>
  fcppt::unique_ptr<Ptr> add_resource(fcppt::unique_ptr<Ptr> &&);

  void reset();

  void reinit();

  void release();

  awl::event::container on_window_event(awl::window::event::base const &);

  awl::event::container on_system_event(awl::event::base const &);

  void on_resize(awl::window::event::resize const &);

  sge::d3d9::device_index const index_;

  sge::renderer::pixel_format::srgb const srgb_;

  sge::renderer::caps::device const caps_;

  D3DPRESENT_PARAMETERS present_parameters_;

  sge::d3d9::d3d_device_unique_ptr const device_;

  sge::d3d9::resource_manager resources_;

  sge::d3d9::swapchain::d3d_unique_ptr const swap_chain_;

  typedef fcppt::unique_ptr<sge::d3d9::target::onscreen> onscreen_target_unique_ptr;

  onscreen_target_unique_ptr const onscreen_target_;

  typedef fcppt::unique_ptr<sge::d3d9::state::core::defaults> core_defaults_unique_ptr;

  core_defaults_unique_ptr const core_defaults_;

  typedef fcppt::unique_ptr<sge::d3d9::state::ffp::defaults> ffp_defaults_unique_ptr;

  ffp_defaults_unique_ptr const ffp_defaults_;

  sge::renderer::display_mode::container const display_modes_;

  sge::window::object &window_;

  awl::timer::unique_ptr const draw_timer_;

  fcppt::signal::auto_connection const window_event_connection_;

  fcppt::signal::auto_connection const system_event_connection_;
};

}
}

#endif
