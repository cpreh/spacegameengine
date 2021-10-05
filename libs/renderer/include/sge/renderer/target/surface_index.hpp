//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TARGET_SURFACE_INDEX_HPP_INCLUDED
#define SGE_RENDERER_TARGET_SURFACE_INDEX_HPP_INCLUDED

#include <sge/renderer/target/surface_index_value.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge::renderer::target
{

/**
 * \brief A strong typedef describing the index of a surface
*/
FCPPT_DECLARE_STRONG_TYPEDEF(
	sge::renderer::target::surface_index_value,
	surface_index
);

}

#endif
