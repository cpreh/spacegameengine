#ifndef SGE_GUI_LAYOUTS_GRID_HPP_INCLUDED	
#define SGE_GUI_LAYOUTS_GRID_HPP_INCLUDED	

#include <sge/gui/detail/grid_cache.hpp>
#include <sge/gui/layouts/base.hpp>
#include <sge/gui/widgets/fwd.hpp>
#include <sge/gui/export.hpp>
#include <sge/gui/dim.hpp>
#include <sge/gui/size_policy.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/axis_type.hpp>
#include <sge/container/field.hpp>
#include <sge/container/raw_vector.hpp>
#include <sge/scoped_ptr.hpp>
#include <boost/multi_array.hpp>
#include <utility>
#include <vector>
#include <map>

namespace sge
{
namespace gui
{
namespace layouts
{
class SGE_CLASS_SYMBOL grid : public base
{
public:
	SGE_GUI_SYMBOL void compile_static();
	SGE_GUI_SYMBOL dim const optimal_size() const;
private:
	typedef scoped_ptr<detail::grid_cache> cache_ptr;
	mutable cache_ptr cache_;

  detail::grid_cache &valid_cache() const;

	void adapt_outer(
		dim const &,
		dim const &,
		axis_type);
	void shrink(
		dim const &,
		dim const &,
		axis_type);
	void expand(
		dim const &,
		dim const &,
		axis_type);
	void adapt(
		dim const &,
		dim const &,
		axis_policy::type,
		axis_type);
	void update_rolumn(
		axis_type,
		unsigned,
		axis_policy::type,
		unit);
	unsigned count_flags(
		axis_policy::type,
		axis_type) const;
	void update_cache();
	void update_policy_cache();
	void update_size_cache();
	void update_rolumn_cache();
	void update_widgets();
	void update_widget(
		widgets::base &,
		point const &,
		dim const &);
};
}
}
}

#endif
