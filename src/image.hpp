#pragma once
#include <vector>
#include "types.hpp"

class buffer : public std::vector<u8>
{
public:
	template<typename T, typename... Ts>
	void fill(T t, Ts... ts) { fill(t); fill(ts...); }
	template<typename T>
	void fill(T t) { insert(end(), (u8*)&t, (u8*)&t + sizeof(T)); }	
	void fill(buffer& buf) { insert(end(), buf.begin(), buf.end()); }
};

// executable image for vm_t
class image
{
public:
	//void save_to_file();
	//static void load_from_file();
	
	// once these two are called, fill_*() should not be called,
	// or the two pointers will be invalidated.
	u8* get_text() { return text.data(); }
	u8* get_data() { return data.data(); }
	
	template<typename... Ts>
	void fill_text(Ts... ts) { text.fill(ts...); }
	template<typename... Ts>
	void fill_data(Ts... ts) { data.fill(ts...); }

public:
	buffer text;
	buffer data;
};
