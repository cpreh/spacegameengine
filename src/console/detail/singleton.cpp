/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/console/detail/singleton.hpp>
#include <sge/console/exception.hpp>
#include <sge/console/var_base.hpp>
#include <sge/log/headers.hpp>
#include <sge/make_auto_ptr.hpp>
#include <sge/auto_ptr.hpp>
#include <sge/string.hpp>
#include <sge/text.hpp>

#include <boost/bind.hpp>
#include <boost/spirit/core/scanner/scanner.hpp>
#include <boost/spirit/core/non_terminal/rule.hpp>
#include <boost/spirit/core/composite/epsilon.hpp>
#include <boost/spirit/core/composite/actions.hpp>
#include <boost/spirit/actor/push_back_actor.hpp>
#include <boost/spirit/actor/assign_actor.hpp>
#include <boost/spirit/utility/confix.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/filesystem/fstream.hpp>
#include <locale>
#include <algorithm>
#include <ostream>
#include <utility>
#include <cctype>

namespace
{
// helper class to sort out empty lines
template<typename T>
struct basic_whitespace_filter : public std::unary_function<T,bool>
{
	typedef typename T::value_type char_type;
	typedef typename T::const_iterator iterator_type;
	typedef typename std::iterator_traits<iterator_type>::difference_type difference_type;

	bool operator()(const T &s) const 
	{ 
		return std::count_if(s.begin(),s.end(),
			boost::bind(&std::isspace<char_type>,_1,std::locale::classic())) != 
			difference_type(s.size()); 
	}
};
typedef basic_whitespace_filter<sge::string> sge_whitespace_filter;

template<typename T>
struct filtered_file
{
	typedef T filter_type;
	typedef typename filter_type::argument_type string_type;
	typedef typename string_type::value_type char_type;
	typedef sge::filesystem::path filename_type;
	typedef std::vector<string_type> line_vector;
	typedef typename boost::filter_iterator<filter_type,typename line_vector::const_iterator> const_iterator;
	typedef typename boost::filter_iterator<filter_type,typename line_vector::iterator> iterator;

	const filename_type fn;
	line_vector lines;

	filtered_file(const filename_type &fn) : fn(fn)
	{
		boost::filesystem::basic_ifstream<char_type> file(fn);
		while (!file.eof() && !file.fail())
		{
			string_type line;
			std::getline(file,line);
			lines.push_back(line);
		}
	}

	iterator begin() { return iterator(lines.begin(),lines.end()); }
	const_iterator begin() const { return const_iterator(lines.begin(),lines.end()); }
	iterator end() { return iterator(lines.end(),lines.end()); }
	const_iterator end() const { return const_iterator(lines.end(),lines.end()); }
};

}


sge::con::singleton::singleton()
:
	prefix(SGE_TEXT('/'))
{}
	
sge::signals::connection const
sge::con::singleton::add(
	sge::string const &name,
	sge::con::callback const &v)
{
	callback_map::iterator const it(
		funcs.find(name));
	if(it != funcs.end())
		return it->second->connect(
			v);	

	auto_ptr<
		signal
	> sig(
		make_auto_ptr<
			signal
		>());

	std::pair<callback_map::iterator, bool> const ret
		= funcs.insert(
			name,
			sig);
	if(ret.second == false)
		throw exception(
			SGE_TEXT("console function ")
			+ name
			+ SGE_TEXT(" registered twice!"));
	return ret.first->second->connect(
		v);
}

void sge::con::singleton::add(
	sge::string const &name,
	sge::con::var_base &v)
{
	if(vars.insert(
		std::make_pair(
			name,
			&v))
	.second == false)
		throw exception(
			SGE_TEXT("console variable ")
			+ name
			+ SGE_TEXT(" registered twice!"));

	// TODO: this might be pretty slow
	config_map::const_iterator i = config_vars.find(name);
	if (i != config_vars.end())
		v.set(i->second);
}

void sge::con::singleton::erase(
	sge::string const &name)
{
	if(vars.erase(name) == 0)
		throw exception(
			SGE_TEXT("console variable ")
			+ name
			+ SGE_TEXT(" not registered!"));
}

void sge::con::singleton::eval(
	sge::string const &line)
{
	// TODO: rewrite this with spirit-2!
	sge::con::arg_list args;

	sge::string command_str;
	sge::string chat_str;

	using namespace boost::spirit;

	// types
	typedef scanner<sge::string::const_iterator> scanner_type;
	typedef rule<scanner_type> rule_type;

	// constants
	const sge::string::value_type ws = SGE_TEXT(' ');
	const sge::string::value_type sd = SGE_TEXT('\'');

	// grammar
	// <sd>.*<sd> | \S*
	rule_type argument = confix_p(ch_p(sd),(*anychar_p)[push_back_a(args)],ch_p(sd)) | 
	                     (+(~ch_p(ws)))[push_back_a(args)];
	// \s+<argument><arguments> | \s+ | e
	rule_type arguments = (+ch_p(ws) >> argument >> arguments) | +ch_p(ws) | epsilon_p;
	// <prefix>\S+<arguments>
	rule_type command = ch_p(prefix) >> (+(~ch_p(ws)))[assign_a(command_str)] >> arguments;
	// <not-prefix>.*
	rule_type chat_line = (*anychar_p);
	// <chat-line> | <command>
	//rule_type r = command | chat_line[assign_a(chat_str)];
	rule_type r = command | chat_line[push_back_a(args)];

	parse(line.begin(),line.end(),r);

	if (command_str.empty())
		chat(args);
	else
	{
		args.insert(args.begin(),command_str);
		if (funcs.find(command_str) == funcs.end())
			throw exception(SGE_TEXT("couldn't find command \"")+command_str+SGE_TEXT("\""));
		funcs[command_str](args);
	}
}

void sge::con::singleton::read_config(
	sge::filesystem::path const &fn)
{
	typedef filtered_file<sge_whitespace_filter> file_type;

	file_type file(fn);

	for (file_type::const_iterator i = file.begin(); i != file.end(); ++i)
	{
		sge::string::size_type const equals = i->find(SGE_TEXT('='));
		if (equals == sge::string::npos)
			throw exception(SGE_TEXT("error parsing \"")+fn.string()+SGE_TEXT("\": no '=' found"));

		sge::string const name = i->substr(0,equals),value = i->substr(equals+1);
		if (name.empty())
			throw exception(SGE_TEXT("error parsing \"")+fn.string()+SGE_TEXT("\": empty variable name"));

		// just a warning about multiply defined variables
		if (config_vars.find(name) != config_vars.end())
			SGE_LOG_WARNING(
				log::global(),
				log::_1
					<< SGE_TEXT("console variable \"")
					<< name
					<< SGE_TEXT("\" already registered from another file"));

		config_vars[name] = value;
	}
}

sge::string const
sge::con::singleton::var(
	sge::string const &name)
{
	var_map::const_iterator const i = vars.find(name);
	if (i == vars.end())
		throw exception(SGE_TEXT("variable \"")+name+SGE_TEXT("\" not found"));
	return i->second->get();
}

void sge::con::singleton::var(
	sge::string const &name,
	sge::string const &value)
{
	sge::con::var_map::const_iterator const i = vars.find(name);
	if (i == vars.end())
		throw exception(SGE_TEXT("variable \"")+name+SGE_TEXT("\" not found"));
	return i->second->set(value);
}

void sge::con::singleton::latch(
	sge::string const &name,
	sge::string const &value)
{
	config_vars[name] = value;
}

sge::con::singleton &
sge::con::instance()
{
	static sge::con::singleton s;
	return s;
}
