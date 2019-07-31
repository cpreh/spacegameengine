//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_DYNAMIC_FORMAT_ELEMENT_HPP_INCLUDED
#define SGE_RENDERER_INDEX_DYNAMIC_FORMAT_ELEMENT_HPP_INCLUDED

#include <sge/renderer/index/i16.hpp>
#include <sge/renderer/index/i32.hpp>
#include <sge/renderer/index/dynamic/format.hpp>


namespace sge
{
namespace renderer
{
namespace index
{
namespace dynamic
{

template<
	sge::renderer::index::dynamic::format
>
struct format_element;

template<>
struct format_element<
	sge::renderer::index::dynamic::format::i16
>
{
	typedef
	sge::renderer::index::i16
	type;
};

template<>
struct format_element<
	sge::renderer::index::dynamic::format::i32
>
{
	typedef
	sge::renderer::index::i32
	type;
};

}
}
}
}

#endif
