//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_MD3_IMPL_READ_SCALAR_HPP_INCLUDED
#define SGE_MODEL_MD3_IMPL_READ_SCALAR_HPP_INCLUDED

#include <sge/model/md3/scalar.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace model
{
namespace md3
{
namespace impl
{

sge::model::md3::scalar
read_scalar(
	std::istream &
);

}
}
}
}

#endif
