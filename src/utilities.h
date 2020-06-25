#ifndef SERIALIZR_UTILITIES_H
#define SERIALIZR_UTILITIES_H

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <Rinternals.h>
#undef error

/// #include "AnalysisSwitch.h"
/// #include "stdlibs.h"
/// #include <openssl/evp.h>
///
/// #define RID_INVALID 0 //(rid_t) - 1
///
/// // Typical human-readable representation
/// typedef uintptr_t rid_t; // hexadecimal
/// typedef intptr_t rsid_t; // hexadecimal
///
/// // typedef rsid_t promise_id_t;  // hexadecimal
/// typedef rid_t
///     call_id_t; // integer TODO this is pedantic, but shouldn't this be int?
///
/// typedef std::string fn_id_t;  // integer
/// typedef std::string fn_key_t; // pun
/// typedef int env_id_t;
/// typedef int var_id_t;
/// typedef unsigned long int arg_id_t; // integer
///
/// typedef int event_t;
///
/// typedef std::pair<call_id_t, std::string> arg_key_t;
///
/// enum class parameter_mode_t {
///     UNASSIGNED = 0,
///     MISSING,
///     DEFAULT,
///     CUSTOM,
///     NONPROMISE
/// };
///
/// typedef long long int timestamp_t;
/// extern const timestamp_t UNDEFINED_TIMESTAMP;
///

///
/// struct eval_depth_t {
///     int call_depth;
///     int promise_depth;
///     int nested_promise_depth;
/// };
///
/// extern const eval_depth_t ESCAPED_PROMISE_EVAL_DEPTH;
/// extern const eval_depth_t UNASSIGNED_PROMISE_EVAL_DEPTH;
///
/// extern const size_t PROMISE_MAPPING_BUCKET_COUNT;
///
///
///
///
///
/// int get_file_size(std::ifstream &file);
///
/// std::string readfile(std::ifstream &file);
///
/// bool file_exists(const std::string &filepath);
///
/// char *copy_string(char *destination, const char *source, size_t
/// buffer_size);
///
/// bool sexp_to_bool(SEXP value);
///
/// int sexp_to_int(SEXP value);
///
/// std::string sexp_to_string(SEXP value);
///
/// template <typename T>
/// typename std::underlying_type<T>::type to_underlying_type(const T &enum_val)
/// {
///     return static_cast<typename std::underlying_type<T>::type>(enum_val);
/// }
///
/// std::string compute_hash(const char *data);
/// const char *get_ns_name(SEXP op);
/// const char *get_name(SEXP call);
/// std::string get_definition_location_cpp(SEXP op);
/// std::string get_callsite_cpp(int);
/// int is_byte_compiled(SEXP op);
/// // char *to_string(SEXP var);
/// std::string get_expression(SEXP e);
/// std::string escape(const std::string &s);
/// const char *remove_null(const char *value);
/// std::string clock_ticks_to_string(clock_t ticks);
/// AnalysisSwitch to_analysis_switch(SEXP env);
/// std::string to_string(const char *str);
///
/// inline std::string check_string(const char *s) {
///     return s == NULL ? "<unknown>" : s;
/// }
///

namespace serializr {

extern const char UNIT_SEPARATOR;
extern const char RECORD_SEPARATOR;

struct memory_block_t {
    void* origin;
    std::size_t size;
};

#define failwith(format, ...) \
    failwith_impl(__FILE__, __LINE__, format, __VA_ARGS__)

#define failwith_impl(file, line, format, ...)     \
    do {                                           \
        fprintf(stderr,                            \
                "serializr error [%s:%d] " format, \
                file,                              \
                line,                              \
                __VA_ARGS__);                      \
        exit(EXIT_FAILURE);                        \
    } while (0)

inline void* malloc_or_die(std::size_t size) {
    void* data = std::malloc(size);
    if (data == nullptr) {
        failwith("memory allocation error: unable to allocate %lu bytes.\n",
                 size);
    }
    return data;
}

inline void* calloc_or_die(std::size_t num, std::size_t size) {
    void* data = std::calloc(num, size);
    if (data == nullptr) {
        failwith("memory allocation error: unable to allocate %lu bytes.\n",
                 size);
    }
    return data;
}

inline void* realloc_or_die(void* ptr, std::size_t size) {
    void* data = std::realloc(ptr, size);
    if (data == nullptr) {
        failwith("memory allocation error: unable to reallocate %lu bytes.\n",
                 size);
    }
    return data;
}

int parse_integer(const char* buffer, const char** end, std::size_t bytes = 4);

bool can_parse_integer(const char* buffer,
                       const char* end,
                       std::size_t bytes = 4);

double parse_real(const char* buffer, const char** end);

bool can_parse_real(const char* buffer, const char* end);

int parse_logical(const char* buffer, const char** end);

bool can_parse_logical(const char* buffer, const char* end);

SEXPTYPE parse_sexptype(const char* buffer, const char** end);

SEXP parse_character(const char* buffer,
                     const char** end,
                     char** dest,
                     std::size_t* dest_size);

bool can_parse_character(const char* buffer, const char* end);

std::string sexptype_to_string(SEXPTYPE sexptype);

int open_file(const std::string& filepath, int flags, mode_t mode = 0666);

void close_file(int fd, const std::string& filepath);

memory_block_t map_to_memory(const std::string& filepath);

void unmap_memory(void* data, std::size_t size);

} // namespace serializr

#endif /* SERIALIZR_UTILITIES_H */