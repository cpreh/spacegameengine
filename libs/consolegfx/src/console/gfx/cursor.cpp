//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/console/function_map.hpp>
#include <sge/console/prefix.hpp>
#include <sge/console/gfx/cursor.hpp>
#include <sge/font/char_type.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/string.hpp>
#include <fcppt/const.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/container/at_optional.hpp>
#include <fcppt/container/maybe_front.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


sge::console::gfx::cursor::cursor()
:
	line_(),
	pos_{
		0u
	}
{
}

sge::console::gfx::cursor::~cursor()
{
}

sge::font::string
sge::console::gfx::cursor::edited() const
{
	sge::font::string result(
		line_
	);

	constexpr sge::font::char_type const caret{
		SGE_FONT_LIT('_')
	};

	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_CLANG_WARNING(-Wunused-lambda-capture)

	fcppt::optional::maybe(
		fcppt::container::at_optional(
			result,
			pos_
		),
		[
			caret,
			&result
		]{
			result.push_back(
				caret
			);
		},
		[
			caret
		](
			fcppt::reference<
				sge::font::char_type
			> const _ref
		)
		{
			_ref.get() =
				caret;
		}
	);

	FCPPT_PP_POP_WARNING

	return
		result;
}

sge::font::string const &
sge::console::gfx::cursor::string() const
{
	return
		line_;
}

void
sge::console::gfx::cursor::string(
	sge::font::string const &_line
)
{
	line_ =
		_line;

	pos_ =
		line_.length();
}

void
sge::console::gfx::cursor::erase_word()
{
	// TODO: Move this out of here
	typedef
	fcppt::optional::object<
		size_type
	>
	optional_index;

	auto const rfind(
		[
			this
		](
			sge::font::char_type const _char,
			size_type const _index
		)
		->
		optional_index
		{
			size_type const index{
				line_.rfind(
					_char,
					_index
				)
			};

			return
				index
				==
				sge::font::string::npos
				?
					optional_index()
				:
					optional_index(
						index
					)
				;
		}
	);

	if(
		pos_
		==
		0u
	)
		return;

	size_type const index{
		fcppt::optional::from(
			rfind(
				SGE_FONT_LIT(' '),
				pos_
				-
				1u
			),
			[]{
				return
					fcppt::literal<
						size_type
					>(
						0u
					);
			}
		)
	};

	line_.erase(
		index,
		pos_
		-
		index
	);

	pos_ =
		index;
}

void
sge::console::gfx::cursor::erase_char()
{
	line_.erase(
		pos_,
		1u
	);
}

void
sge::console::gfx::cursor::left()
{
	if(
		pos_
		!=
		0u
	)
		--pos_;
}

void
sge::console::gfx::cursor::right()
{
	if(
		pos_
		!=
		line_.length()
	)
		++pos_;
}

void
sge::console::gfx::cursor::to_start()
{
	pos_ =
		0u;
}

void
sge::console::gfx::cursor::to_end()
{
	pos_ =
		line_.length();
}

bool
sge::console::gfx::cursor::empty() const
{
	return
		line_.empty();
}

void
sge::console::gfx::cursor::insert(
	sge::font::char_type const _char
)
{
	line_.insert(
		pos_,
		1u,
		_char
	);

	++pos_;
}

void
sge::console::gfx::cursor::complete_word(
	sge::console::prefix const _prefix,
	sge::console::function_map const &_map
)
{
	if(
		fcppt::optional::maybe(
			fcppt::container::maybe_front(
				line_
			),
			fcppt::const_(
				true
			),
			[
				_prefix
			](
				fcppt::reference<
					sge::font::char_type
				> const _front
			)
			{
				return
					_front.get()
					!=
					_prefix.get();
			}
		)
	)
		return;

	typedef
	fcppt::optional::reference<
		sge::font::string const
	>
	optional_string_ref;

	// TODO: Move this out of here
	auto const upper_bound(
		[
			&_map
		](
			sge::font::string const &_string
		)
		->
		optional_string_ref
		{
			sge::console::function_map::const_iterator const it{
				_map.upper_bound(
					_string
				)
			};

			return
				it
				==
				_map.end()
				?
					optional_string_ref{}
				:
					optional_string_ref{
						fcppt::make_cref(
							it->first
						)
					}
				;
		}
	);

	constexpr size_type const start_pos{
		1u
	};

	sge::font::string const search_string(
		line_.substr(
			start_pos,
			pos_
			-
			start_pos
		)
	);

	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_CLANG_WARNING(-Wunused-lambda-capture)

	fcppt::optional::maybe_void(
		upper_bound(
			search_string
		),
		[
			start_pos,
			&search_string,
			this
		](
			fcppt::reference<
				sge::font::string const
			> const _string
		)
		{
			auto const is_prefix_of(
				[](
					sge::font::string const &_search,
					sge::font::string const &_whole
				)
				{
					return
						_search.size()
						<=
						_whole.size()
						&&
						_whole.substr(
							0u,
							_search.size()
						)
						==
						_search;
				}
			);

			if(
				!search_string.empty()
				&&
				is_prefix_of(
					search_string,
					_string.get()
				)
			)
			{
				line_.replace(
					start_pos,
					search_string.size(),
					_string.get()
				);

				pos_ =
					start_pos
					+
					_string.get().size();

			}
		}
	);

	FCPPT_PP_POP_WARNING
}
