#include "../widgets/container.hpp"
#include "row.hpp"
#include <sge/iostream.hpp>
#include <boost/foreach.hpp>

sge::gui::layouts::row::row(widgets::container &w)
	: layout(w)
{
	sge::cerr << "row: constructed row layout\n";
}

void sge::gui::layouts::row::update()
{
	sge::cerr << "row: updating\n";
	// if this widget has no children, just quit
	if (!connected_widget().children().size())
	{
		sge::cerr << "row: widget has no children, returning\n";
		return;
	}

	// if we have a top level widget which isn't fixed, set it to the minimum size
	if (!connected_widget().parent_widget() && connected_widget().size_policy() != size_policy::fixed)
	{
		sge::cerr << "row: top level widget which can expand, setting to minimum size\n";
		sge::cerr << "row: minimum size is " << minimum_size() << "\n";
		connected_widget().size(minimum_size());
	}

	sge::cerr << "row: minimum size for this widget is " << minimum_size() << "\n";

	// now assume we have this widget's size fixed
	dim const fixed_size = connected_widget().size();
	// minimum size for all widgets
	dim const minimum = minimum_size();
	// overhead space
	dim const extra = fixed_size - minimum;

	// get all non fixed widgets
	unsigned non_fixed = static_cast<unsigned>(0);
	BOOST_FOREACH(widget &child,connected_widget().children())
		if (child.size_policy() != size_policy::fixed)
			non_fixed++;

	sge::cerr << "row: there are " << non_fixed << " non fixed children\n";
	
	// extra space per widget
	unit const widget_space = 
		static_cast<unit>(non_fixed ? extra[master(extra)]/non_fixed : 0);
	
	sge::cerr << "row: ... so we have " << 
		widget_space << " pixels extra space to spare\n";

	unit master_pos = connected_widget().pos()[master(connected_widget().pos())];
	unit const slave_pos = connected_widget().pos()[slave(connected_widget().pos())];

	// loop through widgets and update according to space
	sge::cerr << "row: updating children\n";
	BOOST_FOREACH(widget &child,connected_widget().children())
	{
		// if size is fixed, just use w.size()
		if (child.size_policy() == size_policy::fixed)
		{
			sge::cerr << "row: child is fixed size\n";

			point new_pos;
			new_pos[master(new_pos)] = master_pos;
			new_pos[slave(new_pos)] = 
				static_cast<unit>(
					slave_pos+
					connected_widget().size()[slave(connected_widget().size())]/2-
					child.size()[slave(child.size())]/2);
			child.set_pos_raw(new_pos);
			sge::cerr << "row: new position is " << new_pos << "\n";
			master_pos += child.size()[master(child.size())];
		}
		else
		{
			sge::cerr << "row: child is dynamic size\n";

			dim const this_min_size = child.minimum_size();
			// else use minimum size plus extra space and keep height
			dim new_size;
			new_size[master(new_size)] = this_min_size[master(this_min_size)]+widget_space;
			new_size[slave(new_size)] = fixed_size[slave(fixed_size)];

			point new_pos;
			new_pos[master(new_pos)] = master_pos;
			new_pos[slave(new_pos)] = static_cast<unit>(
				slave_pos+
				connected_widget().size()[slave(connected_widget().size())]/2-
				new_size[slave(new_size)]/2);
			sge::cerr << "row: new size is " << new_size << "\n";
			child.set_pos_raw(new_pos);
			child.size(new_size);
			master_pos += new_size[master(new_size)];
		}
	}
}

sge::gui::dim const sge::gui::layouts::row::minimum_size() const
{
	sge::cerr << "row: in minimum size\n";

	// calculate total minimum size (rowly)
	dim minimum(static_cast<unit>(0),static_cast<unit>(0));

	BOOST_FOREACH(widget const &child,connected_widget().children())
	{
		dim const child_size = child.minimum_size();
		sge::cerr << "row: this child's minimum size " << child_size << "\n";
		minimum[master(minimum)] += child_size[master(child_size)];
		minimum[slave(minimum)] = std::max(minimum[slave(minimum)],child_size[slave(child_size)]);
	}

	return minimum;
}
