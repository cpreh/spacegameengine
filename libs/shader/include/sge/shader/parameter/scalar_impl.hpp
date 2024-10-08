//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SHADER_PARAMETER_SCALAR_IMPL_HPP_INCLUDED
#define SGE_SHADER_PARAMETER_SCALAR_IMPL_HPP_INCLUDED

#include <sge/cg/parameter/scalar/set.hpp>
#include <sge/cg/program/object.hpp> // IWYU pragma: keep
#include <sge/cg/program/object_ref.hpp>
#include <sge/shader/parameter/name.hpp>
#include <sge/shader/parameter/scalar_decl.hpp> // IWYU pragma: export
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

template <typename ValueType>
sge::shader::parameter::scalar<ValueType>::scalar(
    sge::cg::program::object_ref const _program,
    sge::shader::parameter::name const &_name,
    value_type const _initial_value)
    : parameter_(_program.get().parameter(_name.get()))
{
  this->set(_initial_value);
}

template <typename ValueType>
void sge::shader::parameter::scalar<ValueType>::set(value_type const _scalar)
{
  using promoted_type = std::conditional_t<std::is_same_v<value_type, bool>, int, value_type>;

  sge::cg::parameter::scalar::set(parameter_.object(), static_cast<promoted_type>(_scalar));
}

namespace sge::shader::parameter
{
template <typename ValueType>
scalar<ValueType>::~scalar() = default;
}

#endif
