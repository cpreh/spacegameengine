//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_BUFFER_TRAITS_VIEW_HPP_INCLUDED
#define SGE_RENDERER_BUFFER_TRAITS_VIEW_HPP_INCLUDED

#include <sge/renderer/buffer/traits/view_tpl_fwd.hpp>

namespace sge::renderer::buffer::traits
{

template <typename Tag>
using view = typename sge::renderer::buffer::traits::view_tpl<Tag>::type;

}

#endif
