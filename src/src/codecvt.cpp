/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <locale>
#include "../raw_vector_impl.hpp"
#include "../exception.hpp"
#include "../vector.hpp"
#include "../codecvt.hpp"

namespace
{

typedef std::mbstate_t state_type;
typedef std::codecvt<wchar_t, char, state_type> codecvt_t;

template<typename OutCh> struct call_traits;

template<> struct call_traits<char> {
	static std::codecvt_base::result conv(const codecvt_t& cvt,
	                                      state_type& state,
	                                      wchar_t const *const from,
	                                      wchar_t const *const from_end,
	                                      wchar_t const*& from_next,
	                                      char *const to,
	                                      char *const to_limit,
	                                      char*& to_next)
	{
		return cvt.out(state, from, from_end, from_next, to, to_limit, to_next);
	}
};

template<> struct call_traits<wchar_t> {
	static std::codecvt_base::result conv(const codecvt_t& cvt,
	                                      state_type& state,
	                                      char const *const from,
	                                      char const *const from_end,
	                                      char const*& from_next,
	                                      wchar_t *const to,
	                                      wchar_t *const to_limit,
	                                      wchar_t*& to_next)
	{
		return cvt.in(state, from, from_end, from_next, to, to_limit, to_next);
	}
};

std::locale get_locale()
{
	static std::locale loc;
	return loc;
}

template<typename Out, typename In>
std::basic_string<Out> convert(const std::basic_string<In>& s)
{
	std::locale loc(get_locale());

	const codecvt_t& conv(std::use_facet<codecvt_t>(loc));
	typedef sge::raw_vector<Out> buffer_type;
	buffer_type buffer(s.size());

	const In* from = s.data();
	state_type state;
	std::basic_string<Out> ret;
	bool too_little_space = false;
	std::codecvt_base::result result = codecvt_t::partial;
	while(result != std::codecvt_base::ok)
	{
		const In* from_next;
		Out* const to = buffer.data();
		Out* to_next;
		result = call_traits<Out>::conv(conv, state,
		                                from, s.data() + s.size(), from_next,
		                                to, to + buffer.size(), to_next);
		switch(result) {
		case std::codecvt_base::noconv:
			throw sge::exception(SGE_TEXT("codecvt: noconv!"));
		case std::codecvt_base::error:
			throw sge::exception(SGE_TEXT("codecvt: error!"));
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
