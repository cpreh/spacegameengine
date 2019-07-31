//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_LINE_DRAWER_OBJECT_HPP_INCLUDED
#define SGE_LINE_DRAWER_OBJECT_HPP_INCLUDED

#include <sge/line_drawer/line_sequence.hpp>
#include <sge/line_drawer/scoped_lock_fwd.hpp>
#include <sge/line_drawer/detail/symbol.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/state/core/blend/object_unique_ptr.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sge
{
namespace line_drawer
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	SGE_LINE_DRAWER_DETAIL_SYMBOL
	explicit
	object(
		sge::renderer::device::core &
	);

	SGE_LINE_DRAWER_DETAIL_SYMBOL
	void
	render(
		sge::renderer::context::core &
	);

	SGE_LINE_DRAWER_DETAIL_SYMBOL
	~object();
private:
	friend class sge::line_drawer::scoped_lock;

	sge::renderer::device::core &renderer_;

	sge::renderer::vertex::declaration_unique_ptr const vertex_declaration_;

	sge::renderer::state::core::blend::object_unique_ptr const blend_state_;

	typedef
	fcppt::optional::object<
		sge::renderer::vertex::buffer_unique_ptr
	>
	optional_vertex_buffer_unique_ptr;

	optional_vertex_buffer_unique_ptr vb_;

	sge::line_drawer::line_sequence lines_;

	void
	lock();

	void
	unlock();
};

}
}

#endif
