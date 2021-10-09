//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_MODEL_MD3_IMPL_XYZ_SCALE_HPP_INCLUDED
#define SGE_MODEL_MD3_IMPL_XYZ_SCALE_HPP_INCLUDED

#include <sge/model/md3/scalar.hpp>
#include <fcppt/literal.hpp>

namespace sge::model::md3::impl
{

inline sge::model::md3::scalar xyz_scale()
{
  return fcppt::literal<sge::model::md3::scalar>(1) /
         fcppt::literal<sge::model::md3::scalar>(
             64 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
         );
}

}

#endif
