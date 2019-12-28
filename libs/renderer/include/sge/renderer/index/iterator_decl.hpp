//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_ITERATOR_DECL_HPP_INCLUDED
#define SGE_RENDERER_INDEX_ITERATOR_DECL_HPP_INCLUDED

#include <sge/renderer/index/is_const_tag.hpp>
#include <sge/renderer/index/is_format.hpp>
#include <sge/renderer/index/iterator_fwd.hpp>
#include <sge/renderer/index/pointer.hpp>
#include <sge/renderer/index/detail/iterator_base.hpp>
#include <fcppt/iterator/base_impl.hpp>


namespace sge
{
namespace renderer
{
namespace index
{

template<
	typename Format,
	typename Constness
>
class iterator final
:
	public
		sge::renderer::index::detail::iterator_base<
			Format,
			Constness
		>
{
	typedef
	sge::renderer::index::detail::iterator_base<
		Format,
		Constness
	>
	base;

	static_assert(
		sge::renderer::index::is_format<
			Format
		>::value
	);

	static_assert(
		sge::renderer::index::is_const_tag<
			Constness
		>::value
	);
public:
	typedef
	typename
	base::value_type
	value_type;

	typedef
	typename
	base::reference
	reference;

	typedef
	sge::renderer::index::pointer<
		Constness
	>
	pointer;

	typedef
	typename
	base::difference_type
	difference_type;

	typedef
	typename
	base::iterator_category
	iterator_category;

	explicit
	iterator(
		pointer
	);

	pointer
	data() const;

	iterator &
	operator+=(
		difference_type
	);

	void
	increment();

	bool
	equal(
		iterator const &
	) const;

	reference
	dereference() const;
private:
	pointer data_;
};

}
}
}

#endif
