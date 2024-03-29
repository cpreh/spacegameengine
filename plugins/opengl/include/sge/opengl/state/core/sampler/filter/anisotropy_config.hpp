//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_STATE_CORE_SAMPLER_FILTER_ANISOTROPY_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_SAMPLER_FILTER_ANISOTROPY_CONFIG_HPP_INCLUDED

#include <sge/opengl/state/core/sampler/filter/anisotropy_config_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sge::opengl::state::core::sampler::filter
{

class anisotropy_config
{
public:
  FCPPT_DECLARE_STRONG_TYPEDEF(GLenum, anisotropy_flag_type);
  FCPPT_DECLARE_STRONG_TYPEDEF(GLenum, max_anisotropy_flag_type);

  anisotropy_config(anisotropy_flag_type, max_anisotropy_flag_type);

  [[nodiscard]] GLenum anisotropy_flag() const;

  [[nodiscard]] GLenum max_anisotropy_flag() const;

private:
  GLenum anisotropy_flag_;

  GLenum max_anisotropy_flag_;
};

}

#endif
