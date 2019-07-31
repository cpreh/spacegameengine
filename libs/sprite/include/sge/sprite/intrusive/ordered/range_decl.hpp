//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_RANGE_DECL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_RANGE_DECL_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/intrusive/ordered/iterator_fwd.hpp>
#include <sge/sprite/intrusive/ordered/range_fwd.hpp>
#include <sge/sprite/intrusive/ordered/detail/map.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace intrusive
{
namespace ordered
{

template<
	typename Choices,
	typename Order,
	bool IsConst
>
class range
{
	typedef
	sge::sprite::intrusive::ordered::detail::map<
		Order,
		Choices
	>
	ordered_map;
public:
	typedef
	fcppt::reference<
		typename
		std::conditional<
			IsConst,
			ordered_map const,
			ordered_map
		>::type
	>
	ordered_map_reference;

	typedef
	sge::sprite::intrusive::ordered::iterator<
		Choices,
		Order,
		IsConst
	>
	iterator;

	explicit
	range(
		ordered_map_reference
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
		typename Equal
	>
	void
	sort(
		Equal const &
	) const;
private:
	ordered_map_reference ordered_map_;

	sge::sprite::count size_;
};

}
}
}
}

#endif
