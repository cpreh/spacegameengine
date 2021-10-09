//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_BASIC_PARAMETERS_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_PARAMETERS_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/object_reference.hpp>

namespace sge::opengl::texture
{

class basic_parameters
{
public:
  basic_parameters(fcppt::log::object_reference, sge::opengl::context::object_ref);

  [[nodiscard]] fcppt::log::object &log() const;

  [[nodiscard]] sge::opengl::context::object &context() const;

private:
  fcppt::log::object_reference log_;

  sge::opengl::context::object_ref context_;
};

}

#endif
