#ifndef STORAGE_CORE
#define STORAGE_CORE
#include <sqlite3.h>
#include <cstdio>

class Storage_core {
	sqlite3 *db;
	int rc;
	char *errMSG = 0;
public:
    static void static_exec(char const *filename_tmp, char const *sql_request, int (*callback)(void*,int,char**,char**), void *callback_arg) {
        sqlite3 *db_tmp;
        char *errMSG_tmp = 0;
        int rc_tmp;
        rc_tmp = sqlite3_open(filename_tmp, &db_tmp);
        if (!rc_tmp) {
            rc_tmp = sqlite3_exec(db_tmp, sql_request, callback, callback_arg, &errMSG_tmp);
            if (rc_tmp != SQLITE_OK) {
                // Error (text in errMSG)
                printf("%s\n", errMSG_tmp);
                sqlite3_free(errMSG_tmp);
            }
        sqlite3_close(db_tmp);
        }
    }
	void exec(char const *sql_request, int (*callback)(void*,int,char**,char**), void *callback_arg) {
		rc = sqlite3_exec(db, sql_request, callback, callback_arg, &errMSG);
		if (rc != SQLITE_OK) {
			// Error (text in errMSG)
			printf("%s\n", errMSG);
			sqlite3_free(errMSG);
		}
	}
	void exec(char const *sql_request) {
		exec(sql_request, 0, 0);
	}
	Storage_core(char const *filename, char const *create_sql_table_request /* Sql request realise in adapter */) {
		rc = sqlite3_open(filename, &db);
		if (rc) {
			// Error in opening database
		}
		this->exec(create_sql_table_request);
	}
	
	~Storage_core() {
		sqlite3_close(db);
	}
};
#endif		
		
