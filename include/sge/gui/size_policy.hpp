#ifndef SGE_GUI_SIZE_POLICY_HPP_INCLUDED
#define SGE_GUI_SIZE_POLICY_HPP_INCLUDED

#include <sge/bitfield.hpp>
// hrhr, no impl crap for me!
#include <sge/bitfield_impl.hpp>
#include <sge/gui/export.hpp>
#include <cstddef>

namespace sge
{
namespace gui
{
namespace axis_policy
{
enum internal_type 
{ 
	none,
	can_grow,
	can_shrink,
	should_grow,
	size 
};

typedef bitfield<internal_type,size> type;
}

class size_policy
{
	public:
	SGE_GUI_SYMBOL size_policy(
		axis_policy::type const &x,
		axis_policy::type const &y);
	SGE_GUI_SYMBOL axis_policy::type const &x() const;
	SGE_GUI_SYMBOL axis_policy::type const &y() const;
	// this is a hack so we can use it with the layouts::row::master stuff
	SGE_GUI_SYMBOL axis_policy::type const &index(std::size_t const i) const;
	SGE_GUI_SYMBOL static size_policy const default_policy;
	private:
	axis_policy::type x_,y_;
};
}
}

#endif
