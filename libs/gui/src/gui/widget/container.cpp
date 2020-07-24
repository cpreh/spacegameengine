//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/gui/context.hpp>
#include <sge/gui/context_ref.hpp>
#include <sge/gui/duration.hpp>
#include <sge/gui/get_focus.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/container.hpp>
#include <sge/gui/widget/optional_focus.hpp>
#include <sge/gui/widget/optional_focus_ref.hpp>
#include <sge/gui/widget/optional_ref.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_vector.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/reference.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_comparison.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/algorithm/remove_if.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/math/box/contains_point.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/optional/comparison.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::gui::widget::container::container(
	sge::gui::context_ref const _context,
	sge::gui::widget::reference_vector &&_widgets,
	sge::rucksack::widget::reference const _layout
)
:
	sge::gui::widget::base(),
	context_(
		_context
	),
	widgets_(
		std::move(
			_widgets
		)
	),
	layout_(
		_layout
	)
{
	this->foreach_widget(
		[
			this
		](
			sge::gui::widget::base &_widget
		)
		{
			_widget.parent(
				sge::gui::widget::optional_ref(
					fcppt::reference_to_base<
						sge::gui::widget::base
					>(
						fcppt::make_ref(
							*this
						)
					)
				)
			);

			return
				sge::gui::widget::container::foreach_result::continue_;
		}
	);
}

sge::gui::widget::container::~container()
{
	this->foreach_widget(
		[
			this
		](
			sge::gui::widget::base &_widget
		)
		{
			_widget.parent(
				sge::gui::widget::optional_ref()
			);

			this->context_.get().destroy(
				_widget
			);

			return
				sge::gui::widget::container::foreach_result::continue_;
		}
	);
}

sge::rucksack::widget::base &
sge::gui::widget::container::layout()
{
	return
		layout_.get();
}

void
sge::gui::widget::container::push_front_widget(
	sge::gui::widget::reference const _widget
)
{
	this->insert_widget(
		widgets_.begin(),
		_widget
	);
}

void
sge::gui::widget::container::pop_front_widget()
{
	this->erase_widget(
		widgets_.begin()
	);
}

void
sge::gui::widget::container::push_back_widget(
	sge::gui::widget::reference const _widget
)
{
	this->insert_widget(
		widgets_.end(),
		_widget
	);
}

void
sge::gui::widget::container::pop_back_widget()
{
	this->erase_widget(
		std::prev(
			widgets_.end()
		)
	);
}

void
sge::gui::widget::container::replace_widgets(
	sge::gui::widget::reference_vector::size_type const _pos,
	sge::gui::widget::reference const _widget
)
{
	this->insert_widget(
		this->erase_widget(
			std::next(
				widgets_.begin(),
				fcppt::cast::to_signed(
					_pos
				)
			)
		),
		_widget
	);
}

void
sge::gui::widget::container::clear_widgets()
{
	for(
		auto it(
			widgets_.begin()
		);
		it != widgets_.end();
		it =
			this->erase_widget(
				it
			)
	)
	{
	}
}

void
sge::gui::widget::container::insert_widget(
	sge::gui::widget::reference_vector::iterator const _pos,
	sge::gui::widget::reference const _widget
)
{
	widgets_.insert(
		_pos,
		_widget
	);

	_widget.get().parent(
		sge::gui::widget::optional_ref(
			fcppt::reference_to_base<
				sge::gui::widget::base
			>(
				fcppt::make_ref(
					*this
				)
			)
		)
	);
}

sge::gui::widget::reference_vector::iterator
sge::gui::widget::container::erase_widget(
	sge::gui::widget::reference_vector::iterator const _pos
)
{
	_pos->get().parent(
		sge::gui::widget::optional_ref()
	);

	return
		widgets_.erase(
			_pos
		);
}

void
sge::gui::widget::container::on_update(
	sge::gui::duration const _duration
)
{
	this->foreach_widget(
		[
			_duration
		](
			sge::gui::widget::base &_widget
		)
		{
			_widget.on_update(
				_duration
			);

			return
				sge::gui::widget::container::foreach_result::continue_;
		}
	);
}

void
sge::gui::widget::container::on_draw(
	sge::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context
)
{
	this->foreach_widget(
		[
			&_renderer,
			&_context
		](
			sge::gui::widget::base &_widget
		)
		{
			_widget.on_draw(
				_renderer,
				_context
			);

			return
				sge::gui::widget::container::foreach_result::continue_;
		}
	);
}

sge::gui::get_focus
sge::gui::widget::container::on_click(
	sge::rucksack::vector const &_pos
)
{
	if(
		!this->enabled()
	)
	{
		return
			sge::gui::get_focus(
				false
			);
	}

	this->foreach_widget(
		[
			this,
			_pos
		](
			sge::gui::widget::base &_widget
		)
		{
			if(
				!fcppt::math::box::contains_point(
					_widget.layout().area(),
					_pos
				)
			)
			{
				return
					sge::gui::widget::container::foreach_result::continue_;
			}

			if(
				_widget.on_click(
					_pos
				)
				==
				sge::gui::get_focus{
					true
				}
			)
			{
				this->context_.get().focus(
					fcppt::make_ref(
						_widget
					)
				);
			}

			return
				sge::gui::widget::container::foreach_result::abort;
		}
	);

	return
		sge::gui::get_focus(
			false
		);
}

sge::gui::widget::optional_ref
sge::gui::widget::container::on_tab(
	sge::gui::widget::optional_focus_ref const _focus
)
{
	for(
		auto &ref
		:
		widgets_
	)
	{
		sge::gui::widget::optional_ref const result(
			ref.get().on_tab(
				_focus
			)
		);

		if(
			!result.has_value()
		)
		{
			continue;
		}

		if(
			!_focus.get().get().has_value()
		)
		{
			return
				result;
		}

		if(
			_focus.get().get()
			==
			result
		)
		{
			_focus.get() =
				sge::gui::widget::optional_focus(
					sge::gui::widget::optional_ref()
				);
		}
	}

	return
		sge::gui::widget::optional_ref();
}

void
sge::gui::widget::container::unregister(
	sge::gui::widget::base const &_widget
)
{
	this->context_.get().destroy(
		_widget
	);

	fcppt::algorithm::remove_if(
		widgets_,
		[
			&_widget
		](
			sge::gui::widget::reference const _ref
		)
		{
			return
				&_ref.get()
				==
				&_widget;
		}
	);
}

template<
	typename Function
>
void
sge::gui::widget::container::foreach_widget(
	Function const &_function
)
{
	for(
		auto &ref
		:
		widgets_
	)
	{
		if(
			_function(
				ref.get()
			)
			==
			sge::gui::widget::container::foreach_result::abort
		)
		{
			return;
		}
	}
}
