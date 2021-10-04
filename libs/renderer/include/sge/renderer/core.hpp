//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_CORE_HPP_INCLUDED
#define SGE_RENDERER_CORE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/core_fwd.hpp>
#include <sge/renderer/system_unique_ptr.hpp>
#include <sge/renderer/caps/system_field_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/window/system_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::renderer
{

/**
\brief The staring class of a renderer plugin

\ingroup sge_renderer

Creates renderer systems from window systems and provides the plugin's
capabilities.
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL core
{
	FCPPT_NONMOVABLE(
		core
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	core();
public:
	SGE_RENDERER_DETAIL_SYMBOL
	virtual
	~core();

	[[nodiscard]]
	virtual
	sge::renderer::system_unique_ptr
	create_system(
		sge::window::system_ref
	) = 0;

	[[nodiscard]]
	virtual
	sge::renderer::caps::system_field
	caps() const = 0;
};

}

#endif
