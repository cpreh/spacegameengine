//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_FORMAT_16_HPP_INCLUDED
#define SGE_RENDERER_INDEX_FORMAT_16_HPP_INCLUDED

#include <sge/renderer/index/format_fwd.hpp>
#include <sge/renderer/index/i16.hpp>
#include <sge/renderer/index/nonconst_tag.hpp>


namespace sge
{
namespace renderer
{
namespace index
{

typedef
sge::renderer::index::format<
	sge::renderer::index::i16,
	sge::renderer::index::nonconst_tag
>
format_16;

}
}
}

#endif
