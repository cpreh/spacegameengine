//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_INFO_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_INFO_CONTEXT_HPP_INCLUDED

#include <sge/opengl/backend/const_current_ref.hpp>
#include <sge/opengl/backend/fun_ptr.hpp>
#include <sge/opengl/info/context_fwd.hpp>
#include <sge/opengl/info/extension_set.hpp>
#include <sge/opengl/info/version.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace sge::opengl::info
{

class context
{
  FCPPT_NONMOVABLE(context);

public:
  context(
      fcppt::log::object &, // NOLINT(google-runtime-references)
      sge::opengl::backend::const_current_ref);

  ~context();

  [[nodiscard]] sge::opengl::info::version version() const;

  [[nodiscard]] sge::opengl::info::extension_set const &extensions() const;

  [[nodiscard]] sge::opengl::backend::fun_ptr load_function(std::string const &) const;

private:
  sge::opengl::backend::const_current_ref const current_;

  sge::opengl::info::version const version_;

  sge::opengl::info::extension_set const extensions_;
};

}

#endif
