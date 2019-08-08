//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_INFO_CONTAINER_HPP_INCLUDED
#define SGE_INPUT_INFO_CONTAINER_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/info/container_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace input
{
namespace info
{

template<
	typename Id,
	typename Obj
>
class container
{
public:
	typedef
	Id
	id;

	typedef
	id
	size_type;

	typedef
	Obj
	object;

	typedef
	object
	value_type;

	typedef
	std::vector<
		Obj
	>
	vector;

	SGE_INPUT_DETAIL_SYMBOL
	explicit
	container(
		vector &&
	);

	SGE_INPUT_DETAIL_SYMBOL
	Obj const &
	operator[](
		Id const &
	) const;

	SGE_INPUT_DETAIL_SYMBOL
	Id
	size() const;

	SGE_INPUT_DETAIL_SYMBOL
	bool
	empty() const;

	SGE_INPUT_DETAIL_SYMBOL
	vector const &
	get() const;
private:
	vector vector_;
};

}
}
}

#endif
