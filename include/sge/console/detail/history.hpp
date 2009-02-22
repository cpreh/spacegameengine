#ifndef SGE_CONSOLE_DETAIL_HISTORY_HPP_INCLUDED
#define SGE_CONSOLE_DETAIL_HISTORY_HPP_INCLUDED

#include <sge/console/detail/cursor_fwd.hpp>
#include <sge/math/vector/vector.hpp>
#include <sge/math/dim/basic_decl.hpp>
#include <sge/math/rect.hpp>
#include <sge/string.hpp>
#include <boost/range/iterator_range.hpp>
#include <utility>
#include <deque>

namespace sge
{
namespace console
{
namespace detail
{
class history
{
	public:
	typedef std::deque<string> container;
	typedef container::iterator iterator;
	typedef container::const_iterator const_iterator;
	typedef container::const_reverse_iterator const_reverse_iterator;
	typedef boost::iterator_range<const_iterator> iterator_pair;
	typedef unsigned unit;
	typedef math::rect<unit> rect;
	typedef math::dim::static_<unit,2>::type dim;
	typedef math::vector::static_<unit,2>::type point;

	history();

	iterator_pair const lines_inside(
		rect const &,
		unit height) const;
	void up();
	void down();
	void push_front(string const &);
	void push_back(string const &);
	string const current() const;
	private:
	container items_;
	iterator pos_;
};
}
}
}

#endif
