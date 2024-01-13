//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_VF_ATTRIBUTE_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_VF_ATTRIBUTE_CONFIG_HPP_INCLUDED

#include <sge/opengl/ext.hpp>
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/vf/attribute_config_fwd.hpp> // IWYU pragma: keep

namespace sge::opengl::vf
{

class attribute_config
{
public:
  using gl_vertex_attrib_pointer = sge::opengl::fun_ref<PFNGLVERTEXATTRIBPOINTERPROC>;

  using gl_enable_vertex_attrib_array = sge::opengl::fun_ref<PFNGLENABLEVERTEXATTRIBARRAYPROC>;

  using gl_disable_vertex_attrib_array = sge::opengl::fun_ref<PFNGLDISABLEVERTEXATTRIBARRAYPROC>;

  attribute_config(
      gl_vertex_attrib_pointer, gl_enable_vertex_attrib_array, gl_disable_vertex_attrib_array);

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
