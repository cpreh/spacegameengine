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


#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/entry_vector.hpp>
#include <sge/parse/ini/parse_string.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/section_vector.hpp>
#include <sge/parse/ini/start.hpp>
#include <sge/parse/ini/value.hpp>
#include <fcppt/strong_typedef_comparison.hpp>
#include <fcppt/catch/convert.hpp>
#include <fcppt/catch/either.hpp>
#include <fcppt/catch/strong_typedef.hpp>
#include <fcppt/either/comparison.hpp>
#include <fcppt/parse/make_success.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <string>
#include <tuple>
#include <fcppt/config/external_end.hpp>


namespace Catch
{

template<>
struct StringMaker<
	sge::parse::ini::start
>
{
	static
	std::string
	convert(
		sge::parse::ini::start const &_value
	)
	{
		return
			fcppt::catch_::convert(
				_value.sections
			);
	}
};

template<>
struct StringMaker<
	sge::parse::ini::section
>
{
	static
	std::string
	convert(
		sge::parse::ini::section const &_value
	)
	{
		return
			fcppt::catch_::convert(
				std::make_tuple(
					_value.name,
					_value.entries
				)
			);
	}
};

template<>
struct StringMaker<
	sge::parse::ini::entry
>
{
	static
	std::string
	convert(
		sge::parse::ini::entry const &_value
	)
	{
		return
			fcppt::catch_::convert(
				std::make_tuple(
					_value.name,
					_value.value
				)
			);
	}
};

}

TEST_CASE(
	"parse_ini",
	"[sge]"
)
{
	CHECK(
		sge::parse::ini::parse_string(
			std::string{
				"[section]\n"
					"foo1 = bar1\n"
				"[sectionfoo]\n"
					"foo3 = bar3\n"
					"foo4=bar4\n"
					"\n"
					"empty=\n"
			}
		)
		==
		fcppt::parse::make_success<
			char
		>(
			sge::parse::ini::start{
				sge::parse::ini::section_vector{
					sge::parse::ini::section{
						sge::parse::ini::section_name{
							std::string{"section"}
						},
						sge::parse::ini::entry_vector{
							sge::parse::ini::entry{
								sge::parse::ini::entry_name{
									std::string{"foo1"}
								},
								sge::parse::ini::value{
									std::string{"bar1"}
								}
							}
						}
					},
					sge::parse::ini::section{
						sge::parse::ini::section_name{
							std::string{"sectionfoo"}
						},
						sge::parse::ini::entry_vector{
							sge::parse::ini::entry{
								sge::parse::ini::entry_name{
									std::string{"foo3"}
								},
								sge::parse::ini::value{
									std::string{"bar3"}
								}
							},
							sge::parse::ini::entry{
								sge::parse::ini::entry_name{
									std::string{"foo4"}
								},
								sge::parse::ini::value{
									std::string{"bar4"}
								}
							},
							sge::parse::ini::entry{
								sge::parse::ini::entry_name{
									std::string{"empty"}
								},
								sge::parse::ini::value{
									std::string{}
								}
							}
						}
					}
				}
			}
		)
	);
}

TEST_CASE(
	"parse_ini error",
	"[sge]"
)
{
	CHECK(
		sge::parse::ini::parse_string(
			std::string{"garbage"}
		).has_failure()
	);

	CHECK(
		sge::parse::ini::parse_string(
			std::string{"[foo] missing_newline"}
		).has_failure()
	);

	CHECK(
		sge::parse::ini::parse_string(
			std::string{"[foo]\n invalid name=foo"}
		).has_failure()
	);
}
