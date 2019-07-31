//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VISUAL_BASE_HPP_INCLUDED
#define SGE_RENDERER_VISUAL_BASE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/visual_base_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

/**
\brief Base class for all renderable visuals created by sge

\ingroup sge_renderer
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL visual_base
{
	FCPPT_NONCOPYABLE(
		visual_base
	);
public:
	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	visual_base(
		sge::renderer::pixel_format::object const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	virtual
	~visual_base();

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::pixel_format::object const &
	pixel_format() const;
private:
	sge::renderer::pixel_format::object const pixel_format_;
};

}
}

#endif
