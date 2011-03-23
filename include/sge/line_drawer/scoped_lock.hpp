#ifndef SGE_LINE_DRAWER_SCOPED_LOCK_HPP_INCLUDED
#define SGE_LINE_DRAWER_SCOPED_LOCK_HPP_INCLUDED

#include <sge/line_drawer/line_sequence.hpp>
#include <sge/line_drawer/symbol.hpp>
#include <sge/line_drawer/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace line_drawer
{
class scoped_lock
{
FCPPT_NONCOPYABLE(
	scoped_lock);
public:
	SGE_LINE_DRAWER_SYMBOL explicit
	scoped_lock(
		object &);

	SGE_LINE_DRAWER_SYMBOL line_sequence &
	value() const;

	SGE_LINE_DRAWER_SYMBOL ~scoped_lock();
private:
	object &object_;
};
}
}

#endif
