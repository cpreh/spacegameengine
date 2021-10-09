//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_CONTEXT_USE_HPP_INCLUDED
#define SGE_OPENGL_CONTEXT_USE_HPP_INCLUDED

#include <sge/opengl/context/dummy_parameter.hpp>
#include <sge/opengl/context/has_parameter.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/context/use_impl.hpp>
#include <fcppt/not.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::opengl::context
{

template <typename Type>
inline std::enable_if_t<fcppt::not_(sge::opengl::context::has_parameter<Type>::value), Type &>
use(sge::opengl::context::object_ref const _object)
{
  return sge::opengl::context::use_impl<Type>(_object, sge::opengl::context::dummy_parameter());
}

template <typename Type>
inline std::enable_if_t<sge::opengl::context::has_parameter<Type>::value, Type &>
use(sge::opengl::context::object_ref const _object, typename Type::parameter _parameter)
{
  return sge::opengl::context::use_impl<Type>(_object, _parameter);
}

}

#endif
