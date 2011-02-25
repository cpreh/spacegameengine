/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SHADER_VF_TO_STRING_HPP_INCLUDED
#define SGE_SHADER_VF_TO_STRING_HPP_INCLUDED

#include <sge/shader/format_printer.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <boost/mpl/for_each.hpp>

#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sge
{
namespace shader
{
template<typename Format>
renderer::glsl::string const
vf_to_string()
{
	typedef typename boost::mpl::fold<
		typename Format::parts,
		boost::mpl::vector0<>,
		boost::mpl::copy<
			boost::mpl::_2,
			boost::mpl::back_inserter<
				boost::mpl::_1
			>
		>
	>::type all_elements;
			
	renderer::glsl::string s;
	boost::mpl::for_each<all_elements>(
		shader::format_printer(
			s));
	return s;
}
}
}

#endif
