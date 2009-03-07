#ifndef SGE_CELL_GRID_HPP_INCLUDED
#define SGE_CELL_GRID_HPP_INCLUDED

#include "field_type.hpp"
#include <sge/collision/rect.hpp>
#include <sge/container/field_decl.hpp>
#include <sge/math/dim/static.hpp>
#include <sge/time/funit.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace cell
{

class grid {
	SGE_NONCOPYABLE(grid)
public:
	explicit grid(
		collision::rect const &);
	
	~grid();

	void update(
		time::funit);
	
	field_type &field();

	typedef math::dim::static_<
		collision::unit,
		2
	>::type dim_type;

	dim_type const
	cell_size() const;
private:
	collision::rect const rect_;
	field_type field_;
};

}
}

#endif
