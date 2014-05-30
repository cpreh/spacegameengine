/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_CONSOLE_FUNCTION_HPP_INCLUDED
#define SGE_CONSOLE_FUNCTION_HPP_INCLUDED

#include <sge/console/function_fwd.hpp>
#include <sge/console/long_description.hpp>
#include <sge/console/short_description.hpp>
#include <sge/console/signal_fwd.hpp>
#include <sge/console/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/signal/unregister/base_decl.hpp>


namespace sge
{
namespace console
{

class function
{
	FCPPT_NONCOPYABLE(
		function
	);
public:
	SGE_CONSOLE_SYMBOL
	function(
		sge::console::short_description const &,
		sge::console::long_description const &
	);

	SGE_CONSOLE_SYMBOL
	function(
		function &&
	);

	SGE_CONSOLE_SYMBOL
	function &
	operator=(
		function &&
	);

	SGE_CONSOLE_SYMBOL
	~function();

	SGE_CONSOLE_SYMBOL
	sge::console::signal &
	signal();

	SGE_CONSOLE_SYMBOL
	sge::console::short_description const &
	short_description() const;

	SGE_CONSOLE_SYMBOL
	sge::console::long_description const &
	long_description() const;
private:
	sge::console::signal signal_;

	sge::console::short_description short_description_;

	sge::console::long_description long_description_;
};

}
}

#endif
