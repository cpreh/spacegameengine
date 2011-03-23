#ifndef SGE_LINE_DRAWER_OBJECT_HPP_INCLUDED
#define SGE_LINE_DRAWER_OBJECT_HPP_INCLUDED

#include <sge/line_drawer/line_sequence.hpp>
#include <sge/line_drawer/symbol.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace line_drawer
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_LINE_DRAWER_SYMBOL explicit
	object(
		sge::renderer::device_ptr);

	SGE_LINE_DRAWER_SYMBOL void
	render();

	SGE_LINE_DRAWER_SYMBOL ~object();
private:
	friend class scoped_lock;

	sge::renderer::device_ptr renderer_;
	sge::renderer::vertex_declaration_ptr vertex_declaration_;
	sge::renderer::vertex_buffer_ptr vb_;
	line_sequence lines_;

	void
	lock();

	void
	unlock();
};
}
}

#endif
