//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/common.hpp>
#include <sge/opengl/occlusion_query/begin.hpp>
#include <sge/opengl/occlusion_query/config.hpp>
#include <sge/opengl/occlusion_query/const_config_ref.hpp>
#include <sge/opengl/occlusion_query/end.hpp>
#include <sge/opengl/occlusion_query/get_object_int.hpp>
#include <sge/opengl/occlusion_query/get_object_uint.hpp>
#include <sge/opengl/occlusion_query/object.hpp>
#include <sge/renderer/occlusion_query/blocking_wait.hpp>
#include <sge/renderer/occlusion_query/object.hpp>
#include <sge/renderer/occlusion_query/optional_pixel_count.hpp>
#include <sge/renderer/occlusion_query/pixel_count.hpp>

sge::opengl::occlusion_query::object::object(
    sge::opengl::occlusion_query::const_config_ref const _config)
    : sge::renderer::occlusion_query::object(), config_(_config), holder_(config_)
{
}

sge::opengl::occlusion_query::object::~object() = default;

void sge::opengl::occlusion_query::object::begin()
{
  sge::opengl::occlusion_query::begin(config_.get(), holder_.id());
}

void sge::opengl::occlusion_query::object::end()
{
  sge::opengl::occlusion_query::end(config_.get());
}

sge::renderer::occlusion_query::optional_pixel_count sge::opengl::occlusion_query::object::result(
    sge::renderer::occlusion_query::blocking_wait const _block) const
{
  return (sge::opengl::occlusion_query::get_object_int(
              config_.get(), holder_.id(), config_.get().query_result_available()) == GL_FALSE &&
          !_block.get())
             ? sge::renderer::occlusion_query::optional_pixel_count()
             : sge::renderer::occlusion_query::optional_pixel_count(
                   sge::renderer::occlusion_query::pixel_count(
                       sge::opengl::occlusion_query::get_object_uint(
                           config_.get(), holder_.id(), config_.get().query_result())));
}
