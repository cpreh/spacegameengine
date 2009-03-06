#ifndef SGE_CELL_GRID_ENTRY_HPP_INCLUDED
#define SGE_CELL_GRID_ENTRY_HPP_INCLUDED

namespace sge
{
namespace cell
{

class grid_entry {
public:
	explicit grid_entry(
		rect const &);

	void update(
		time::funit);
	
	void add(
		circle_ptr);
	
	collision::rect const &
	rect() const;

	weak_circle_list &
	entries() const;
private:
	collision::rect const rect_;
};

}
}

#endif
