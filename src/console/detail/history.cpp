#include <sge/console/detail/history.hpp>
#include <sge/input/modifier/states.hpp>
#include <sge/input/key_type.hpp>
#include <sge/math/compare.hpp>
#include <sge/assert.hpp>
#include <boost/next_prior.hpp>

sge::console::detail::history::history()
	: items_(),
	  pos_(items_.begin())
{
}

sge::console::detail::history::iterator_pair const 
	sge::console::detail::history::lines_inside(
	rect const &r,
	unit const height) const
{
	SGE_ASSERT(!math::almost_zero(height));
	
	// draw history
	unit const total_lines = static_cast<unit>(r.h()/height);

	// go from pos_ to min(pos_+total_lines,end)
	const_iterator it = pos_;
	for (unit i = static_cast<unit>(0); 
	     i < total_lines && it != items_.end(); 
			 ++i)
		++it;

	return boost::make_iterator_range(
		const_iterator(pos_),
		const_iterator(it));
}

void sge::console::detail::history::up()
{
	if (pos_ == --items_.end())
		return;
	pos_ = boost::next(pos_);
}

void sge::console::detail::history::down()
{
	if (pos_ == items_.begin())
		return;
	pos_ = boost::prior(pos_);
}

sge::string const sge::console::detail::history::current() const
{
	return *pos_;
}

void sge::console::detail::history::push_front(string const &s)
{
	iterator::difference_type const d = 
		std::distance(
			items_.begin(),
			pos_);
	items_.push_front(s);
	pos_ = boost::next(items_.begin(),d);
}

void sge::console::detail::history::push_back(string const &s)
{
	iterator::difference_type const d = 
		std::distance(
			items_.begin(),
			pos_);
	items_.push_back(s);
	pos_ = boost::next(items_.begin(),d);
}
