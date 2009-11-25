/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/x11/class_hint.hpp>
#include <sge/noncopyable.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/iconv.hpp>

class sge::x11::class_hint::impl {
public:
	SGE_NONCOPYABLE(impl)
public:
	impl();
	~impl();
	XClassHint *get() const;
private:
	XClassHint *const hint;
};


sge::x11::class_hint::class_hint(
	string const &app_name_,
	string const &res_name_)
:
	impl_(
		new impl()),
	app_name(
		iconv(
			app_name_)),
	res_name(
		iconv(
			res_name_))
{
	XClassHint *const hint(
		get());

	hint->res_name = const_cast<char *>(app_name.c_str());
	hint->res_class = const_cast<char *>(res_name.c_str());
}

sge::x11::class_hint::~class_hint()
{}

XClassHint *
sge::x11::class_hint::get() const
{
	return impl_->get();
}

sge::x11::class_hint::impl::impl()
:
	hint(
		XAllocClassHint())
{
	if(!hint)
		throw exception(
			SGE_TEXT("XAllocClassHint() failed!"));
}

sge::x11::class_hint::impl::~impl()
{
	XFree(hint);
}

XClassHint *
sge::x11::class_hint::impl::get() const
{
	return hint;
}
