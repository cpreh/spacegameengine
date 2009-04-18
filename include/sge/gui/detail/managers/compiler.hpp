#ifndef SGE_GUI_DETAIL_MANAGERS_COMPILER_HPP_INCLUDED
#define SGE_GUI_DETAIL_MANAGERS_COMPILER_HPP_INCLUDED

#include <sge/gui/invalidation.hpp>
#include <sge/gui/detail/managers/fwd.hpp>
#include <sge/gui/detail/submanager.hpp>
#include <sge/gui/widgets/fwd.hpp>
#include <map>

namespace sge
{
namespace gui
{
namespace detail
{
namespace managers
{
class compiler : public submanager
{
	public:
	compiler(mouse &,render &);
	void add(widgets::base &);
	void update();
	void remove(widgets::base &);
	void invalidate(
		widgets::base &,
		invalidation::type const &);
	private:
	typedef std::map<
		widgets::base*,
		invalidation::type> recompile_container;

	mouse &mouse_;
	render &render_;
	recompile_container recompiles;
	recompile_container invalidates;

	void insert_or_combine(
		recompile_container &,
		widgets::base &,
		invalidation::type const &);
};
}
}
}
}

#endif
