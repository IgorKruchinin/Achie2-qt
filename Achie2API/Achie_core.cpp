#ifndef ACHIE_CORE
#define ACHIE_CORE

#define DEBUG
#include <cstring>
#ifdef DEBUG
#include <cstdio>
#endif
class Achie_core {
	int ID;
	long long unsigned unixtime;
	char *name;
	char *description;
	int count = 0;
public:
	Achie_core(int ID, long long unsigned unixtime, char const *name, char const *description, int count) {
			this->ID = ID;
			this->unixtime = unixtime;
			this->name = new char[1024];
			this->description = new char[4096];
			strcpy(this->name, name);
			strcpy(this->description, description);
			this->count = count;
	}
	void set_unixtime(long long unsigned  unixtime) {
		this->unixtime = unixtime;
	}
	void set_name(char const *name) {
		strcpy(this->name, name);
	}
	void set_description(char const *description) {
		strcpy(this->description, description);
	}
	void set_count(int count) {
		this->count = count;
	}
	void set(int ID, long long unsigned unixtime, char const *name, char const *description, int count) {
			this->ID = ID;
			this->unixtime = unixtime;
			this->name = new char[sizeof(name)];
			this->description = new char[sizeof(description)];
			strcpy(this->name, name);
			strcpy(this->description, description);
			this->count = count;
			#ifdef DEBUG
			//printf("%d, %llu, %s, %s, %d\n", this->ID, this->unixtime, this->name, this->description, this->count);
			#endif
	}
	int get_ID() {
		return ID;
	}
	long long unsigned get_unixtime() {
		return unixtime;
	}
	char const * get_name() {
		return name;
	}
	char const * get_description() {
		return description;
	}
	int get_count() {
		return count;
	}
};
#endif
