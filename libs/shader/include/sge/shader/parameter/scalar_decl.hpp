//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SHADER_PARAMETER_SCALAR_DECL_HPP_INCLUDED
#define SGE_SHADER_PARAMETER_SCALAR_DECL_HPP_INCLUDED

#include <sge/cg/parameter/is_int_float_double.hpp>
#include <sge/cg/parameter/named.hpp>
#include <sge/cg/program/object_ref.hpp>
#include <sge/shader/parameter/name.hpp>
#include <sge/shader/parameter/scalar_fwd.hpp> // IWYU pragma: keep
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::shader::parameter
{

template <typename ValueType>
class scalar
{
  FCPPT_NONMOVABLE(scalar);

public:
  static_assert(
      std::is_same_v<ValueType, bool> ||
          sge::cg::parameter::is_int_float_double<ValueType>::value,
      "Shader parameters must be either bool, int, float or double");

  using value_type = ValueType;

  scalar(sge::cg::program::object_ref, sge::shader::parameter::name const &, value_type);

  void set(value_type);

  ~scalar(); // NOLINT(performance-trivially-destructible)
private:
  sge::cg::parameter::named const parameter_;
};

}

#endif
