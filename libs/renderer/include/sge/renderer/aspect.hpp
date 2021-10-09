//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_ASPECT_HPP_INCLUDED
#define SGE_RENDERER_ASPECT_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <sge/renderer/screen_size_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <fcppt/optional/object_impl.hpp>

namespace sge::renderer
{

/**
\brief Calculates the aspect of a screen size

\ingroup sge_renderer

An aspect of a dimension (w,h) is defined as the ratio from the larger to the
smaller. The division is done as a floating point division.

\param size The size to calculate the aspect from

\return <code> size.w > size.h ? size.w / size.h : size.h / size.w </code>
*/
SGE_RENDERER_DETAIL_SYMBOL
fcppt::optional::object<sge::renderer::scalar> aspect(sge::renderer::screen_size const &size);

}

#endif
