#ifndef SGE_CELL_GRID_HPP_INCLUDED
#define SGE_CELL_GRID_HPP_INCLUDED

#include <sge/collision/rect.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace cell
{

class grid {
	SGE_NONCOPYABLE(grid)
public:
	explicit grid(
		rect const &);
	
	void update(
		time::funit);
	
	field_type &field() const;
private:
	field_type field_;
};

}
}

#endif
