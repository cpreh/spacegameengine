//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_ITERATOR_DECL_HPP_INCLUDED
#define SGE_RENDERER_VF_ITERATOR_DECL_HPP_INCLUDED

#include <sge/renderer/vf/iterator_fwd.hpp>
#include <sge/renderer/vf/pointer.hpp>
#include <sge/renderer/vf/view_fwd.hpp>
#include <sge/renderer/vf/detail/iterator_base.hpp>


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

	typedef value_type vertex_type;

	typedef
	sge::renderer::vf::pointer<
		Constness
	>
	internal_pointer;

	static
	difference_type
	stride();

	explicit
	iterator(
		internal_pointer
	);

	void
	increment();

	bool
	equal(
		iterator const &
	) const;

	vertex_type
	dereference() const;

	iterator &
	operator+=(
		difference_type
	);
private:
	internal_pointer data_;

	template<
		typename,
		typename
	> friend class sge::renderer::vf::view;
};

}
}
}

#endif
