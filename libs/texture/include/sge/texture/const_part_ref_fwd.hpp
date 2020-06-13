//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TEXTURE_CONST_PART_REF_FWD_HPP_INCLUDED
#define SGE_TEXTURE_CONST_PART_REF_FWD_HPP_INCLUDED

#include <sge/texture/part_fwd.hpp>
#include <fcppt/reference_fwd.hpp>


namespace sge
{
namespace texture
{

using
const_part_ref
=
fcppt::reference<
	sge::texture::part const
>;

}
}

#endif
