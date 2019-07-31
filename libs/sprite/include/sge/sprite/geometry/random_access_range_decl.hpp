//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_RANDOM_ACCESS_RANGE_DECL_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_RANDOM_ACCESS_RANGE_DECL_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/geometry/random_access_range_fwd.hpp>
#include <fcppt/type_traits/is_iterator_of_category.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace geometry
{

template<
	typename Iterator
>
class random_access_range
{
public:
	static_assert(
		fcppt::type_traits::is_iterator_of_category<
			Iterator,
			std::random_access_iterator_tag
		>::value,
		"Iterator must be a random access iterator"
	);

	typedef Iterator iterator;

	random_access_range(
		iterator begin,
		iterator end
	);

	iterator
	begin() const;

	iterator
	end() const;

	sge::sprite::count
	size() const;

	bool
	empty() const;

	template<
		typename Compare
	>
	void
	sort(
		Compare const &
	) const;
private:
	iterator
		begin_,
		end_;
};

}
}
}

#endif
