//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_OCCLUSION_QUERY_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_OCCLUSION_QUERY_CONFIG_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/occlusion_query/config_fwd.hpp>

namespace sge::opengl::occlusion_query
{

class config
{
public:
  using gl_gen_queries = sge::opengl::fun_ref<PFNGLGENQUERIESPROC>;

  using gl_delete_queries = sge::opengl::fun_ref<PFNGLDELETEQUERIESPROC>;

  using gl_begin_query = sge::opengl::fun_ref<PFNGLBEGINQUERYPROC>;

  using gl_end_query = sge::opengl::fun_ref<PFNGLENDQUERYPROC>;

  using gl_get_query_object_iv = sge::opengl::fun_ref<PFNGLGETQUERYOBJECTIVPROC>;

  using gl_get_query_object_uiv = sge::opengl::fun_ref<PFNGLGETQUERYOBJECTUIVPROC>;

  config(
      gl_gen_queries,
      gl_delete_queries,
      gl_begin_query,
      gl_end_query,
      gl_get_query_object_iv,
      gl_get_query_object_uiv,
      GLenum samples_target_,
      GLenum query_result_available_,
      GLenum query_result_);

  [[nodiscard]] gl_gen_queries gen_queries() const;

  [[nodiscard]] gl_delete_queries delete_queries() const;

  [[nodiscard]] gl_begin_query begin_query() const;

  [[nodiscard]] gl_end_query end_query() const;

  [[nodiscard]] gl_get_query_object_iv get_query_object_iv() const;

  [[nodiscard]] gl_get_query_object_uiv get_query_object_uiv() const;

  [[nodiscard]] GLenum samples_target() const;

  [[nodiscard]] GLenum query_result_available() const;

  [[nodiscard]] GLenum query_result() const;

private:
  gl_gen_queries gen_queries_;

  gl_delete_queries delete_queries_;

  gl_begin_query begin_query_;

  gl_end_query end_query_;

  gl_get_query_object_iv get_query_object_iv_;

  gl_get_query_object_uiv get_query_object_uiv_;

  GLenum samples_target_;

  GLenum query_result_available_;

  GLenum query_result_;
};

}

#endif
