//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_DIFFERENCE_TYPE_HPP_INCLUDED
#define SGE_RENDERER_INDEX_DIFFERENCE_TYPE_HPP_INCLUDED

#include <sge/renderer/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace index
{

using
difference_type
=
std::make_signed_t<
	sge::renderer::size_type
>;

}
}
}

#endif
