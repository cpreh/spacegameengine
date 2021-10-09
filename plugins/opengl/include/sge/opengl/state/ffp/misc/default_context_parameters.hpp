//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_STATE_FFP_MISC_DEFAULT_CONTEXT_PARAMETERS_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_MISC_DEFAULT_CONTEXT_PARAMETERS_HPP_INCLUDED

#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/state/ffp/misc/default_context_parameters_fwd.hpp>
#include <fcppt/log/object_reference.hpp>

namespace sge::opengl::state::ffp::misc
{

class default_context_parameters
{
public:
  default_context_parameters(fcppt::log::object_reference, sge::opengl::context::object_ref);

  [[nodiscard]] fcppt::log::object_reference log() const;

  [[nodiscard]] sge::opengl::context::object_ref context() const;

private:
  fcppt::log::object_reference log_;

  sge::opengl::context::object_ref context_;
};

}

#endif
