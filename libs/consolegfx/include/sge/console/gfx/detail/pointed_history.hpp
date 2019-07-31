//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CONSOLE_GFX_DETAIL_POINTED_HISTORY_HPP_INCLUDED
#define SGE_CONSOLE_GFX_DETAIL_POINTED_HISTORY_HPP_INCLUDED

#include <sge/font/string.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <deque>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace console
{
namespace gfx
{
namespace detail
{

class pointed_history
{
	FCPPT_NONCOPYABLE(
		pointed_history
	);
public:
	typedef
	sge::font::string
	value_type;

	typedef
	std::deque
	<
		value_type
	>
	container;

	typedef
	container::size_type
	size_type;

	typedef
	container::const_iterator
	const_iterator;

	explicit
	pointed_history(
		size_type limit
	);

	~pointed_history();

	void
	push_front(
		value_type const &
	);

	void
	up();

	void
	down();

	void
	to_begin();

	void
	to_end();

	const_iterator
	point() const;

	const_iterator
	end() const;
private:
	container container_;

	size_type limit_;

	size_type point_;
};

}
}
}
}

#endif
