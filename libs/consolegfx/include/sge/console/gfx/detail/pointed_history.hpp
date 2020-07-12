//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CONSOLE_GFX_DETAIL_POINTED_HISTORY_HPP_INCLUDED
#define SGE_CONSOLE_GFX_DETAIL_POINTED_HISTORY_HPP_INCLUDED

#include <sge/font/string.hpp>
#include <fcppt/nonmovable.hpp>
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
	FCPPT_NONMOVABLE(
		pointed_history
	);
public:
	using
	value_type
	=
	sge::font::string;

	using
	container
	=
	std::deque<
		value_type
	>;

	using
	size_type
	=
	container::size_type;

	using
	const_iterator
	=
	container::const_iterator;

	explicit
	pointed_history(
		size_type limit
	);

	~pointed_history();

	void
	push_front(
		value_type &&
	);

	void
	up();

	void
	down();

	void
	to_begin();

	void
	to_end();

	[[nodiscard]]
	const_iterator
	point() const;

	[[nodiscard]]
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
