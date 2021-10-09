//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_DINPUT_DEVICE_ADD_ELEMENT_HPP_INCLUDED
#define SGE_DINPUT_DEVICE_ADD_ELEMENT_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace dinput
{
namespace device
{

template <typename Map, typename Vector, typename Function>
void add_element(
    DIDEVICEOBJECTINSTANCE const &_data, Map &_map, Vector &_vector, Function const &_function)
{
  FCPPT_ASSERT_ERROR(_map.insert(std::make_pair(
                                     _data.dwOfs,
                                     fcppt::strong_typedef_construct_cast<
                                         typename Map::mapped_type,
                                         fcppt::cast::static_cast_fun>(_vector.size())))
                         .second);

  _vector.push_back(_function(_data));
}

}
}
}

#endif
