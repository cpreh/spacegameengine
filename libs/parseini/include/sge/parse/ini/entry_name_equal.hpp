//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_INI_ENTRY_NAME_EQUAL_HPP_INCLUDED
#define SGE_PARSE_INI_ENTRY_NAME_EQUAL_HPP_INCLUDED

#include <sge/parse/ini/entry_fwd.hpp>
#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/detail/symbol.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge::parse::ini
{

class entry_name_equal
{
public:
	SGE_PARSE_INI_DETAIL_SYMBOL
	explicit
	entry_name_equal(
		fcppt::reference<
			sge::parse::ini::entry_name const
		>
	);

	SGE_PARSE_INI_DETAIL_SYMBOL
	bool
	operator()(
		sge::parse::ini::entry const &
	) const;
private:
	fcppt::reference<
		sge::parse::ini::entry_name const
	> name_;
};

}

#endif
