#include <map>
#include <functional>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include <boost/function.hpp>
#include <boost/spirit.hpp>
#include <boost/bind.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include "../../string.hpp"
#include "../console.hpp"

namespace cs = sge::con;

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
	typedef std::string filename_type;
	typedef std::vector<string_type> line_vector;
	typedef typename boost::filter_iterator<filter_type,typename line_vector::const_iterator> const_iterator;
	typedef typename boost::filter_iterator<filter_type,typename line_vector::iterator> iterator;

	const filename_type fn;
	line_vector lines;

	filtered_file(const filename_type &fn) : fn(fn)
	{
		std::basic_ifstream<char_type> file(fn.c_str());
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

struct singleton
{
	typedef std::map<sge::string,sge::string> config_map;

	cs::var_map vars;
	cs::callback_map funcs;
	config_map config_vars;
	cs::callback chat;
	sge::string::value_type prefix;

	singleton() : prefix(L'/') {}

	void add(const sge::string &,cs::var_base &);
	void add(const sge::string &,const cs::callback &);
	void eval(const sge::string &);
	void read_config(const std::string &);
	sge::string get_var(const sge::string &);
	void set_var(const sge::string &,const sge::string &);
	void latch(const sge::string &,const sge::string &);
};

singleton &instance()
{
	static singleton s;
	return s;
}

sge::string singleton::get_var(const sge::string &name)
{
	cs::var_map::const_iterator i = vars.find(name);
	if (i == vars.end())
		throw cs::exception(L"variable \""+name+L"\" not found");
	return i->second->get();
}

void singleton::latch(const sge::string &name,const sge::string &value)
{
	config_vars[name] = value;
}

void singleton::set_var(const sge::string &name,const sge::string &value)
{
	cs::var_map::const_iterator i = vars.find(name);
	if (i == vars.end())
		throw cs::exception(L"variable \""+name+L"\" not found");
	return i->second->set(value);
}

void singleton::read_config(const std::string &fn)
{
	typedef filtered_file<sge_whitespace_filter> file_type;

	file_type file(fn);

	for (file_type::const_iterator i = file.begin(); i != file.end(); ++i)
	{
		const sge::string::size_type equals = i->find(L'=');
		if (equals == sge::string::npos)
			throw cs::exception(L"error parsing \""+sge::string(fn.begin(),fn.end())+L"\": no '=' found");

		const sge::string name = i->substr(0,equals),value = i->substr(equals+1);
		if (name.empty())
			throw cs::exception(L"error parsing \""+sge::string(fn.begin(),fn.end())+L"\": empty variable name");

		// just a warning about multiply defined variables
		if (config_vars.find(name) != config_vars.end())
			std::wcerr << L"warning, console variable \"" << name << L"\" already registered from another file\n";

		config_vars[name] = value;
	}
}

void singleton::eval(const sge::string &line)
{
	cs::arg_list args;

	sge::string command_str;
	sge::string chat_str;

	using namespace boost::spirit;

	// types
	typedef scanner<sge::string::const_iterator> scanner_type;
	typedef rule<scanner_type> rule_type;

	// constants
	const sge::string::value_type ws = L' ';
	const sge::string::value_type sd = L'\'';

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
	{
		if (chat)
			chat(args);
	}
	else
	{
		args.insert(args.begin(),command_str);
		if (funcs.find(command_str) == funcs.end())
			throw cs::exception(L"couldn't find command \""+command_str+L"\"");
		funcs[command_str](args);
	}
}

void singleton::add(const sge::string &name,const cs::callback &v)
{
	if (funcs.find(name) != funcs.end())
		throw cs::exception(L"console function "+name+L" registered twice!");

	funcs[name] = v;
}

void singleton::add(const sge::string &name,cs::var_base &v)
{
	if (vars.find(name) != vars.end())
		throw cs::exception(L"console variable "+name+L" registered twice!");

	vars[name] = &v;

	// TODO: this might be pretty slow
	config_map::const_iterator i = config_vars.find(name);
	if (i != config_vars.end())
		v.set(i->second);
}

}

void cs::eval(const string &s)
{
	instance().eval(s);
}


void cs::chat_callback(const callback &c)
{
	instance().chat = c;
}

void cs::add(const string &name,const callback &c)
{
	instance().add(name,c);
}

void cs::prefix(const string::value_type &c)
{
	instance().prefix = c;
}

sge::string::value_type cs::prefix()
{
	return instance().prefix;
}

void cs::read_config(const std::string &s)
{
	instance().read_config(s);
}

void cs::var_base::late_construct()
{
	instance().add(name_,*this);
}

const cs::var_map &cs::vars()
{
	return instance().vars;
}

const cs::callback_map &cs::funcs()
{
	return instance().funcs;
}

sge::string cs::get_var(const sge::string &name)
{
	return instance().get_var(name);
}

void cs::set_var(const sge::string &name,const sge::string &value)
{
	instance().set_var(name,value);
}

void cs::latch(const sge::string &name,const sge::string &value)
{
	instance().latch(name,value);
}

cs::var_base::var_base(const string &name_)
	: name_(name_) {}
