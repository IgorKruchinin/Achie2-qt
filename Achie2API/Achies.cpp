#ifndef ACHIES
#define ACHIES
#include "Achie_core.cpp"
#include "Storage.cpp"
#include <vector>
#include <cstdio>
class Achies {
    Storage *storage_;
	std::vector<Achie_core*> achies;
    char *name;
    bool is_default = false;
public:
    Achies(const char *name, bool is_default=false) {
        this->is_default = is_default;
        this->name = new char[1024];
        strcpy(this->name, name);
        storage_ = new Storage(this->name, is_default);
		//storage_.
        //int size = storage_.size();
        storage_->get(&achies);
		//printf("%s\n", achie->get_name());
		
		
	}
    void add(long unixtime, const char *name, const char *description, int count) {
        achies.push_back(new Achie_core(achies.size(), unixtime, name, description, count));
        storage_->insert(achies[achies.size() - 1]);
	}
	Achie_core * const get_achie(int index) {
		return achies[index];
	}
	void delete_achie(int index) {
		delete achies[index];
		achies.erase(achies.cbegin() + index);
	}
    void edit(Achie_core *achie) {
        storage_->update(achie);
		delete achies[achie->get_ID()];
		achies[achie->get_ID()] = achie;
	}
	int size() {
		return achies.size();
	}
};
#endif
