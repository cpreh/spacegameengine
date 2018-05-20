/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/console/gfx/cursor.hpp>
#include <sge/font/lit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch.hpp>
#include <fcppt/config/external_end.hpp>


TEST_CASE(
	"console cursor",
	"[sge]"
)
{
	sge::console::gfx::cursor c;

	REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("_")
	);

	REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("")
	);

	REQUIRE(
		c.empty()
	);

	c.insert(
		SGE_FONT_LIT('f')
	);

	c.insert(
		SGE_FONT_LIT('o')
	);
	c.insert(
		SGE_FONT_LIT('o')
	);

	REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("foo_")
	);

	REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("foo")
	);

	c.erase_word();

	REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("_")
	);

	REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("")
	);

	c.string(
		SGE_FONT_LIT("bar")
	);

	REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("bar_")
	);

	REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("bar")
	);

	c.left();
	c.left();
	c.left();
	c.left();

	REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("_ar")
	);

	REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("bar")
	);

	c.erase_char();

	REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("_r")
	);

	REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("ar")
	);

	c.erase_char();
	c.erase_char();
	c.erase_char();

	REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("_")
	);

	REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("")
	);

	c.string(
		SGE_FONT_LIT("foo")
	);

	c.left();
	c.left();

	c.insert(
		SGE_FONT_LIT('b')
	);

	REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("fb_o")
	);

	REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("fboo")
	);

	c.left();

	c.insert(
		SGE_FONT_LIT('r')
	);

	REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("fr_oo")
	);

	REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("frboo")
	);

	c.right();
	c.right();
	c.right();
	c.right();
	c.right();
	c.right();
	c.right();

	REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("frboo_")
	);

	REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("frboo")
	);

	c.to_start();

	REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("_rboo")
	);

	REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("frboo")
	);

	c.to_end();

	REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("frboo_")
	);

	REQUIRE(
		c.string()
		==
		SGE_FONT_LIT("frboo")
	);

	c.string(
		SGE_FONT_LIT("foo bar")
	);

	c.left();
	c.left();
	c.left();
	c.left();
	c.erase_word();

	REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("_bar")
	);

	REQUIRE(
		c.string()
		==
		SGE_FONT_LIT(" bar")
	);

	c.erase_word();

	REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("_bar")
	);

	REQUIRE(
		c.string()
		==
		SGE_FONT_LIT(" bar")
	);

	c.string(
		SGE_FONT_LIT("foo")
	);

	c.left();
	c.left();

	REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("f_o")
	);

	c.insert(
		SGE_FONT_LIT('a')
	);

	REQUIRE(
		c.edited()
		==
		SGE_FONT_LIT("fa_o")
	);

	// TODO: Add complete_word tests
}
