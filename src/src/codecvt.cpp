/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <locale>
#include <vector>
#include "../exception.hpp"
#include "../vector.hpp"
#include "../codecvt.hpp"

namespace
{

template<typename Out, typename In>
std::basic_string<Out> convert(const std::basic_string<In>& s)
{
	typedef std::mbstate_t state_type;
	typedef std::codecvt<In, Out, state_type> codecvt_t;

	std::locale loc;

	const codecvt_t& conv(std::use_facet<codecvt_t>(loc));
	typedef std::vector<Out> buffer_type;
	buffer_type buffer(s.size());

	const In* from = s.data();
	state_type state;
	std::basic_string<Out> ret;
	bool too_little_space = false;
	std::codecvt_base::result result = codecvt_t::partial;
	while(result != std::codecvt_base::ok)
	{
		const In* from_next;
		Out* const to = sge::data(buffer);
		Out* to_next;
		result = conv.out(state,
		                  from, s.data() + s.size(), from_next,
		                  to, to + buffer.size(), to_next);
		switch(result) {
		case std::codecvt_base::noconv:
			throw sge::exception("codecvt::in() noconv!");
		case std::codecvt_base::error:
			throw sge::exception("codecvt::in() error!");
		case std::codecvt_base::partial:
			if(too_little_space)
			{
				buffer.resize(buffer.size()*2);
				too_little_space = false;
			}
			else
				too_little_space = true;
		case std::codecvt_base::ok:
			ret.append(to, to_next); 
			from = from_next;
			break;
		}
	}
	return ret;
}

}

std::string sge::narrow(const std::wstring& s)
{
	return convert<char>(s);
}

std::wstring sge::widen(const std::string& s)
{
	return convert<wchar_t>(s);
}
