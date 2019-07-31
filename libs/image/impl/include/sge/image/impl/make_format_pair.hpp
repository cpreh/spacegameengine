//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_MAKE_FORMAT_PAIR_HPP_INCLUDED
#define SGE_IMAGE_IMPL_MAKE_FORMAT_PAIR_HPP_INCLUDED


#define SGE_IMAGE_IMPL_MAKE_FORMAT_PAIR(\
	namespace_name,\
	name \
) \
sge::image:: namespace_name ::impl::format_pair<\
	sge::image:: namespace_name ::format:: name, \
	sge::image:: namespace_name :: name ## _format \
>

#endif
