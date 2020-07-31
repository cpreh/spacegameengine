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
	using
	list
	=
	sge::sprite::intrusive::detail::list<
		Choices
	>;
public:
	using
	reference
	=
	fcppt::reference<
		std::conditional_t<
			IsConst,
			list const,
			list
		>
	>;

	using
	iterator
	=
	std::conditional_t<
		IsConst,
		typename
		list::const_iterator,
		typename
		list::iterator
	>;

	range(
		reference,
		sge::sprite::count
	);

	[[nodiscard]]
	iterator
	begin() const;

	[[nodiscard]]
	iterator
	end() const;

	[[nodiscard]]
	sge::sprite::count
	size() const;

	[[nodiscard]]
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
