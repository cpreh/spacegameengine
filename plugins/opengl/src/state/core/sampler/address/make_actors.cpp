//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/state/convert/address_mode.hpp>
#include <sge/opengl/state/convert/address_mode_type.hpp>
#include <sge/opengl/state/core/sampler/actor.hpp>
#include <sge/opengl/state/core/sampler/address/make_actors.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/funcs/parameter_int.hpp>
#include <sge/renderer/state/core/sampler/address/parameters.hpp>
#include <fcppt/cast/to_signed.hpp>

namespace
{

template <typename Mode>
sge::opengl::state::core::sampler::actor set_one(Mode);

}

sge::opengl::state::core::sampler::actor_vector
sge::opengl::state::core::sampler::address::make_actors(
    sge::renderer::state::core::sampler::address::parameters const &_parameters)
{
  return sge::opengl::state::core::sampler::actor_vector{
      set_one(_parameters.mode_s()), set_one(_parameters.mode_t()), set_one(_parameters.mode_t())};
}

namespace
{

template <typename Mode>
sge::opengl::state::core::sampler::actor set_one(Mode const _mode)
{
  return sge::opengl::state::core::sampler::actor{
      [_mode](sge::opengl::texture::binding const &_binding)
      {
        sge::opengl::texture::funcs::parameter_int(
            _binding,
            sge::opengl::state::convert::address_mode_type<Mode>::get(),
            fcppt::cast::to_signed(sge::opengl::state::convert::address_mode(_mode.get())));
      }};
}

}
