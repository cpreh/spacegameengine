#ifndef SGE_RUCKSACK_WIDGET_BASE_HPP_INCLUDED
#define SGE_RUCKSACK_WIDGET_BASE_HPP_INCLUDED

#include <sge/rucksack/axis_policy2.hpp>
#include <sge/class_symbol.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/symbol.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/optional_parent.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/intrusive/list.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace rucksack
{
namespace widget
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

class SGE_CLASS_SYMBOL base
:
	public
		boost::intrusive::list_base_hook
		<
			boost::intrusive::link_mode<boost::intrusive::auto_unlink>
		>
{
FCPPT_PP_POP_WARNING

FCPPT_NONCOPYABLE(
	base);
public:
	virtual void
	size(
		sge::rucksack::dim const &) = 0;

	virtual void
	position(
		sge::rucksack::vector const &) = 0;

	virtual sge::rucksack::dim const
	size() const = 0;

	sge::rucksack::rect const
	area() const;

	virtual sge::rucksack::vector const
	position() const = 0;

	virtual sge::rucksack::axis_policy2 const
	axis_policy() const = 0;

	virtual void
	relayout() = 0;

	SGE_RUCKSACK_SYMBOL void
	parent(
		sge::rucksack::widget::optional_parent const &);

	SGE_RUCKSACK_SYMBOL sge::rucksack::widget::optional_parent const &
	parent() const;

	SGE_RUCKSACK_SYMBOL
	virtual ~base() = 0;
protected:
	SGE_RUCKSACK_SYMBOL
	explicit
	base(
		sge::rucksack::widget::optional_parent const &);

	SGE_RUCKSACK_SYMBOL virtual void
	child_destroyed(
		base &);
private:
	sge::rucksack::widget::optional_parent parent_;
};
}
}
}


#endif
