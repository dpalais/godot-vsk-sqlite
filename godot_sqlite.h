#ifndef GD_MVSQLITE_H
#define GD_MVSQLITE_H

#include "core/config/engine.h"
#include "core/object/ref_counted.h"
#include "core/templates/local_vector.h"

#include "thirdparty/spmemvfs/spmemvfs.h"
#include "thirdparty/sqlite/sqlite3.h"

class SQLite;

class SQLiteQuery : public RefCounted {
	GDCLASS(SQLiteQuery, RefCounted);

	SQLite *db = nullptr;
	sqlite3_stmt *stmt = nullptr;
	String query;

protected:
	static void _bind_methods();

public:
	SQLiteQuery();
	~SQLiteQuery();

	void init(SQLite *p_db, const String &p_query);

	bool is_ready() const;

	String get_last_error_message() const;

	Variant execute(const Array &p_args = Array());

	Variant batch_execute(const Array &p_rows);

	Array get_columns();

	void finalize();

private:
	bool prepare();
};

class SQLite : public RefCounted {
	GDCLASS(SQLite, RefCounted);

	friend class SQLiteQuery;

private:
	sqlite3 *db;
	spmemvfs_db_t p_db;
	bool memory_read;

	::LocalVector<WeakRef *, uint32_t, true> queries;

	sqlite3_stmt *prepare(const char *statement);
	Array fetch_rows(const String &query, const Array &args, int result_type = RESULT_BOTH);
	sqlite3 *get_handler() const { return memory_read ? p_db.handle : db; }
	Dictionary parse_row(sqlite3_stmt *stmt, int result_type);

public:
	static bool bind_args(sqlite3_stmt *stmt, const Array &args);

protected:
	static void _bind_methods();

public:
	enum { RESULT_BOTH = 0,
		RESULT_NUM,
		RESULT_ASSOC };

	SQLite();
	~SQLite();

	bool open(const String &path);
	bool open_in_memory();
	bool open_buffered(const String &name, const PackedByteArray &buffers, int64_t size);
	void close();

	Ref<SQLiteQuery> create_query(const String &p_query);

	String get_last_error_message() const;
};
#endif
