//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_INTRUSIVE_DETAIL_LIST_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_DETAIL_LIST_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/intrusive/list.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge::sprite::intrusive::detail
{

template<
	typename Choices
>
using
list
=
boost::intrusive::list<
	sge::sprite::object<
		Choices
	>,
	boost::intrusive::constant_time_size<
		false
	>
>;

}

#endif
