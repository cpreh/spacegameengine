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


#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/gui/click_callback.hpp>
#include <sge/gui/context_fwd.hpp>
#include <sge/gui/optional_needed_width.hpp>
#include <sge/gui/impl/relayout_ancestor.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/button.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/gui/widget/reference_name_pair.hpp>
#include <sge/gui/widget/reference_name_vector.hpp>
#include <sge/gui/widget/tab.hpp>
#include <sge/gui/widget/unique_ptr.hpp>
#include <sge/gui/widget/unique_ptr_vector.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/container/maybe_front.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/auto_connection.hpp>


sge::gui::widget::tab::tab(
	sge::gui::context &_context,
	sge::gui::style::base const &_style,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sge::gui::widget::reference_name_vector const &_widgets
)
:
	sge::gui::widget::box_container(
		_context,
		sge::gui::widget::reference_alignment_vector(),
		sge::rucksack::axis::y
	),
	top_buttons_(
		fcppt::algorithm::map<
			sge::gui::widget::unique_ptr_vector
		>(
			_widgets,
			[
				&_style,
				&_renderer,
				&_font,
				this
			](
				sge::gui::widget::reference_name_pair const &_pair
			)
			{
				class gui_button
				:
					public sge::gui::widget::button
				{
					FCPPT_NONCOPYABLE(
						gui_button
					);
				public:
					gui_button(
						sge::gui::style::base const &_style_arg,
						sge::renderer::device::ffp &_renderer_arg,
						sge::font::object &_font_arg,
						sge::font::string const &_name,
						sge::gui::widget::reference const _widget,
						sge::gui::widget::tab &_self
					)
					:
						sge::gui::widget::button(
							_style_arg,
							_renderer_arg,
							_font_arg,
							_name,
							sge::gui::optional_needed_width()
						),
						click_connection_(
							this->click(
								sge::gui::click_callback{
									[
										_widget,
										&_self
									]
									()
									{
										_self.replace(
											1u,
											sge::gui::widget::reference_alignment_pair(
												_widget,
												sge::rucksack::alignment::left_or_top
											)
										);

										sge::gui::impl::relayout_ancestor(
											_self
										);
									}
								}
							)
						)
					{
					}

					~gui_button()
					{
					}
				private:
					fcppt::signal::auto_connection const click_connection_;
				};

				return
					fcppt::unique_ptr_to_base<
						sge::gui::widget::base
					>(
						fcppt::make_unique_ptr<
							gui_button
						>(
							_style,
							_renderer,
							_font,
							_pair.name(),
							_pair.reference(),
							*this
						)
					);
			}
		)
	),
	top_buttons_box_(
		_context,
		fcppt::algorithm::map<
			sge::gui::widget::reference_alignment_vector
		>(
			top_buttons_,
			[](
				sge::gui::widget::unique_ptr const &_widget
			)
			{
				return
					sge::gui::widget::reference_alignment_pair(
						sge::gui::widget::reference(
							*_widget
						),
						sge::rucksack::alignment::left_or_top
					);
			}
		),
		sge::rucksack::axis::x
	)
{
	this->push_back(
		sge::gui::widget::reference_alignment_pair(
			sge::gui::widget::reference(
				top_buttons_box_
			),
			sge::rucksack::alignment::left_or_top
		)
	);

	fcppt::optional::maybe_void(
		fcppt::container::maybe_front(
			_widgets
		),
		[
			this
		](
			fcppt::reference<
				sge::gui::widget::reference_name_pair const
			> const _front
		)
		{
			this->push_back(
				sge::gui::widget::reference_alignment_pair(
					_front.get().reference(),
					sge::rucksack::alignment::left_or_top
				)
			);
		}
	);
}

sge::gui::widget::tab::~tab()
{
}
