//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_MD3_IMPL_ENDIAN_HPP_INCLUDED
#define SGE_MODEL_MD3_IMPL_ENDIAN_HPP_INCLUDED

#include <fcppt/endianness/format.hpp>


namespace sge
{
namespace model
{
namespace md3
{
namespace impl
{

inline
fcppt::endianness::format
endian()
{
	return
		fcppt::endianness::format::little;
}

}
}
}
}

#endif
