//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_MODEL_MD3_IMPL_AXIS_ARRAY_HPP_INCLUDED
#define SGE_MODEL_MD3_IMPL_AXIS_ARRAY_HPP_INCLUDED

#include <sge/model/md3/impl/vec3.hpp>
#include <fcppt/array/object_impl.hpp>

namespace sge::model::md3::impl
{

using axis_array = fcppt::array::object<sge::model::md3::impl::vec3, 3>;

}

#endif
