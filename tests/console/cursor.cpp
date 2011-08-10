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


#include <sge/console/cursor.hpp>
#include <sge/font/text/lit.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(cursor)
{
	sge::console::cursor c;

	BOOST_REQUIRE(
		c.edited(true) ==
			SGE_FONT_TEXT_LIT("_"));

	BOOST_REQUIRE(
		c.edited(false) ==
			SGE_FONT_TEXT_LIT(" "));

	BOOST_REQUIRE(
		c.string() ==
			SGE_FONT_TEXT_LIT(""));

	BOOST_REQUIRE(
		c.empty());

	c.insert(
		SGE_FONT_TEXT_LIT('f'));
	c.insert(
		SGE_FONT_TEXT_LIT('o'));
	c.insert(
		SGE_FONT_TEXT_LIT('o'));

	BOOST_REQUIRE(
		c.edited(true) ==
			SGE_FONT_TEXT_LIT("foo_"));

	BOOST_REQUIRE(
		c.edited(false) ==
			SGE_FONT_TEXT_LIT("foo "));

	BOOST_REQUIRE(
		c.string() ==
			SGE_FONT_TEXT_LIT("foo"));

	c.erase_word();

	BOOST_REQUIRE(
		c.edited(true) ==
			SGE_FONT_TEXT_LIT("_"));

	BOOST_REQUIRE(
		c.edited(false) ==
			SGE_FONT_TEXT_LIT(" "));

	BOOST_REQUIRE(
		c.string() ==
			SGE_FONT_TEXT_LIT(""));

	c.string(
		SGE_FONT_TEXT_LIT("bar"));

	BOOST_REQUIRE(
		c.edited(true) ==
			SGE_FONT_TEXT_LIT("bar_"));

	BOOST_REQUIRE(
		c.edited(false) ==
			SGE_FONT_TEXT_LIT("bar "));

	BOOST_REQUIRE(
		c.string() ==
			SGE_FONT_TEXT_LIT("bar"));

	c.left();
	c.left();
	c.left();
	c.left();

	BOOST_REQUIRE(
		c.edited(true) ==
			SGE_FONT_TEXT_LIT("_ar "));

	BOOST_REQUIRE(
		c.edited(false) ==
			SGE_FONT_TEXT_LIT("bar "));

	BOOST_REQUIRE(
		c.string() ==
			SGE_FONT_TEXT_LIT("bar"));

	c.erase_char();

	BOOST_REQUIRE(
		c.edited(true) ==
			SGE_FONT_TEXT_LIT("_r "));

	BOOST_REQUIRE(
		c.edited(false) ==
			SGE_FONT_TEXT_LIT("ar "));

	BOOST_REQUIRE(
		c.string() ==
			SGE_FONT_TEXT_LIT("ar"));

	c.erase_char();
	c.erase_char();
	c.erase_char();

	BOOST_REQUIRE(
		c.edited(true) ==
			SGE_FONT_TEXT_LIT("_"));

	BOOST_REQUIRE(
		c.edited(false) ==
			SGE_FONT_TEXT_LIT(" "));

	BOOST_REQUIRE(
		c.string() ==
			SGE_FONT_TEXT_LIT(""));

	c.string(
		SGE_FONT_TEXT_LIT("foo"));

	c.left();
	c.left();

	c.insert(
		SGE_FONT_TEXT_LIT('b'));

	BOOST_REQUIRE(
		c.edited(true) ==
			SGE_FONT_TEXT_LIT("fb_o "));

	BOOST_REQUIRE(
		c.edited(false) ==
			SGE_FONT_TEXT_LIT("fboo "));

	BOOST_REQUIRE(
		c.string() ==
			SGE_FONT_TEXT_LIT("fboo"));

	c.left();

	c.insert(
		SGE_FONT_TEXT_LIT('r'));

	BOOST_REQUIRE(
		c.edited(true) ==
			SGE_FONT_TEXT_LIT("fr_oo "));

	BOOST_REQUIRE(
		c.edited(false) ==
			SGE_FONT_TEXT_LIT("frboo "));

	BOOST_REQUIRE(
		c.string() ==
			SGE_FONT_TEXT_LIT("frboo"));

	c.right();
	c.right();
	c.right();
	c.right();
	c.right();
	c.right();
	c.right();

	BOOST_REQUIRE(
		c.edited(true) ==
			SGE_FONT_TEXT_LIT("frboo_"));

	BOOST_REQUIRE(
		c.edited(false) ==
			SGE_FONT_TEXT_LIT("frboo "));

	BOOST_REQUIRE(
		c.string() ==
			SGE_FONT_TEXT_LIT("frboo"));

	c.to_start();

	BOOST_REQUIRE(
		c.edited(true) ==
			SGE_FONT_TEXT_LIT("_rboo "));

	BOOST_REQUIRE(
		c.edited(false) ==
			SGE_FONT_TEXT_LIT("frboo "));

	BOOST_REQUIRE(
		c.string() ==
			SGE_FONT_TEXT_LIT("frboo"));

	BOOST_REQUIRE(
		c.at_start());

	c.to_end();

	BOOST_REQUIRE(
		c.edited(true) ==
			SGE_FONT_TEXT_LIT("frboo_"));

	BOOST_REQUIRE(
		c.edited(false) ==
			SGE_FONT_TEXT_LIT("frboo "));

	BOOST_REQUIRE(
		c.string() ==
			SGE_FONT_TEXT_LIT("frboo"));

	c.string(
		SGE_FONT_TEXT_LIT("foo bar"));
	c.left();
	c.left();
	c.left();
	c.left();
	c.erase_word();

	BOOST_REQUIRE(
		c.edited(true) ==
			SGE_FONT_TEXT_LIT("_bar "));

	BOOST_REQUIRE(
		c.edited(false) ==
			SGE_FONT_TEXT_LIT(" bar "));

	BOOST_REQUIRE(
		c.string() ==
			SGE_FONT_TEXT_LIT(" bar"));

	c.erase_word();

	BOOST_REQUIRE(
		c.edited(true) ==
			SGE_FONT_TEXT_LIT("_bar "));

	BOOST_REQUIRE(
		c.edited(false) ==
			SGE_FONT_TEXT_LIT(" bar "));

	BOOST_REQUIRE(
		c.string() ==
			SGE_FONT_TEXT_LIT(" bar"));

	c.string(
		SGE_FONT_TEXT_LIT("foo"));
	c.left();
	c.left();

	BOOST_REQUIRE(
		c.edited(true) ==
			SGE_FONT_TEXT_LIT("f_o "));

	c.insert(
		SGE_FONT_TEXT_LIT('a'));

	BOOST_REQUIRE(
		c.edited(true) ==
			SGE_FONT_TEXT_LIT("fa_o "));
}
