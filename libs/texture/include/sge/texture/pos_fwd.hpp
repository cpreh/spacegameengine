//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TEXTURE_POS_FWD_HPP_INCLUDED
#define SGE_TEXTURE_POS_FWD_HPP_INCLUDED

#include <sge/renderer/size_type.hpp>
#include <fcppt/math/vector/static_fwd.hpp>


namespace sge
{
namespace texture
{

typedef
fcppt::math::vector::static_<
	sge::renderer::size_type,
	2u
>
pos;

}
}

#endif
