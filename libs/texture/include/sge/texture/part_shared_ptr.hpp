//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TEXTURE_PART_SHARED_PTR_HPP_INCLUDED
#define SGE_TEXTURE_PART_SHARED_PTR_HPP_INCLUDED

#include <sge/texture/part_fwd.hpp>
#include <fcppt/shared_ptr_impl.hpp>


namespace sge
{
namespace texture
{

typedef fcppt::shared_ptr<
	sge::texture::part
> part_shared_ptr;

}
}

#endif
