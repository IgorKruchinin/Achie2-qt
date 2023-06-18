#ifndef STORAGE
#define STORAGE
#include <sqlite3.h>

#include "Storage_core.cpp"
#include "Achie_core.cpp"
#include "props.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#define FILENAME "data.db"

class Storage {
	Storage_core *strg_;
    char *name;
    bool is_default = false;
	char *request;
	static int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names) {
		std::vector<Achie_core*> *achies = static_cast<std::vector<Achie_core*>*>(p_data);
		int ID;
		long long unsigned unixtime;
		char *name;
		char *description;
		int count;
		ID = atoi(p_fields[0]);
		unixtime = atoll(p_fields[1]);
		name = p_fields[2];
		description = p_fields[3];
		count = atoi(p_fields[4]);
		//printf(" %d, %llu, %s, %s, %d\n", ID, unixtime, name, description, count);
		//printf("%s", p_fields[5]);
		achies->push_back(new Achie_core(ID, unixtime, name, description, count));
		//printf("%llu\n", ((*achies)[0])->get_unixtime());
		return 0;
	}
    static int static_select_names_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names) {
        std::vector<char*> *names = static_cast<std::vector<char*>*>(p_data);
        for (int i = 0; i < num_fields; ++i) {
            names->push_back(p_fields[i]);
        }
        return 0;
    }
    static int static_select_is_default_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names) {
        int *index = (int*)p_data;
        for (int i = 0; i < num_fields; ++i) {
            if (atoi(p_fields[i])) {
                *index = i;
                return 0;
            }
        }
        return 1;
    }
	static int size_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names) {
		int *size = (int*)p_data;
		*size = atoi(p_fields[0]);
		return 0;
	}
public:
    static Achies_info get_all_profiles() {
        char *profile_request = new char[512];
        std::vector<char*> names;
        int index = 0;
        printf("1");
        sprintf(profile_request, "SELECT NAME FROM PROFILES", select_callback, &names);
        Storage_core::static_exec(FILENAME, profile_request, static_select_names_callback, &names);
        printf("2");
        sprintf(profile_request, "SELECT IS_DEFAULT FROM PROFILES", static_select_is_default_callback, &index);
        Achies_info achinfo;
        achinfo.default_index = index;
        achinfo.names = names;
        return achinfo;
        delete[] profile_request;
    }
    Storage(char *name, bool is_default = false) {
        this->is_default = is_default;
        this->name = new char[1024];
        strcpy(this->name, name);
		request = new char[512];
        sprintf(request, "CREATE TABLE IF NOT EXISTS \'%s\'(" \
									"ID	INT	PRIMARY	KEY	NOT NULL," \
									"DATE	DATE," \
									"NAME	TEXT	NOT NULL," \
                                    "DESCRIPTION	TEXT," \
                                    "COUNT	INT );", this->name);
        //printf("%s", request);
        char *tablist_request = new char[512];
        sprintf(tablist_request, "CREATE TABLE IF NOT EXISTS \'PROFILES\'(" \
                                "ID INT PRIMARY KEY NOT NULL," \
                                "NAME   TEXT    NOT_NULL," \
                                "IS_DEFAULT BOOLEAN );");
        strg_ = new Storage_core(FILENAME, request);
        strg_->exec(tablist_request);
        int is_exists = 0;
        sprintf(tablist_request, "SELECT COUNT(*) FROM \'PROFILES\' WHERE NAME=\'%s\';", name);
        strg_->exec(tablist_request, size_callback, &is_exists);
        //printf("%s %d", tablist_request, is_exists);
        if (!is_exists) {
            int ID = 0;
            sprintf(request, "SELECT COUNT(*) FROM \'PROFILES\'");
            strg_->exec(request, size_callback, &ID);
            sprintf(tablist_request, "INSERT INTO \'PROFILES\'(ID, NAME, IS_DEFAULT)" \
                "VALUES (%d, \'%s\', %d);", ID, this->name, this->is_default);
            strg_->exec(tablist_request);
        }
        delete[] tablist_request;
	}
	void insert(Achie_core *achie) {
        sprintf(request, "INSERT INTO \'%s\'(ID, DATE, NAME, DESCRIPTION, COUNT)" \
                "VALUES (%d, %llu, \'%s\', \'%s\', %d);", this->name, achie->get_ID(), achie->get_unixtime(), achie->get_name(), achie->get_description(), achie->get_count());
		strg_->exec(request);
	}
	void update(Achie_core *achie) {
        sprintf(request, "UPDATE \'%s\'" \
				"SET DATE = %llu," \
				"SET NAME = \'%s\'," \
				"SET DESCRIPTION = \'%s\'," \
				"SET COUNT = %d" \
                "WHERE ID = %d;", this->name, achie->get_unixtime(), achie->get_name(), achie->get_description(), achie->get_count(), achie->get_ID());
		strg_->exec(request);
	}
	void get(std::vector<Achie_core*> *achies) {
        for (int i = 0; i < size(); ++i) {
            sprintf(request, "SELECT * FROM \'%s\' WHERE ID = %d;", this->name, i);
            //printf("%s\n", request);
			strg_->exec(request, select_callback, achies);
            //printf("%s\n", request);
		}
	}
	int size() {
        int size = 0;
        sprintf(request, "SELECT COUNT(*) FROM \'%s\'", this->name);
		strg_->exec(request, size_callback, &size);
		return size;
	}
	~Storage() {
		delete strg_;
	}
};
#endif
