//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/convert/anisotropic_mip_filter.hpp>
#include <sge/opengl/state/core/sampler/actor.hpp>
#include <sge/opengl/state/core/sampler/actor_vector.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropic.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropy_context.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/funcs/parameter_int.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/parameters.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/optional/to_exception.hpp>

sge::opengl::state::core::sampler::actor_vector
sge::opengl::state::core::sampler::filter::anisotropic(
    sge::opengl::context::object_ref const _context,
    sge::renderer::state::core::sampler::filter::anisotropic::parameters const &_filter)
{
  return sge::opengl::state::core::sampler::actor_vector{
      sge::opengl::state::core::sampler::actor{[](sge::opengl::texture::binding const &_binding) {
        sge::opengl::texture::funcs::parameter_int(_binding, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      }},
      sge::opengl::state::core::sampler::actor{
          [mip = _filter.mip()](sge::opengl::texture::binding const &_binding)
          {
            sge::opengl::texture::funcs::parameter_int(
                _binding,
                GL_TEXTURE_MIN_FILTER,
                fcppt::cast::to_signed(sge::opengl::state::convert::anisotropic_mip_filter(mip)));
          }},
      sge::opengl::state::core::sampler::actor{
          [_context, level = _filter.level()](sge::opengl::texture::binding const &_binding)
          {
            sge::opengl::texture::funcs::parameter_int(
                _binding,
                fcppt::optional::to_exception(
                    sge::opengl::context::use<
                        sge::opengl::state::core::sampler::filter::anisotropy_context>(
                        _context, _context.get().info())
                        .config(),
                    []
                    {
                      return sge::renderer::unsupported{
                          FCPPT_TEXT("anisotropic filtering"),
                          FCPPT_TEXT(""),
                          FCPPT_TEXT("GL_EXT_texture_filter_anisotropic")};
                    })
                    .anisotropy_flag(),
                fcppt::cast::to_signed(level.get()));
          }}};
}
