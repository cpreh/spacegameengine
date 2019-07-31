//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_MD3_IMPL_INDEX_ARRAY_HPP_INCLUDED
#define SGE_MODEL_MD3_IMPL_INDEX_ARRAY_HPP_INCLUDED

#include <sge/model/md3/impl/s32.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace model
{
namespace md3
{
namespace impl
{

typedef
std::array<
	sge::model::md3::impl::s32,
	3
>
index_array;

}
}
}
}

#endif
