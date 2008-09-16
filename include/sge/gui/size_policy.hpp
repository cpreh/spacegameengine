#ifndef SGE_GUI_SIZE_POLICY_HPP_INCLUDED
#define SGE_GUI_SIZE_POLICY_HPP_INCLUDED

#include "../bitfield.hpp"
// hrhr, no impl crap for me!
#include "../bitfield_impl.hpp"
#include "../export.hpp"
#include <cstddef>

namespace sge
{
namespace gui
{
namespace axis_policy
{
enum internal_type { none,can_grow,can_shrink,should_grow,size };
typedef bitfield<internal_type,size> type;
};

class size_policy
{
	public:
	SGE_SYMBOL size_policy(axis_policy::type const &x,axis_policy::type const &y);
	axis_policy::type const &x() const { return x_; }
	axis_policy::type const &y() const { return y_; }
	// this is a hack so we can use it with the layouts::row::master stuff
	axis_policy::type const &index(std::size_t const i) const
	{ 
		return i == static_cast<std::size_t>(0) ? x() : y(); 
	}

	static size_policy const default_policy;
	private:
	axis_policy::type x_,y_;
};
}
}

#endif
