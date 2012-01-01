/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_MODEL_OBJ_TOKEN_HPP_INCLUDED
#define SGE_SRC_MODEL_OBJ_TOKEN_HPP_INCLUDED

#include <sge/model/obj/index.hpp>
#include <sge/model/obj/scalar.hpp>
#include <sge/src/model/obj/base_iterator.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/spirit/home/lex/lexer/terminals.hpp> // not self contained
#include <boost/spirit/home/lex/lexer/lexertl/token.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace model
{
namespace obj
{

typedef boost::spirit::lex::lexertl::token<
	obj::base_iterator,
	boost::mpl::vector3<
		obj::scalar,
		obj::index,
		fcppt::string
	>
> token;

}
}
}

#endif
