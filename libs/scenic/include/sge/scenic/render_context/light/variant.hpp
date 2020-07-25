//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_RENDER_CONTEXT_LIGHT_VARIANT_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_LIGHT_VARIANT_HPP_INCLUDED

#include <sge/scenic/render_context/light/directional.hpp>
#include <sge/scenic/render_context/light/point.hpp>
#include <fcppt/variant/object_impl.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
namespace light
{

using
variant
=
fcppt::variant::object<
	sge::scenic::render_context::light::directional,
	sge::scenic::render_context::light::point
>;

}
}
}
}

#endif
