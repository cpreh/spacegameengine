#ifndef SGE_GUI_LAYOUTS_ROW_HPP_INCLUDED
#define SGE_GUI_LAYOUTS_ROW_HPP_INCLUDED

#include <sge/gui/layouts/base.hpp>
#include <sge/gui/widgets/fwd.hpp>
#include <sge/gui/export.hpp>
#include <sge/gui/size_policy.hpp>
#include <sge/math/dim/basic_decl.hpp>
#include <sge/math/vector/basic_decl.hpp>
#include <vector>
#include <cstddef>

namespace sge
{
namespace gui
{
namespace layouts
{
class SGE_CLASS_SYMBOL row : public base
{
	public:
	SGE_GUI_SYMBOL row();
	SGE_GUI_SYMBOL void compile(invalidation::type const &);
	SGE_GUI_SYMBOL void compile_static();
	SGE_GUI_SYMBOL void pos(point const &);
	SGE_GUI_SYMBOL void size(dim const &);
	SGE_GUI_SYMBOL dim const optimal_size() const;
	private:
	virtual dim::reference master(
		dim &) const = 0;
	virtual dim::const_reference master(
		dim const &) const = 0;
	virtual point::reference master(
		point &) const = 0;
	virtual point::const_reference master(
		point const &) const = 0;
	dim::reference slave(
		dim &) const;
	dim::const_reference slave(
		dim const &) const;
	point::reference slave(
		point &) const;
	point::const_reference slave(
		point const &) const;

	void adapt(
		dim const &,
		dim const &,
		axis_policy::type,
		dim::size_type);
	void adapt_outer(
		dim const &,
		dim const &,
		dim::size_type);
	void update_widgets(
		dim const &);
	void reset_cache();
	unsigned count_flags(
		axis_policy::type,
		dim::size_type) const;
	void do_compile(
		dim const &);

	typedef std::vector<
		std::pair<
			widgets::base*,
			dim>
			> widget_map;
	//typedef std::map<widget*,dim> widget_map;
	widget_map sizes;
};
}
}
}

#endif
