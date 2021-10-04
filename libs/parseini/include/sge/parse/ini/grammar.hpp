//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_INI_GRAMMAR_HPP_INCLUDED
#define SGE_PARSE_INI_GRAMMAR_HPP_INCLUDED

#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/grammar_base_fwd.hpp>
#include <sge/parse/ini/grammar_fwd.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/section_vector.hpp>
#include <sge/parse/ini/start.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/parse/grammar_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace sge::parse::ini
{

class grammar
:
	public
		sge::parse::ini::grammar_base
{
	FCPPT_NONMOVABLE(
		grammar
	);
public:
	grammar();

	~grammar();
private:
	base_type<
		sge::parse::ini::entry
	>
	entry_;

	base_type<
		std::string
	>
	header_;

	base_type<
		sge::parse::ini::section
	>
	section_;

	base_type<
		sge::parse::ini::section_vector
	>
	section_vector_;

	base_type<
		sge::parse::ini::start
	>
	ini_;
};

}

#endif
