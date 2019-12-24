//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_ITERATOR_DECL_HPP_INCLUDED
#define SGE_RENDERER_VF_ITERATOR_DECL_HPP_INCLUDED

#include <sge/renderer/vf/iterator_fwd.hpp>
#include <sge/renderer/vf/detail/iterator_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{

template<
	typename Part,
	typename Constness
>
class iterator final
:
	public
		sge::renderer::vf::detail::iterator_base<
			Part,
			Constness
		>
{
	typedef
	sge::renderer::vf::detail::iterator_base<
		Part,
		Constness
	>
	base;
public:
	typedef typename base::value_type value_type;

	typedef typename base::reference reference;

	typedef typename base::pointer pointer;

	typedef typename base::difference_type difference_type;

	typedef typename base::iterator_category iterator_category;
private:
	typedef value_type vertex_type;

	typedef typename vertex_type::pointer internal_pointer;

	static
	difference_type
	stride();

	explicit
	iterator(
		internal_pointer
	);

	friend class boost::iterator_core_access;

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

	vertex_type
	dereference() const;

	internal_pointer data_;

	template<
		typename,
		typename
	> friend class view;
};

}
}
}

#endif
