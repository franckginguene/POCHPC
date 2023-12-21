#pragma once
#include <optional>
#include <vector>
#include <string>
#include <sstream>

#include <backward.hpp>

//! helper class for OptTraced
struct voidOpt{
	std::vector<std::string> msgs;
};

//! std::optional overload that as msg vector and some stack tracing ability
template<class T=voidOpt>
struct OptTraced: public std::optional<T>{
	OptTraced(T val):std::optional<T>(val){}
	OptTraced(T&& val):std::optional<T>(val){}
	OptTraced(std::nullopt_t _):std::optional<T>(std::nullopt){}
	OptTraced(voidOpt&& other):std::optional<T>(std::nullopt),msgs(other.msgs){}
	OptTraced(std::optional<T>& other):std::optional<T>(other){}
	OptTraced(OptTraced<T>& other):std::optional<T>(other),msgs(other.msgs){}

	void print(){
		for(auto& msg : msgs){
			std::cout << msg << std::endl;
		}
	}

	std::vector<std::string> msgs;
};
namespace OptT{
inline voidOpt err(std::string msg){
	voidOpt ret;
	ret.msgs.push_back(msg);
	return ret;
}

inline voidOpt trace(){
	voidOpt ret;

	std::stringstream ss;{
		backward::StackTrace st;
		st.load_here(32);
		backward::Printer p;
		p.print(st, ss);
	}
	for (std::string line; std::getline(ss, line); ){
		if(line.rfind("#",0)!=std::string::npos || line.rfind("      >",0)!=std::string::npos ){
			ret.msgs.push_back(line);
		}
	}
	//removing this function from callstack
	ret.msgs.pop_back();
	ret.msgs.pop_back();
	return ret;
}

inline voidOpt tracedErr(std::string msg){
	auto ret=trace();
	ret.msgs.push_back(msg);
	return ret;
}
}


