#ifndef SGE_GUI_LAYOUTS_ROW_HPP_INCLUDED
#define SGE_GUI_LAYOUTS_ROW_HPP_INCLUDED

#include "../layout.hpp"
#include "../widget_fwd.hpp"
#include "../../export.hpp"
#include "../size_policy.hpp"
#include <vector>
#include <cstddef>

namespace sge
{
namespace gui
{
namespace layouts
{
class SGE_CLASS_SYMBOL row : public layout
{
	public:
	SGE_SYMBOL row(widget &);
	SGE_SYMBOL void update();
	SGE_SYMBOL dim const size_hint() const;
	private:
	// NOTE: this is actually quite hacky, I first tried to return a reference to
	// the w() or h() component, but then you get const issues which _might_ be
	// resolved somehow virtual dim::size_type master(dim const &) const = 0;
	virtual std::size_t master() const = 0;
	std::size_t slave() const 
	{ 
		return master() == static_cast<std::size_t>(0) 
			? static_cast<std::size_t>(1) 
			: static_cast<std::size_t>(0); 
	}

	void adapt(dim const &,dim const &,axis_policy::type,std::size_t);
	void adapt_outer(dim const &,dim const &,std::size_t);
	void update_widgets(dim const &);
	void reset_cache();
	unsigned count_flags(axis_policy::type,std::size_t) const;

	typedef std::vector<std::pair<widget*,dim> > widget_map;
	//typedef std::map<widget*,dim> widget_map;
	widget_map sizes;
};
}
}
}

#endif
