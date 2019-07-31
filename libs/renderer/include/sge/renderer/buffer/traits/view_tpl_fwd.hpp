//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_BUFFER_TRAITS_VIEW_TPL_FWD_HPP_INCLUDED
#define SGE_RENDERER_BUFFER_TRAITS_VIEW_TPL_FWD_HPP_INCLUDED

#include <sge/image/view/object_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace buffer
{
namespace traits
{

template<
	typename Tag
>
struct view_tpl
{
	typedef
	sge::image::view::object<
		Tag
	>
	type;
};

}
}
}
}

#endif
