//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_DRAW_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_DRAW_CONTEXT_HPP_INCLUDED

#include <sge/opengl/ext.hpp> // IWYU pragma: keep
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/fun_ref_value_type.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/info/context_fwd.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/optional/reference.hpp>

namespace sge::opengl
{

class draw_context : public sge::opengl::context::base
{
  FCPPT_NONMOVABLE(draw_context);

public:
  using parameter = sge::opengl::info::context const &;

  explicit draw_context(sge::opengl::info::context const &);

  ~draw_context() override;

  using gl_draw_range_elements = sge::opengl::fun_ref<PFNGLDRAWRANGEELEMENTSPROC>;

  using optional_draw_range_elements =
      fcppt::optional::reference<sge::opengl::fun_ref_value_type<gl_draw_range_elements>>;

  using draw_range_elements_ref = optional_draw_range_elements::value_type;

  [[nodiscard]] optional_draw_range_elements draw_range_elements() const;

  static sge::opengl::context::id const static_id;

private:
  optional_draw_range_elements const draw_range_elements_;
};

}

#endif
