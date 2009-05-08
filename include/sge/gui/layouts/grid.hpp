#ifndef SGE_GUI_LAYOUTS_GRID_HPP_INCLUDED	
#define SGE_GUI_LAYOUTS_GRID_HPP_INCLUDED	

#include <sge/gui/layouts/base.hpp>
#include <sge/gui/widgets/fwd.hpp>
#include <sge/gui/export.hpp>
#include <sge/gui/dim.hpp>
#include <boost/multi_array.hpp>
#include <utility>
#include <vector>

namespace sge
{
namespace gui
{
namespace layouts
{
class SGE_CLASS_SYMBOL grid : public base
{
public:
	SGE_GUI_SYMBOL void compile(invalidation::type const &);
	SGE_GUI_SYMBOL void compile_static();
	SGE_GUI_SYMBOL dim const optimal_size() const;
private:
	typedef container::field<
		widgets::base*,
		container::raw_vector
		> child_container;
	typedef container::field<
		widgets::base const *,
		container::raw_vector
		> const_child_container;
	typedef child_container::size_type size_type;
	typedef std::vector<
		std::pair<
			widgets::base*,
			dim>
			> sizes_map;
	typedef field<
		axis_policy::type,
		std::vector
		> policy_cache_type;

	sizes_map sizes_;
	policy_cache_type policy_cache_;
	const_child_container children_;

	dim const dimensions() const;
	child_container const children();
	const_child_container const children() const;
	void update_cache();
	void update_policy_cache();
};
}
}
}

#endif
