//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_VF_ATTRIBUTE_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_VF_ATTRIBUTE_CONFIG_HPP_INCLUDED

#include <sge/opengl/ext.hpp>
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/vf/attribute_config_fwd.hpp> // IWYU pragma: keep
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sge::opengl::vf
{

class attribute_config
{
public:
  using gl_vertex_attrib_pointer = sge::opengl::fun_ref<PFNGLVERTEXATTRIBPOINTERPROC>;

  using gl_enable_vertex_attrib_array = sge::opengl::fun_ref<PFNGLENABLEVERTEXATTRIBARRAYPROC>;

  using gl_disable_vertex_attrib_array = sge::opengl::fun_ref<PFNGLDISABLEVERTEXATTRIBARRAYPROC>;

  FCPPT_DECLARE_STRONG_TYPEDEF(gl_enable_vertex_attrib_array, enable_vertex_attrib_array_type);
  FCPPT_DECLARE_STRONG_TYPEDEF(gl_disable_vertex_attrib_array, disable_vertex_attrib_array_type);

  attribute_config(
      gl_vertex_attrib_pointer, enable_vertex_attrib_array_type, disable_vertex_attrib_array_type);

  [[nodiscard]] gl_vertex_attrib_pointer vertex_attrib_pointer() const;

  [[nodiscard]] gl_enable_vertex_attrib_array enable_vertex_attrib_array() const;

  [[nodiscard]] gl_disable_vertex_attrib_array disable_vertex_attrib_array() const;

private:
  gl_vertex_attrib_pointer vertex_attrib_pointer_;

  gl_enable_vertex_attrib_array enable_vertex_attrib_array_;

  gl_disable_vertex_attrib_array disable_vertex_attrib_array_;
};

}

#endif
