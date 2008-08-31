#ifndef SGE_GUI_SIZE_POLICY_HPP_INCLUDED
#define SGE_GUI_SIZE_POLICY_HPP_INCLUDED

namespace sge
{
namespace gui
{
namespace axis_policy
{
enum type 
{  
	/* 
	 * the widget::size_hint() is the only acceptable alternative, so the widget can
	 * never grow or shrink (e.g. the vertical direction of a push button)
	 */
	fixed, 
	/*
	 * The widget::size_hint() is minimal, and sufficient. The widget can be
	 * expanded, but there is no advantage to it being larger (e.g. the
	 * horizontal direction of a push button). It cannot be smaller than the size
	 * provided by widget::size_hint().
	 */
	minimum, 
	/*
	 * The widget::size_hint() is a maximum. The widget can be shrunk any amount
	 * without detriment if other widgets need the space (e.g. a separator line).
	 * It cannot be larger than the size provided by widget::size_hint().
	 */
	maximum, 
	/*
	 * The widget::size_hint() is best, but the widget can be shrunk and still be
	 * useful. The widget can be expanded, but there is no advantage to it being
	 * larger than widget::size_hint() (the default widget policy).
	 */
	preferred,
	/*
	 * The widget::size_hint() is a sensible size, but the widget can be shrunk
	 * and still be useful. The widget can make use of extra space, so it should
	 * get as much space as possible (e.g. the horizontal direction of a slider).
	 */
	expanding, 
	/*
	 * The widget::size_hint() is minimal, and sufficient. The widget can make
	 * use of extra space, so it should get as much space as possible (e.g. the
	 * horizontal direction of a slider). 
	 */
	minimum_expanding
};
};

class size_policy
{
	public:
	SGE_SYMBOL size_policy(axis_policy::type const &x,axis_policy::type const &y);
	size_policy::type const &x() const { return x_; }
	size_policy::type const &y() const { return y_; }

	static size_policy const default_policy;
	private:
	axis_policy::type const x_,y_;
};
}
}

#endif
