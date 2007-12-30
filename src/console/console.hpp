#ifndef CONSOLE_HPP_INCLUDED
#define CONSOLE_HPP_INCLUDED

// c++
#include <iostream>
#include <exception>
#include <vector>
#include <map>
// boost
#include <boost/lexical_cast.hpp>
#include <boost/function.hpp>
// sge
#include "../string.hpp"

namespace sge
{
namespace con
{

struct exception : public std::runtime_error
{
	const sge::string wide;

	explicit exception(const sge::string &wide) 
		: std::runtime_error(std::string(wide.begin(),wide.end())),wide(wide) {}
	const sge::string &wide_what() const { return wide; }
	~exception() throw() {}
};

struct var_base
{
	string name_;

	var_base(const string &);
	void late_construct();
	string name() { return name_; }
	virtual void set(const string &) = 0;
	virtual string get() const = 0;
	virtual ~var_base() {}
};

template<typename T>
class var : public var_base
{
	public:
	typedef T value_type;

	void set(const string &s) 
	{ 
		try
		{
			t = boost::lexical_cast<T>(s); 
		} 
		catch (const boost::bad_lexical_cast &c)
		{
			throw exception(L"couldn't parse variable \""+name_+L"\"");
		}
	}

	string get() const { return boost::lexical_cast<string>(t); }

	const T &value() const { return t; }
	void value(const T &_t) { t = _t; }

	var(const string &name,const value_type &t = value_type()) 
		: var_base(name),t(t) { late_construct(); }

	protected:
	value_type t;
};

template<typename T,typename A>
struct action_var_base : public var_base
{
	public:
	typedef T value_type;
	typedef A action_type;

	void set(const string &s) 
	{ 
		try
		{
			value(boost::lexical_cast<T>(s));
			//t = a(boost::lexical_cast<T>(s),t); 
		} 
		catch (const boost::bad_lexical_cast &c)
		{
			throw exception(L"couldn't parse variable \""+name()+L"\"");
		}
	}
	string get() const { return boost::lexical_cast<string>(t); }

	const T &value() const { return t; }

	void value(const T &_t) 
	{ 
		t = _t;
		t = a(_t,t); 
	}

	action_var_base(const string &name,A _a,const value_type &_t = value_type()) 
		: var_base(name),a(_a),t(_t)
	{
		late_construct();
	}

	private:
	action_type a;
	value_type t;
};

// this constructs an action_var with boost::function as functor
// which is an extremely convenient shortcut (you don't have to specify
// action_var< T,boost::function<T (const T &,const T &)> >
template<typename T>
struct action_var
{
	typedef boost::function<T (const T &,const T &)> fn;
	typedef action_var_base<T,fn> type;

	private:
	action_var() {}
	action_var(const action_var &) {}
};

typedef std::vector<string> arg_list;
typedef boost::function<void (const arg_list &)> callback;
typedef std::map<string,var_base*> var_map;
typedef std::map<string,callback> callback_map;

void prefix(const string::value_type &);
string::value_type prefix();
void add(const string &,const callback &);
void eval(const string &);
void chat_callback(const callback &);
void read_config(const std::string &);
const var_map &vars();
const callback_map &funcs();
sge::string get_var(const sge::string &);
void set_var(const sge::string &,const sge::string &);
void latch(const sge::string &,const sge::string &);

}
}

#endif
