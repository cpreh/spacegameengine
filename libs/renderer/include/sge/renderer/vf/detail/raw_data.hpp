//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VF_DETAIL_RAW_DATA_HPP_INCLUDED
#define SGE_RENDERER_VF_DETAIL_RAW_DATA_HPP_INCLUDED

#include <sge/renderer/vf/detail/raw_data_type.hpp>
#include <mizuiro/color/is_color.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/math/vector/is_vector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::vf::detail
{

template <typename T>
inline sge::renderer::vf::detail::raw_data_type<T> raw_data(T &_value)
  requires(fcppt::math::vector::is_vector<std::remove_const_t<T>>::value)
{
  return fcppt::cast::to_char_ptr<sge::renderer::vf::detail::raw_data_type<T>>(
      _value.storage().data());
}

template <typename T>
inline sge::renderer::vf::detail::raw_data_type<T> raw_data(T &_value)
  requires(std::is_fundamental_v<T>)
{
  return fcppt::cast::to_char_ptr<sge::renderer::vf::detail::raw_data_type<T>>(&_value);
}

template <typename T>
inline sge::renderer::vf::detail::raw_data_type<T> raw_data(T &_value)
  requires(mizuiro::color::is_color<std::remove_const_t<T>>::value)
{
  return fcppt::cast::to_char_ptr<sge::renderer::vf::detail::raw_data_type<T>>(_value.data());
}
}

#endif
