//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_CONST_FORMAT_32_HPP_INCLUDED
#define SGE_RENDERER_INDEX_CONST_FORMAT_32_HPP_INCLUDED

#include <sge/renderer/index/const_tag.hpp>
#include <sge/renderer/index/format_fwd.hpp>
#include <sge/renderer/index/i32.hpp>


namespace sge
{
namespace renderer
{
namespace index
{

typedef
sge::renderer::index::format<
	sge::renderer::index::i32,
	sge::renderer::index::const_tag
>
const_format_32;

}
}
}

#endif
