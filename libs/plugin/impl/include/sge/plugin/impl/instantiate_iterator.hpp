//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_IMPL_INSTANTIATE_ITERATOR_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_INSTANTIATE_ITERATOR_HPP_INCLUDED

#include <sge/plugin/impl/iterator_impl.hpp>


#define SGE_PLUGIN_IMPL_INSTANTIATE_ITERATOR(\
	plugin_type\
)\
template \
class \
sge::plugin::iterator<\
	plugin_type\
>

#endif
