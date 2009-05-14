#ifndef SGE_GUI_LAYOUTS_GRID_CACHE_HPP_INCLUDED
#define SGE_GUI_LAYOUTS_GRID_CACHE_HPP_INCLUDED


// TODO: this can live completely without the grid, it doesn't have to be
// grid's friend and it can be modeled so it contains only const elements
class sge::gui::layouts::grid::cache
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

	cache(grid &);

	child_plane &plane();
	data_map &data();
	rolumn_container &rolumns();
private:
	grid &that_;
	
	child_plane      plane_;
	data_map         data_;
	rolumn_container rolumns_;

	void first_pass();
	void second_pass();
};

#endif
