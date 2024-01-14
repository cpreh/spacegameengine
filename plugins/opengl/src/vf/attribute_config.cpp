//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/vf/attribute_config.hpp>

sge::opengl::vf::attribute_config::attribute_config(
    gl_vertex_attrib_pointer _vertex_attrib_pointer,
    enable_vertex_attrib_array_type const _enable_vertex_attrib_array,
    disable_vertex_attrib_array_type const _disable_vertex_attrib_array)
    : vertex_attrib_pointer_{_vertex_attrib_pointer},
      enable_vertex_attrib_array_{_enable_vertex_attrib_array.get()},
      disable_vertex_attrib_array_{_disable_vertex_attrib_array.get()}
{
}

sge::opengl::vf::attribute_config::gl_vertex_attrib_pointer
sge::opengl::vf::attribute_config::vertex_attrib_pointer() const
{
  return vertex_attrib_pointer_;
}

sge::opengl::vf::attribute_config::gl_enable_vertex_attrib_array
sge::opengl::vf::attribute_config::enable_vertex_attrib_array() const
{
  return enable_vertex_attrib_array_;
}

sge::opengl::vf::attribute_config::gl_disable_vertex_attrib_array
sge::opengl::vf::attribute_config::disable_vertex_attrib_array() const
{
  return disable_vertex_attrib_array_;
}
