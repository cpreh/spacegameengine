//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_IMPL_SCOPED_RENDER_CONTEXT_HPP_INCLUDED
#define SGE_CEGUI_IMPL_SCOPED_RENDER_CONTEXT_HPP_INCLUDED

#include <sge/cegui/impl/renderer_ref.hpp>
#include <sge/renderer/context/ffp_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace cegui
{
namespace impl
{

class scoped_render_context
{
	FCPPT_NONMOVABLE(
		scoped_render_context
	);
public:
	scoped_render_context(
		sge::cegui::impl::renderer_ref,
		sge::renderer::context::ffp_ref
	);

	~scoped_render_context();
private:
	sge::cegui::impl::renderer_ref const renderer_;
};

}
}
}

#endif
