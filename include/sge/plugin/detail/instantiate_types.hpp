/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_PLUGIN_INSTANTIATE_TYPES_HPP_INCLUDED
#define SGE_PLUGIN_INSTANTIATE_TYPES_HPP_INCLUDED

#include <sge/plugin/detail/manager_impl.hpp>
#include <sge/plugin/detail/iterator_impl.hpp>
#include <sge/plugin/detail/plugin_impl.hpp>
#include <sge/plugin/detail/context_impl.hpp>
#include <sge/export.hpp>

#define SGE_PLUGIN_INSTANTIATE_TYPES(x)\
template SGE_SYMBOL sge::plugin::iterator<x> sge::plugin::manager::begin<x>();\
template SGE_SYMBOL sge::plugin::iterator<x> sge::plugin::manager::end<x>();\
template SGE_SYMBOL sge::plugin::iterator<x>::reference sge::plugin::manager::plugin<x>(sge::plugin::manager::size_type);\
template SGE_SYMBOL sge::plugin::manager::size_type sge::plugin::manager::size<x>() const;\
template class sge::plugin::iterator<x>;\
template class sge::plugin::plugin<x>;\
template class sge::plugin::context<x>;

#endif
