
#include <vector>
#include <cstddef>

template<typename T, size_t& (*F)(T&)>
struct SelfSet{
	std::vector<T> vs;
	void insert(T v){
		size_t index = vs.size();
		vs.emplace_back(std::move(v));
		F(vs.back()) = index;
	}
	void erase(size_t i){
		size_t leli = vs.size() - 1;
		if(i < leli){
			T lel = std::move(vs[leli]);
			F(lel) = i;
			vs[i] = std::move(lel);
		}
		vs.pop_back();
	}
	void erase(T& v){
		erase(F(v));
	}
};

#ifdef SELFSET_EXAMPLE
#include <iostream>
#include <string>

struct SomeItem{
	std::string name;
	size_t containmentIndex;
	SomeItem(std::string name):name(name) {}
};

size_t& containmentIndexOfSomeItem(SomeItem& v){ return v.containmentIndex; }

int main(){
	SelfSet<SomeItem, containmentIndexOfSomeItem> comset;
	
	comset.insert(SomeItem("0"));
	comset.insert(SomeItem("One, the lamb"));
	comset.insert(SomeItem("2"));
	comset.insert(SomeItem("3"));
	comset.insert(SomeItem("4"));
	comset.insert(SomeItem("5"));
	comset.insert(SomeItem("Six, the deposer"));
	
	for(SomeItem& v : comset.vs){ std::cout<<v.name<<", at location "<<v.containmentIndex<<std::endl; }
	std::cout<<"---"<<std::endl;
		
	comset.erase(1); //this is a constant time operation
	
	for(SomeItem& v : comset.vs){ std::cout<<v.name<<", at location "<<v.containmentIndex<<std::endl; }
}
#endif