//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_INTRUSIVE_RANGE_DECL_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_RANGE_DECL_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/intrusive/range_fwd.hpp>
#include <sge/sprite/intrusive/detail/list.hpp>
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

template<
	typename Choices,
	bool IsConst
>
class range
{
	typedef
	sge::sprite::intrusive::detail::list<
		Choices
	>
	list;
public:
	typedef
	fcppt::reference<
		typename
		std::conditional<
			IsConst,
			list const,
			list
		>::type
	>
	reference;

	typedef
	typename
	std::conditional<
		IsConst,
		typename
		list::const_iterator,
		typename
		list::iterator
	>::type
	iterator;

	range(
		reference,
		sge::sprite::count
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
	reference list_;

	sge::sprite::count size_;
};

}
}
}

#endif
