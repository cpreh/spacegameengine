//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_ITERATOR_DECL_HPP_INCLUDED
#define SGE_RENDERER_INDEX_ITERATOR_DECL_HPP_INCLUDED

#include <sge/renderer/index/iterator_fwd.hpp>
#include <sge/renderer/index/detail/iterator_base.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace index
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Format
>
class iterator final
:
	public sge::renderer::index::detail::iterator_base<
		Format
	>
{
public:
	typedef
	sge::renderer::index::detail::iterator_base<
		Format
	>
	base;

	typedef
	typename
	base::value_type
	value_type;

	typedef
	typename
	base::reference
	reference;

	typedef
	typename
	Format::pointer
	pointer;

	typedef
	typename
	base::difference_type
	difference_type;

	typedef
	typename
	base::iterator_category
	iterator_category;

	friend class boost::iterator_core_access;

	explicit
	iterator(
		pointer
	);

	pointer
	data() const;
private:
	void
	advance(
		difference_type
	);

	void
	increment();

	void
	decrement();

	bool
	equal(
		iterator const &
	) const;

	difference_type
	distance_to(
		iterator const &
	) const;

	reference
	dereference() const;

	pointer data_;
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
