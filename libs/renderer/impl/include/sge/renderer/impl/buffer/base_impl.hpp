//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_IMPL_BUFFER_BASE_IMPL_HPP_INCLUDED
#define SGE_RENDERER_IMPL_BUFFER_BASE_IMPL_HPP_INCLUDED

#include <sge/renderer/buffer/base.hpp>


template<
	typename Tag
>
sge::renderer::buffer::base<
	Tag
>::base()
= default;

namespace sge::renderer::buffer
{
template<
	typename Tag
>
base<
	Tag
>::~base()
= default;
}

#endif
