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


#ifndef SGE_STRING_HPP_INCLUDED
#define SGE_STRING_HPP_INCLUDED

#include <memory>
#include <string>
//#include <ostream>
//#include <istream>
//#include "typeswitch.hpp"
#include "unicode.hpp"

namespace sge
{


typedef std::basic_string<uchar_t> string;

/*template<typename Alloc = std::allocator<uchar_t> >
class string {
	typedef std::basic_string<uchar_t, Alloc> impl_type;
public:
	typedef typename impl_type::traits_type traits_type;
	typedef typename impl_type::value_type value_type;
	typedef typename Alloc allocator_type;
	typedef typename impl_type::size_type size_type;
	typedef typename impl_type::difference_type difference_type;
	typedef typename impl_type::reference reference;
	typedef typename impl_type::const_reference const_reference;
	typedef typename impl_type::pointer pointer;
	typedef typename impl_type::const_pointer const_pointer;
	typedef typename impl_type::iterator iterator;
	typedef typename impl_type::const_iterator const_iterator;
	typedef typename impl_type::reverse_iterator reverse_iterator;
	typedef typename impl_type::const_reverse_iterator const_reverse_iterator;

	string();
	explicit string(const Alloc& a);
	string(const std::string& s, std::string::size_type pos = 0, std::string::size_type n = npos, const allocator_type& alloc = allocator_type());
	string(std::string::const_pointer p, std::string::size_type n, const allocator_type& alloc = allocator_type());
	string(std::string::const_pointer p, const allocator_type& alloc = allocator_type());
	string(std::string::size_type n, std::string::value_type c, const allocator_type& alloc = allocator_type());
	template<typename In>
	string(In beg, In end, const allocator_type& alloc = allocator_type());
	
	explicit string(const allocator_type& alloc = allocator_type());
	string(const string& s, size_type pos = 0, size_type n = npos, const allocator_type& alloc = allocator_type());
	string(const_pointer p, size_type n, const allocator_type& alloc = allocator_type());
	string(const_pointer p, const allocator_type& alloc = allocator_type());
	string(size_type n, value_type c, const allocator_type& alloc = allocator_type());
	
	string& operator=(const string&);
	string& operator=(const_pointer);
	string& operator=(value_type);

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	reverse_iterator rbegin();
	reverse_iterator rend();
	const_reverse_iterator rbegin();
	const_reverse_iterator rend();

	size_type size() const;
	size_type length() const;
	size_type max_size() const;
	size_type capacity() const;

	void clear();
	bool empty() const;

	const_reference operator[](size_type pos) const;
	reference operator[](size_type pos);
	const_reference at(size_type pos) const;
	reference at(size_type pos) const;

	basic_string& operator+=(const basic_string&);
	basic_string& operator+=(const_pointer);
	basic_string& operator+=(value_type);

	string& assign(const_pointer);
	string& assign(size_type n, value_type);
	string& assign(const_pointer p, size_type n);
	string& assign(const string&, size_type pos, size_type n);
	template<typename In>
	string& assign(In beg, In end);
	
	string& append(size_type n, value_type c);
	string& append(const_pointer);
	string& append(const_pointer, size_type n);
	string& append(const string&);
	string& append(const string&, size_type pos, size_type n);
	template<typename In>
	string& append(In beg, In end);

	void push_back(value_type);

	string& insert(size_type pos, const_pointer p, size_type n);
	void insert(iterator, size_type n, value_type);
	template<typename In>
	void insert(iterator dest, In beg, In end);
	string& insert(size_type pos1, const string&);
	string& insert(size_type pos1, const string&, size_type pos2, size_type n);
	string& insert(size_type pos, const_pointer);
	string& insert(size_type pos, size_type n, value_type);
	iterator insert(iterator, value_type);

	string& erase(size_type pos = 0, size_type n = npos);
	iterator erase(iterator);
	iterator erase(iterator beg, iterator end);

	string& replace(size_type pos, size_type n, const string&);
	string& replace(size_type pos1, size_type n1, const string&, size_type pos2, size_type n2);
	string& replace(size_type pos, size_type n1, const_pointer);
	string& replace(size_type pos, size_type n1, size_type n2, value_type);
	string& replace(iterator beg, iterator end, const string&);
	string& replace(iterator beg, iterator end, const_pointer, size_type n);
	string& replace(iterator beg, iterator end, const_pointer);
	string& replace(iterator beg, iterator end, size_type n, value_type);
	string& replace(iterator beg, iterator end, const_pointer k1, const_pointer k2);
	string& replace(iterator i1, iterator i2, iterator k1, iterator k2);
	string& replace(iterator i1, iterator i2, const_iterator k1, const_iterator k2);
	template<typename In>
	string& replace(iterator beg1, iterator end1, In beg2, In end2);
	
	string& replace(size_type pos, size_type n1, const_pointer p, size_type n2);
	const_pointer c_str() const;
	const_pointer data() const;
	
	allocator_type get_allocator() const;

	void reserve(size_type);
	void swap(string&);
	void resize(size_type n, value_type c = value_type());
	size_type copy(pointer, size_type n, size_type pos) const; // is this standard?

	size_type find(const_pointer, size_type pos, size_type n) const;
	size_type find(const basic_string&, size_type pos = 0);
	size_type find(const_pointer, size_type pos = 0);
	size_type find(value_type, size_type pos) const;

	size_type rfind(const_pointer, size_type pos, size_type n) const;
	size_type rfind(value_type, size_type pos) const;
	size_type rfind(const string&, size_type pos = npos) const;
	size_type rfind(const_pointer, size_type pos = npos) const;

	size_type find_first_of(const_pointer, size_type pos, size_type n) const;
	size_type find_first_of(const string&, size_type pos = 0) const;
	size_type find_first_of(const_pointer, size_type pos = 0) const;
	size_type find_first_of(value_type, size_type pos = 0) const;

	size_type find_last_of(const_pointer, size_type pos, size_type n) const;	size_type find_last_of(const string&, size_type pos = npos) const;
	size_type find_last_of(const_pointer, size_type pos = npos) const;
	size_type find_last_of(value_type, size_type pos = npos) const;

	size_type find_first_not_of(const_pointer, size_type pos, size_type n) const;
	size_type find_first_not_of(value_type, size_type pos) const;
	size_type find_first_not_of(const string&, size_type pos = 0) const;
	size_type find_first_not_of(const_pointer, size_type pos = 0) const;

	size_type find_last_not_of(const_pointer, size_type pos, size_type n) const;
	size_type find_last_not_of(value_type, size_type pos) const;
	size_type find_last_not_of(const string&, size_type pos = npos) const;
	size_type find_last_not_of(const_pointer, size_type pos = npos) const;

	int compare(const string&) const;
	int compare(size_type pos, size_type n, const string&) const;
	int compare(size_type pos1, size_type n1, const string&, size_type pos2, size_type n2) const;
	int compare(const_pointer) const;
	int compare(size_type pos, size_type n1, const_pointer) const;
	int compare(size_type pos, size_type n1, const_pointer, size_type n2) const;

	string substr(size_type first = 0, size_type count = npos) const;
private:
	ustring s;
};

string operator+(string::const_pointer, const string&);
string operator+(const string&, string::const_pointer);
string operator+(string::value_type, const string&);
string operator+(const string&, string::value_type);
string operator+(const string&, const string&);

bool operator==(const string&, const string&);
bool operator==(string::const_pointer, const string&);
bool operator==(const string&, string::const_pointer);

bool operator!=(const string&, const string&);
bool operator!=(string::const_pointer, const string&);
bool operator!=(const string&, string::const_pointer);

bool operator<(const string&, const string&);
bool operator<(const string&, string::const_pointer);
bool operator<(string::const_pointer, const string&);

bool operator>(const string&, const string&);
bool operator>(const string&, string::const_pointer);
bool operator>(string::const_pointer, const string&);

bool operator<=(const string&, const string&);
bool operator<=(const string&, string::const_pointer);
bool operator<=(string::const_pointer, const string&);

bool operator>=(const string&, const string&);
bool operator>=(const string&, string::const_pointer);
bool operator>=(string::const_pointer, const string&);

void swap(string&, string&);

std::istream& operator>>(std::istream&, string&);
std::wistream& operator>>(std::wistream&, string&);
std::ostream& operator<<(std::ostream&, const string&);
std::wostream& operator<<(std::wostream&, const string&);

std::istream& getline(std::istream&, string&, char delim = '\n');
std::wistream& getlien(std::wistream&, string&, wchar_t delim = L'\n');
*/
}

//#include "detail/string_impl.hpp"

#endif
