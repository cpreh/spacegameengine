//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/lit.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/font/string.hpp>
#include <sge/gui/click_callback.hpp>
#include <sge/gui/context_ref.hpp>
#include <sge/gui/index.hpp>
#include <sge/gui/index_callback.hpp>
#include <sge/gui/needed_width_from_strings.hpp>
#include <sge/gui/optional_index.hpp>
#include <sge/gui/optional_needed_width.hpp>
#include <sge/gui/string_container.hpp>
#include <sge/gui/text_color.hpp>
#include <sge/gui/style/base.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/choices.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::gui::widget::choices::choices(
	sge::gui::context_ref const _context,
	sge::gui::style::const_reference const _style,
	sge::renderer::device::ffp_ref const _renderer,
	sge::font::object_ref const _font,
	sge::gui::string_container &&_strings,
	sge::gui::optional_index const _opt_index
)
:
	sge::gui::widget::box_container(
		_context,
		sge::gui::widget::reference_alignment_vector(),
		sge::rucksack::axis::x
	),
	strings_(
		std::move(
			_strings
		)
	),
	left_button_(
		_style,
		_renderer,
		_font,
		SGE_FONT_LIT("<"),
		sge::gui::optional_needed_width()
	),
	middle_text_(
		_style,
		_renderer,
		_font,
		fcppt::optional::maybe(
			_opt_index,
			[]{
				return
					sge::font::string();
			},
			[
				this
			](
				sge::gui::index const _index
			)
			{
				return
					this->strings_[
						_index.get()
					];
			}
		),
		_style.get().text_color(),
		sge::gui::optional_needed_width(
			sge::gui::needed_width_from_strings(
				_font.get(),
				this->strings_
			)
		)
	),
	right_button_(
		_style,
		_renderer,
		_font,
		SGE_FONT_LIT(">"),
		sge::gui::optional_needed_width()
	),
	index_{
		_opt_index
	},
	left_connection_{
		left_button_.click(
			sge::gui::click_callback{
				[
					this
				]{
					this->left_clicked();
				}
			}
		)
	},
	right_connection_{
		right_button_.click(
			sge::gui::click_callback{
				[
					this
				]{
					this->right_clicked();
				}
			}
		)
	},
	index_changed_()
{
	this->push_back(
		sge::gui::widget::reference_alignment_pair(
			sge::gui::widget::reference(
				left_button_
			),
			sge::rucksack::alignment::center
		)
	);

	this->push_back(
		sge::gui::widget::reference_alignment_pair(
			sge::gui::widget::reference(
				middle_text_
			),
			sge::rucksack::alignment::center
		)
	);

	this->push_back(
		sge::gui::widget::reference_alignment_pair(
			sge::gui::widget::reference(
				right_button_
			),
			sge::rucksack::alignment::center
		)
	);
}

FCPPT_PP_POP_WARNING

sge::gui::widget::choices::~choices()
= default;

fcppt::signal::auto_connection
sge::gui::widget::choices::change(
	sge::gui::index_callback &&_callback
)
{
	return
		index_changed_.connect(
			std::move(
				_callback
			)
		);
}

sge::gui::optional_index
sge::gui::widget::choices::index() const
{
	return
		index_;
}

void
sge::gui::widget::choices::left_clicked()
{
	this->update_index(
		[
			this
		](
			sge::gui::index const _index
		)
		{
			return
				_index.get()
				==
				0U
				?
					index_
				:
					sge::gui::optional_index(
						sge::gui::index(
							_index.get()
							-
							1U
						)
					)
				;
		}
	);
}

void
sge::gui::widget::choices::right_clicked()
{
	this->update_index(
		[
			this
		](
			sge::gui::index const _index
		)
		{
			return
				_index.get()
				==
				strings_.size() - 1U
				?
					index_
				:
					sge::gui::optional_index(
						sge::gui::index(
							_index.get()
							+
							1U
						)
					)
				;
		}
	);
}

template<
	typename Func
>
void
sge::gui::widget::choices::update_index(
	Func const &_func
)
{
	index_ =
		fcppt::optional::bind(
			index_,
			_func
		);

	fcppt::optional::maybe_void(
		index_,
		[
			this
		](
			sge::gui::index const _index
		)
		{
			middle_text_.value(
				sge::font::string{
					strings_[
						_index.get()
					]
				}
			);

			index_changed_(
				_index
			);
		}
	);
}
