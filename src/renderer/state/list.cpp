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


#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/log/global.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/export_symbol.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name.hpp>

sge::renderer::state::list::list()
:
	set_()
{
}

sge::renderer::state::list::list(
	state::any const &_any
)
:
	set_()
{
	set_.insert(
		_any
	);
}

sge::renderer::state::list::~list()
{
}

sge::renderer::state::list const
sge::renderer::state::list::operator()(
	state::any const &_arg
) const
{
	state::list temp(
		*this
	);

	if(
		!temp.set_.insert(
			_arg
		).second
	)
		FCPPT_LOG_WARNING(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("Duplicate renderer state of type \"")
				<< fcppt::type_name(
					_arg.type()
				)
				<< FCPPT_TEXT("\" given!")
		);

	return temp;
}

void
sge::renderer::state::list::overwrite(
	state::any const &_state
)
{
	set_.erase(
		_state
	);

	set_.insert(
		_state
	);
}

template<
	typename T
>
T
sge::renderer::state::list::get() const
{
	set_type::const_iterator const it(
		set_.find(
			T()
		)
	);

	if(
		it == set_.end()
	)
		throw renderer::exception(
			FCPPT_TEXT("renderer::list::get<")
			+ fcppt::type_name(
				typeid(T)
			)
			+ FCPPT_TEXT(">(): state not found!")
		);
	
	return it->get<T>();
}

template<
	typename T,
	typename States
>
T
sge::renderer::state::list::get(
	state::trampoline<T, States> const &_trampoline
) const
{
	set_type::const_iterator const it(
		set_.find(
			_trampoline = T()
		)
	);

	if(
		it == set_.end()
	)
		throw renderer::exception(
			FCPPT_TEXT("renderer::list::get(): state not found!")
		);
	
	return
		it->get<
			typename state::trampoline<
				T,
				States
			>::var_type
		>().value();
}

sge::renderer::state::list::set_type const &
sge::renderer::state::list::values() const
{
	return set_;
}

// TODO: move this out of this file! Make the functions free functions instead!

#define SGE_INSTANTIATE_STATE_LIST_GET(\
	_state\
)\
template FCPPT_EXPORT_SYMBOL \
_state \
sge::renderer::state::list::get<\
	_state\
>() const;

SGE_INSTANTIATE_STATE_LIST_GET(
	sge::renderer::state::cull_mode::type
)

SGE_INSTANTIATE_STATE_LIST_GET(
	sge::renderer::state::depth_func::type
)

SGE_INSTANTIATE_STATE_LIST_GET(
	sge::renderer::state::stencil_func::type
)

SGE_INSTANTIATE_STATE_LIST_GET(
	sge::renderer::state::alpha_func::type
)

SGE_INSTANTIATE_STATE_LIST_GET(
	sge::renderer::state::fog_mode::type
)

SGE_INSTANTIATE_STATE_LIST_GET(
	sge::renderer::state::draw_mode::type
)

SGE_INSTANTIATE_STATE_LIST_GET(
	sge::renderer::state::source_blend_func::type
)

SGE_INSTANTIATE_STATE_LIST_GET(
	sge::renderer::state::dest_blend_func::type
)

#undef SGE_INSTANTIATE_STATE_LIST_GET

#define SGE_INSTANTIATE_STATE_LIST_GET_T(\
	_state\
)\
template FCPPT_EXPORT_SYMBOL _state::base_type \
sge::renderer::state::list::get(\
	sge::renderer::state::trampoline<\
		_state::base_type,\
		_state::available_states::type\
	> const &\
) const;

SGE_INSTANTIATE_STATE_LIST_GET_T(
	sge::renderer::state::int_
)

SGE_INSTANTIATE_STATE_LIST_GET_T(
	sge::renderer::state::uint
)

SGE_INSTANTIATE_STATE_LIST_GET_T(
	sge::renderer::state::bool_
)

SGE_INSTANTIATE_STATE_LIST_GET_T(
	sge::renderer::state::float_
)

SGE_INSTANTIATE_STATE_LIST_GET_T(
	sge::renderer::state::color
)

SGE_INSTANTIATE_STATE_LIST_GET_T(
	sge::renderer::state::stencil_op
)

#undef SGE_INSTANTIATE_STATE_LIST_GET_T
