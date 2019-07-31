//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_DRAW_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_DRAW_CONTEXT_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/fun_ref_value_type.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/info/context_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/reference.hpp>


namespace sge
{
namespace opengl
{

class draw_context
:
	public sge::opengl::context::base
{
	FCPPT_NONCOPYABLE(
		draw_context
	);
public:
	typedef
	sge::opengl::info::context const &
	parameter;

	explicit
	draw_context(
		sge::opengl::info::context const &
	);

	~draw_context()
	override;

	typedef
	sge::opengl::fun_ref<
		PFNGLDRAWRANGEELEMENTSPROC
	>
	gl_draw_range_elements;

	typedef
	fcppt::optional::reference<
		sge::opengl::fun_ref_value_type<
			gl_draw_range_elements
		>
	>
	optional_draw_range_elements;

	typedef
	optional_draw_range_elements::value_type
	draw_range_elements_ref;

	optional_draw_range_elements
	draw_range_elements() const;

	static sge::opengl::context::id const static_id;
private:
	optional_draw_range_elements const draw_range_elements_;
};

}
}

#endif
