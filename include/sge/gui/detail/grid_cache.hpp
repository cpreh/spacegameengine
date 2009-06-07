#ifndef SGE_GUI_DETAIL_GRID_CACHE_HPP_INCLUDED
#define SGE_GUI_DETAIL_GRID_CACHE_HPP_INCLUDED

#include <sge/container/field.hpp>
#include <sge/container/raw_vector.hpp>
#include <sge/gui/dim.hpp>
#include <sge/gui/unit.hpp>
#include <sge/gui/widgets/base.hpp>
#include <sge/gui/size_policy.hpp>

#include <map>

namespace sge
{
namespace gui
{
namespace detail
{
class grid_cache
{
public:
	class widget_data
	{
	public:
		/*dim optimal_size;
		dim final_size;
    */
    dim size;

		widget_data();
	};

	class rolumn_data
	{
	public:
		unit size;
		axis_policy::type policy; 

		rolumn_data();
	};

	// the "real" grid
	typedef container::field<
		widgets::base*,
		container::raw_vector
		> child_plane;
	typedef child_plane::size_type size_type;
	// stores the size data for each widget (is there because the real grid could
	// be sparse
	typedef std::map<
		widgets::base*,
		widget_data
		> data_map;
	// stores data per column and row (per rolumn)
	typedef container::field<
		rolumn_data
		> rolumn_container;

	grid_cache(
		widgets::base::child_container const &);

	child_plane &plane();
	data_map &data();
	rolumn_container &rolumns();
	rolumn_container &volatile_rolumns();
private:
	widgets::base::child_container const &widgets_;
	
	child_plane      plane_;
	data_map         data_;
	rolumn_container rolumns_;
	rolumn_container volatile_rolumns_;

	void first_pass();
	void second_pass();
};
}
}
}

#endif
