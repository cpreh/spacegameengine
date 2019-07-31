//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WINDOW_OPTIONAL_DIM_FWD_HPP_INCLUDED
#define SGE_WINDOW_OPTIONAL_DIM_FWD_HPP_INCLUDED

#include <sge/window/dim_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge
{
namespace window
{

typedef fcppt::optional::object<
	sge::window::dim
> optional_dim;

}
}

#endif
