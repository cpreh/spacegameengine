//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/console/gfx/cursor.hpp>
#include <sge/font/lit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
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
