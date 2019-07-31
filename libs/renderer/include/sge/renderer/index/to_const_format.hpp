//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_TO_CONST_FORMAT_HPP_INCLUDED
#define SGE_RENDERER_INDEX_TO_CONST_FORMAT_HPP_INCLUDED

#include <sge/renderer/index/const_tag.hpp>
#include <sge/renderer/index/format.hpp>


namespace sge
{
namespace renderer
{
namespace index
{

template<
	typename Format
>
using to_const_format
=
sge::renderer::index::format<
	typename
	Format::index_type,
	sge::renderer::index::const_tag
>;

}
}
}

#endif
