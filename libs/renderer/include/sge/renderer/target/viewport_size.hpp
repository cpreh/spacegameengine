//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TARGET_VIEWPORT_SIZE_HPP_INCLUDED
#define SGE_RENDERER_TARGET_VIEWPORT_SIZE_HPP_INCLUDED

#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/target/base_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace target
{

SGE_RENDERER_DETAIL_SYMBOL
sge::renderer::screen_size
viewport_size(
	sge::renderer::target::base const &
);

}
}
}

#endif
