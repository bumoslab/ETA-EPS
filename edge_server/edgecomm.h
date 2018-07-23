/*
 * =====================================================================================
 *
 *       Filename:  edgecomm.h
 *
 *    Description:  :
 *
 *        Version:  1.0
 *        Created:  04/26/2017 02:47:27 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */


#ifndef __EDGECOMM__
#define __EDGECOMM__
#include "khash.h"
#include "pthread.h"
#include "assert.h"
KHASH_MAP_INIT_STR(header, char*)
KHASH_MAP_INIT_STR(header_list, char*)

typedef struct hash_list{
    pthread_mutex_t lock;
    khash_t(header_list) * list;
}hash_list;

/* typedef struct respone_hash_table{
 *     const char* response_code;
 *     khash_t(header) * h;
 * }response_hash_t;
 *
 * typedef struct request_hash_table {
 *     const char* request;
 *     khash_t(header) * h;
 * }request_hash_t; */

typedef struct hash_table_entry{
    pthread_mutex_t hte_lock;

    const char* request;
    khash_t(header) * rq_ht;

    const char* response_code;
    khash_t(header) * rp_ht;
    /* request_hash_t * rq_ht;
     * response_hash_t * rp_ht; */
}ht_entry;

void hash_list_init(hash_list ** hlist);

char* mystrndup(char* str,int n);
char** mystrsep(char* string_start, int str_end, char* delimiter,size_t split_num, size_t* res_size);

/* void store_headers(const char* request, khash_t(header) * hash_table); */
void free_header_hastable(khash_t(header)* h);
void print_khash(khash_t(header)* h);
char* process_request(char* data,size_t length,ht_entry** hte);
char* process_response(char* data, size_t length, ht_entry* hte,int *o_size);
char* reconstruct_googledoc_request(char* data, size_t length,ht_entry** entry,int * o_size);
#endif /* ifndef __EDGECOMM__ */
