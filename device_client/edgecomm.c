/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/19/2017 02:09:53 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include "edgecomm.h"

#if 0
const char* sample =
"POST /document/u/0/d/18TXk0UI5pJdEBsT9sAdHyPHCxxe7xLCyhKFAtq70TZo/save?id=18TXk0UI5pJdEBsT9sAdHyPHCxxe7xLCyhKFAtq70TZo&sid=790421622421afd6&c=1&w=1&smv=2&token=AC4w5VgGNPzUiO-KUfPoF_Xz0QmZgsyUkg%3A1488316923016 HTTP/1.1\r\n"
"Host: docs.google.com\r\n"
"Connection: keep-alive\r\n"
"Content-Length: 517\r\n"
"X-Build: kix_2017.08-Tue_RC04\r\n"
"X-Same-Domain: 1\r\n"
"Origin: https://docs.google.com\r\n"
"X-Rel-Id: 135.46b9d38.s\r\n"
"User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.91 Safari/537.36\r\n"
"Content-Type: application/x-www-form-urlencoded;charset=UTF-8\r\n"
"X-Chrome-UMA-Enabled: 1\r\n"
"X-Chrome-Connected: id=111122620937263590269,mode=0,enable_account_consistency=true\r\n"
"Accept: */*\r\n"
" Referer: https://docs.google.com/document/d/18TXk0UI5pJdEBsT9sAdHyPHCxxe7xLCyhKFAtq70TZo/edit\r\n"
" Accept-Encoding: gzip, deflate, br\r\n"
" Accept-Language: en-US,en;q=0.8\r\n"
" Cookie: S=documents=q8a1dgODWNpH8B8KZzECpCJ0QpVDPIKF; SID=ZAQkPVIhK5xiebypIkXSb0koKhvctoCVvoicCu-jW5oFyVxjPtnx4oVUYb0U5ZEBQRb4SA.; HSID=Atd1pSV1erZ9q2RrJ; SSID=AMCYUP1U4lfAWS2Mt; APISID=9XTYwljWtzJ-rttO/AZcj5eIB8ryu4nSgy; SAPISID=KKZAp2KqE_-dIdh3/AggcGoVZZx7AalWmU; WRITELY_SID=ZAQkPUy7ZiPLlqUIyHwhQFkYbhVwb_E1JmSzUvuWWJZbN6Mcm73K2RTpu7BJJaToIXEOXQ.; S=explorer=F3MxOn0nSxzN0Q2yGngZrUUduxinHKKB; NID=98=5UaPqIcrUwY_xycmRncTenmJ_Zld0ppWipCPNnBlC3HIRslZ6UbTFMy5f4ud8PmRddAYt90ECoiweLgS_MOl_CrhItfod4PrxPNeZ90q4wOTa77aO_zt2uRC7QlwuCrv5tU7tRxiZ7M_YGNj3aflIy6XQvZdmGTq3X8SIpXZ200mrhCtMkCiRTyiPRN4HQxo0q8JiP_TFpQ40UQ_CgGPjsqT; llbcs=3; lbcs=2\r\n\r\n";

char * app_sample =
"POST /document/save?id=1nuFtr3tNp-CXMYKSSo2bMxynrQvJJf1ZBGJwuS1pkGI&sid=1ed4bd5e8745f55d&c=1&w=1&smv=2 HTTP/1.1\r\n"
"authorization: Bearer ya29.GqEBMgRym_mWAR9rSKNvQ8TJTpQ4sr-YCqr7Bi0qzXHt44SEFI3NWc7B5u8FGm-emLTDaSwKdFimiMzpjpxsM2mT9QpfCdk9W0BiD_Ao9UzoQYWDDx9l8tATZpX2x70hWas4RwKjeIEu_X7pGzFeUrzgh9a-byCQ5RENPxr8ZBa_TnHAWdW-Vt1qNc5M0Ypjg7thGrXNplW9cgZtkyS6cskIPv0\r\n"
"x-same-domain: 1\r\n"
"x-rel-id: 13a.0.b\r\n"
"x-build: 2017.13-Tue\r\n"
"content-encoding: gzip\r\n"
"User-Agent: Cakemix/1.7.132.08.35 (ja3g KTU84Q) Google.Docs/1.7.132.08.35 (OS=Android;OSVer=4.4.4;Manufacturer=samsung;Model=GT-I9500) Mozilla/5.0 (Linux; U; Android 4.4.4; en-us; GT-I9500 Build/KTU84Q) AppleWebKit/525.10+ (KHTML, like Gecko) Version/3.0.4 Mobile Safari/523.12.2\r\n"
"Content-Type: application/x-www-form-urlencoded;charset=utf-8\r\n"
"Transfer-Encoding: chunked\r\n"
"Host: docs.google.com\r\n"
"Connection: Keep-Alive\r\n"
"Accept-Encoding: gzip\r\n\r\n";

char* response =
"HTTP/1.1 200 OK \r\n"
"Content-Type: application/json; charset=utf-8 \r\n"
"X-Robots-Tag: noindex, nofollow, nosnippet \r\n"
"X-Content-Type-Options: nosniff \r\n"
"Cache-Control: no-cache, no-store, max-age=0, must-revalidate \r\n"
"Pragma: no-cache \r\n"
"Expires: Mon, 01 Jan 1990 00:00:00 GMT \r\n"
"Date: Thu, 20 Apr 2017 17:45:04 GMT \r\n"
"Content-Disposition: attachment; filename=\"json.txt\"; filename*=UTF-8''json.txt \r\n"
"Content-Encoding: gzip \r\n"
"P3P: CP=\"This is not a P3P policy! See https://support.google.com/accounts/answer/151657?hl=en for more info.\" \r\n"
"P3P: CP=\"This is not a P3P policy! See https://support.google.com/accounts/answer/151657?hl=en for more info.\" \r\n"
"X-Frame-Options: SAMEORIGIN \r\n"
"X-XSS-Protection: 1; mode=block \r\n"
"Server: GSE \r\n"
"Set-Cookie: NID=101=pKdLZ3nxBh8L_kfFGjx59tGTFe17aTAWrEiuBV3PMVs7Rh1CBQF2SjtAstjd6wmzeA6IwnHQTolQ8utySgvtqtAGkecmc7ICj1jajof4jTOQAKTE_ykD1Be2yF8kj2lO;Domain=.google.com;Path=/;Expires=Fri, 20-Oct-2017 17:45:04 GMT;HttpOnly \r\n"
"Set-Cookie: NID=101=mAnA_2gwTG7fThngIC8GzCGfty8dmy15IKycj1sQ2Spm6vEKXTtb10wj-WTR1V21x1N9RkfD7Rgew0j5LVkNCaCkKF1HyD53u2RKPn_GSq9AzC5j_xQHEi0vTnMHmhCE;Domain=.google.com;Path=/;Expires=Fri, 20-Oct-2017 17:45:04 GMT;HttpOnly \r\n"
"Alt-Svc: quic=\":443\"; ma=2592000; v=\"37,36,35\"\r\n"
"Transfer-Encoding: chunked\r\n\r\n";




/* "rev=1&bundles=%5B%7B%22commands%22%3A%5B%7B%22ty%22%3A%22is%22%2C%22ibi%22%3A1%2C%22s%22%3A%22Ty%22%7D%2C%7B%22ty%22%3A%22as%22%2C%22st%22%3A%22text%22%2C%22si%22%3A1%2C%22ei%22%3A2%2C%22sm%22%3A%7B%22ts_bd_i%22%3Atrue%2C%22ts_fs_i%22%3Atrue%2C%22ts_ff_i%22%3Atrue%2C%22ts_it_i%22%3Atrue%2C%22ts_sc_i%22%3Atrue%2C%22ts_st_i%22%3Atrue%2C%22ts_tw%22%3A400%2C%22ts_un_i%22%3Atrue%2C%22ts_va_i%22%3Atrue%2C%22ts_bgc_i%22%3Atrue%2C%22ts_fgc_i%22%3Atrue%7D%7D%5D%2C%22sid%22%3A%22790421622421afd6%22%2C%22reqId%22%3A0%7D%\r\n";
 *  */
#endif


extern hash_list *global_hlist;
void hash_list_init(hash_list ** hlist)
{
    (*hlist) = malloc(sizeof(hash_list));
    (*hlist)->list = kh_init(header_list);
    pthread_mutex_init(&(*hlist)->lock,NULL);
}

/* void request_hash_init(request_hash_t*);
 * void response_hash_init(response_hash_t*); */

ht_entry* ht_entry_init()
{

    ht_entry *hte = malloc(sizeof(ht_entry));
    hte->request = hte->response_code = NULL;
    pthread_mutex_init(&hte->hte_lock,NULL);
    hte->rq_ht = kh_init(header);
    hte->rp_ht = kh_init(header);
    return hte;
   /* hte -> rq_ht = malloc(sizeof(request_hash_t));
    * hte -> rp_ht = malloc(sizeof(response_hash_t));
    * request_hash_init(hte->rq_ht);
    * response_hash_init(hte->rp_ht); */
}


/* void request_hash_init(request_hash_t* rq_ht)
 * {
 *    rq_ht->request = NULL;
 *    rq_ht->h = kh_init(header);
 * }
 *
 * void response_hash_init(response_hash_t* rp_ht)
 * {
 *    rp_ht->response_code = NULL;
 *    rp_ht->h = kh_init(header);
 * } */


/*  n doesn't include null termiate  */
char* mystrndup(char* str,int n)
{
    char* result = malloc(n + 1);
    memset(result,'\0', n + 1);
    memcpy(result,str, n);
    return result;
}

char** mystrsep(char* string_start, int str_end, char* delimiter,size_t split_num, size_t* res_size)
{
    if(split_num < 1)
        return NULL;

    char** result = NULL;
    char* tmp = string_start;
    char* last_comma = NULL;
    size_t count = 0;
    while(count < split_num - 1 && tmp < string_start + str_end && *tmp){
        char* pos = strstr(tmp,delimiter);
        if(pos != NULL && pos < tmp  + str_end){
            count++;
            last_comma = pos + strlen(delimiter);
            tmp = pos + strlen(delimiter);
        }else{
            break;
        }

    }
    //trailing token
    if(last_comma == NULL && count == 0)
        return NULL;
    count = last_comma < string_start + str_end ? count + 1: count;

    result = malloc(sizeof (char*) * count);

    if(result){
        size_t idx = 0;
        tmp = string_start;
        while(idx < split_num - 1 && tmp < string_start + str_end && *tmp){
            char* pos = strstr(tmp,delimiter);
            if(pos != NULL && pos < string_start + str_end){
                size_t size = pos - tmp;
                /* fprintf(stderr,"size %lu\n",size); */
                result[idx] = mystrndup(tmp, size);
                tmp = pos + strlen(delimiter);
                idx++;
            }else{
                size_t size = string_start + str_end - tmp;
                result[idx] = mystrndup(tmp, size);
                break;
            }
        }
        if(tmp < string_start + str_end){
            size_t size = string_start + str_end - tmp;
            result[idx] = mystrndup(tmp, size);
        }
    }
    *res_size = count;
    return result;

}

//TODO: hash_table should ht_entry->req_ht or ht_entry->rsp_ht
void store_headers(const char* request,const char* request_end, khash_t(header) * hash_table)
{
    char* header_start = NULL;
    char* header_end = NULL;

    /* fprintf(stderr,"store_headers"); */
    /* char* dup = strdup(request); */
    //TODO: First line should be request, store into request_hash_t->request/response_hash_t,set header_start to second Line
    for(header_start = (char*)request; *header_start && header_start < request_end; ){
        header_end = strstr(header_start,"\r\n");
        /* char *result = strsep(&header_start,":"); */
        size_t res_size = 0;
        char** result = mystrsep(header_start,header_end - header_start,":",2,&res_size);
        /* fprintf(stderr,"res_size %lu\n",res_size); */
        if(res_size > 1 && result[0] != NULL && result[1] != NULL){

            /* fprintf(stderr,"result[0]%s\n result[1] %s\n",result[0],result[1]); */
            int ret = 0;
            int k = kh_put(header, hash_table, result[0],&ret);
            if(ret == 1){
                kh_value(hash_table,k) = result[1];
            }
            if(res_size == 3){
                /* free(result[2]); */

            }
        }else if(res_size == 1){
            free(result[0]);
        }
        header_start = header_end + strlen("\r\n");
        free(result);
    }
    /* fprintf(stderr,"end\n"); */
}

void free_header_hastable(khash_t(header)* h)
{
    khiter_t k;
	for (k = kh_begin(h); k != kh_end(h); ++k)
        if (kh_exist(h, k)){
            const char* key = kh_key(h,k);
            char* value = kh_value(h,k);
            fprintf(stderr,"key %s\n", kh_key(h,k));
            fprintf(stderr,"value %s\n",kh_value(h, k));
            kh_del(header,h,k);
            free(value);
            free((char*)key);
        }
	kh_destroy(header, h);
}

void print_khash(khash_t(header)* h)
{
    khiter_t k;
	for (k = kh_begin(h); k != kh_end(h); ++k)
        if (kh_exist(h, k)){
            /* const char* key = kh_key(h,k); */
            /* char* value = kh_value(h,k); */
            fprintf(stderr,"index: %d key:%s ", k, kh_key(h,k));
            fprintf(stderr,"value %s\n",kh_value(h, k));
        }
}

void construct_op_request(const char* request, const char* request_end, khash_t(header) * hash_table, char* request_result)
{
    char* header_start = NULL;
    char* header_end = NULL;

    /* fprintf(stderr,"store_headers"); */
    /* char* dup = strdup(request); */
    //TODO: First line should be request, store into request_hash_t->request/response_hash_t,set header_start to second Line
    int r_index = 0;
    for(header_start = (char*)request; *header_start && header_start < request_end; ){
        header_end = strstr(header_start,"\r\n");
        /* char *result = strsep(&header_start,":"); */
        size_t res_size = 0;
        char** result = mystrsep(header_start,header_end - header_start,":",2,&res_size);

        /* fprintf(stderr, "construct_op_request res_size %lu\n",res_size); */

        if(res_size > 1 && result[0] != NULL && result[1] != NULL){
            /* fprintf(stderr,"result[0]%s\n result[1] %s\n",result[0],result[1]); */
            /* int ret = 0; */
            /* fprintf(stderr, "construct_op_request 1\n"); */
            khint_t k = kh_get(header, hash_table, result[0]);
            if(k != kh_end(hash_table)){
                /* fprintf(stderr, "construct_op_request 2\n"); */
               if(strcmp(kh_value(hash_table,k) , result[1]) == 0){
                   //add it to request;
                    request_result[r_index] = '|';
                    r_index++;
                    int sp_ret = sprintf(request_result + r_index,"%d",k);
                    r_index += sp_ret;

               }
            }else{
                /* fprintf(stderr, "can not find header\n"); */
            }
            if(res_size == 3){
                /* free(result[2]); */

            }
        }else if(res_size == 1){
                fprintf(stderr, "can not find header2\n");
            /* free(result[0]); */
        }
        header_start = header_end + strlen("\r\n");
        size_t i;
        for(i = 0; i < res_size; ++i)
        {
            free(result[i]);
        }
        free(result);
    }
    /* fprintf(stderr,"end\n"); */
}

//length include NULL terminate
char* process_request(char* data,size_t length, ht_entry** hte,int *o_size)
{
    char* result = NULL;
    pthread_mutex_lock(&global_hlist->lock);
    if(strstr(data,"POST /document/save?id=")){
        /* fprintf(stderr,"process_request save id\n"); */
        const char* p = strstr(data,"\r\n");
        char* request = mystrndup(data, p - data);
        khint_t it = kh_get(header_list,global_hlist->list, request);
        if(it == kh_end(global_hlist->list)){
            // Not found
            /* fprintf(stderr,"process_request Not found\n"); */
            int ret = -1;
            it = kh_put(header_list,global_hlist->list,request,&ret);
            ht_entry * new_entry = NULL;
            new_entry = ht_entry_init();
            new_entry->request = request;
            char* end = strstr(p, "\r\n\r\n");
            store_headers(p,end + 2, new_entry->rq_ht);
            *hte = new_entry;
            kh_value(global_hlist->list,it) = (void*)new_entry;

            /* fprintf(stderr, "save entry->request %d %s\n", it, new_entry->request); */
            goto leave;

        }

        // construct new request;
        // TODO: current implementation, edge should not go this part,
        //       replace with new one
        //
        /* fprintf(stderr,"process_request found\n"); */
        char* end = strstr(p, "\r\n\r\n");
        size_t payload_size = length - (end + 4 - data);// include NULL terminate
        ht_entry* entry = (ht_entry*)kh_value(global_hlist->list, it);
        /* fprintf(stderr, "entry->request %s\n",entry->request); */
        /* fprintf(stderr, "request %s\n",request); */

        assert(strcmp( entry->request,request) == 0);

        char header_result[1000] = {0};
        char num_str[10] = {0};
        int p_ret = sprintf(num_str,"%d",it);
        header_result[0] = '*';
        memcpy(header_result + 1, num_str,p_ret);

        construct_op_request(p,end + 2,entry->rq_ht,header_result + p_ret + 1);
        size_t r_size = strlen(header_result) + payload_size + 4;//4 for "/r/n/r/n"
        result = malloc(r_size);
        memset(result,'\0',r_size);
        memcpy(result,header_result,strlen(header_result));
        memcpy(result + strlen(header_result), "\r\n\r\n", 4);
        memcpy(result + strlen(header_result) + 4, end + 4, payload_size);
        *o_size = r_size;
        /* *hte = NULL; */
        goto leave;

    }
leave:
    pthread_mutex_unlock(&global_hlist->lock);
    return result;
}

char* process_response(char* data, size_t length, ht_entry *hte,int* o_size)
{
    pthread_mutex_lock(&global_hlist->lock);
    char* result = NULL;
    if(strstr(data,"HTTP/1.1 200 OK")){
        /* fprintf(stderr,"process_response http ok\n"); */
        const char* p = strstr(data,"\r\n");
        char* response = mystrndup(data, p - data);


            // Not found
        if(hte->response_code == NULL){
            /* fprintf(stderr,"process_response Not found\n"); */
            int ret = -1;
            hte->response_code = response;
            char* end = strstr(p, "\r\n\r\n");
            store_headers(p,end + 2, hte->rp_ht);

            /* fprintf(stderr, "save entry->request %s\n",  hte->response_code); */
            goto leave;
        }


        // construct new request;
        // TODO: current implementation, edge should not go this part,
        //       replace with new one
        //
        /* fprintf(stderr,"process_resposne found\n"); */
        char* end = strstr(p, "\r\n\r\n");
        size_t payload_size = length - (end + 4 - data);// include NULL terminate
        ht_entry* entry = hte;
        /* fprintf(stderr, "entry->response %s\n",entry->response_code); */
        /* fprintf(stderr, "response %s\n",response); */
        {
            /* fprintf(stderr,"print entry-rp_ht\n"); */
            /* print_khash(entry->rp_ht); */
        }

        assert(strcmp( entry->response_code,response) == 0);

        char header_result[1000] = {0};
        char num_str[10] = {0};
        khint_t it = kh_get(header_list,global_hlist->list, hte->request);
        int p_ret = sprintf(num_str,"%d",it);
        header_result[0] = '*';
        memcpy(header_result + 1, num_str,p_ret);

        // TODO: the case of different headers between each response
        construct_op_request(p,end + 2,entry->rp_ht,header_result + p_ret + 1);
        size_t r_size = strlen(header_result) + payload_size + 4;//4 for "/r/n/r/n"
        result = malloc(r_size);
        memset(result,'\0',r_size);
        memcpy(result,header_result,strlen(header_result));
        memcpy(result + strlen(header_result), "\r\n\r\n", 4);
        memcpy(result + strlen(header_result) + 4, end + 4, payload_size);
        goto leave;
    }
leave:
    pthread_mutex_unlock(&global_hlist->lock);
    return result;

}


int get_iterator_from_request(char* data, size_t start,size_t end,int* forward)
{
    size_t index = 0;
    int result = 0;
    while(data[start + index] != '|' && data[start + index] != '$' && start + index < end){
        result = result * 10 + (data[start + index] - '0');
        index++;
    }
    *forward = index;
    /* fprintf(stderr, "get_iterator_from_request: %d\n", result); */
    return result;
}


char* reconstruct_googledoc_response(char* data, size_t length,ht_entry** entry,int *o_size)
{
    ht_entry* tmp = NULL;
    char* result;
    char* data_tmp = data;
    if(data_tmp[0] == '*')
    {
        char* end = strstr(data_tmp,"\r\n\r\n");
        char header_result[10000] = {0};
        size_t result_index = 0;
        size_t index = 0;
        size_t size = end - data_tmp;
        while(index < size){
            if(data_tmp[index] == '*'){
                //request
                index++;
                int forward;
                khint_t it = get_iterator_from_request(data_tmp,index,size,&forward);
                tmp = (ht_entry*)kh_value(global_hlist->list,it);
                memcpy(header_result + result_index,tmp->response_code,strlen(tmp->response_code));
                result_index += strlen(tmp->response_code);
                memcpy(header_result + result_index,"\r\n",2);
                result_index += 2;
                /* fprintf(stderr, "* resuelt %s\n", header_result); */
                *entry = tmp;
                index += forward;

                {
                    /* fprintf(stderr,"print entry-rp_ht\n"); */
                    /* print_khash(tmp->rp_ht); */
                }

            }else if (data_tmp[index] == '|') {
                /* fprintf(stderr, "process | 1 \n"); */
                index++;
                int forward;
                khint_t it = get_iterator_from_request(data_tmp,index,size,&forward);
                index += forward;
                char* header = (char*)kh_key(tmp->rp_ht,it);
                char* header_value = (char*) kh_value(tmp->rp_ht,it);
                /* fprintf(stderr, "| resuelt header %s\n", header);
                 * fprintf(stderr, "| resuelt header_value %s\n", header_value); */
                memcpy(header_result +  result_index, header, strlen(header));
                result_index += strlen(header);
                memcpy(header_result + result_index, ":",1);
                result_index += 1;
                memcpy(header_result + result_index, header_value,strlen(header_value));
                result_index += strlen(header_value);
                memcpy(header_result + result_index, "\r\n",2);
                result_index += 2;
                /* fprintf(stderr, "process | 2 \n"); */
               //header
            }else if(data_tmp[index] == '$') {
                /* fprintf(stderr, "copy original header\n"); */
                index++;
                int end = 0;
                while(data_tmp[index + end] != '|' && data_tmp[index + end] != '$' && data_tmp[index + end] != '\r'){
                    end++;
                }
                /* fprintf(stderr, "end %d\n", end); */
                memcpy(header_result + result_index, &(data_tmp[index]), end);
                index += end;
                result_index += end;
                memcpy(header_result + result_index, "\r\n",2);
                result_index += 2;
            }
        }
        /* fprintf(stderr, "recon1 %s \n",header_result); */
        memcpy(header_result + result_index, "\r\n",2);
        size_t header_size = strlen(header_result);
        size_t payload_size = length - (end - data + 4);// - 1;
        result = malloc(header_size + payload_size + 1);
        memset(result,'\0',header_size + payload_size + 1);
        memcpy(result,header_result,header_size);
        memcpy(result + header_size, end + 4, payload_size);
        *o_size = header_size + payload_size + 1;
        /* fprintf(stderr, "header_size: %lu payload_size: %lu\n",header_size,payload_size); */
        return result;
    }
    return NULL;
}
char* reconstruct_googledoc_request(char* data, size_t length,ht_entry** entry,int *o_size)
{
    ht_entry* tmp = NULL;
    char* result;
    char* data_tmp = data;
    if(data_tmp[0] == '*')
    {
        char* end = strstr(data_tmp,"\r\n\r\n");
        char header_result[10000] = {0};
        size_t result_index = 0;
        size_t index = 0;
        size_t size = end - data_tmp;
        while(index < size){
            if(data_tmp[index] == '*'){
                //request
                index++;
                int forward;
                khint_t it = get_iterator_from_request(data_tmp,index,size,&forward);
                tmp = (ht_entry*)kh_value(global_hlist->list,it);
                memcpy(header_result + result_index,tmp->request,strlen(tmp->request));
                result_index += strlen(tmp->request);
                memcpy(header_result + result_index,"\r\n",2);
                result_index += 2;
                /* fprintf(stderr, "* resuelt %s\n", header_result); */
                *entry = tmp;
                index += forward;

            }else if (data_tmp[index] == '|') {
                index++;
                int forward;
                khint_t it = get_iterator_from_request(data_tmp,index,size,&forward);
                index += forward;
                char* header = (char*)kh_key(tmp->rq_ht,it);
                char* header_value = (char*) kh_value(tmp->rq_ht,it);
                /* fprintf(stderr, "| resuelt header %s\n", header);
                 * fprintf(stderr, "| resuelt header_value %s\n", header_value); */
                memcpy(header_result +  result_index, header, strlen(header));
                result_index += strlen(header);
                memcpy(header_result + result_index, ":",1);
                result_index += 1;
                memcpy(header_result + result_index, header_value,strlen(header_value));
                result_index += strlen(header_value);
                memcpy(header_result + result_index, "\r\n",2);
                result_index += 2;
               //header
            }
        }
        /* fprintf(stderr, "recon1 %s \n",header_result); */
        memcpy(header_result + result_index, "\r\n",2);
        size_t header_size = strlen(header_result);
        size_t payload_size = length - (end - data + 4);// - 1;
        result = malloc(header_size + payload_size + 1);
        memset(result,'\0',header_size + payload_size + 1);
        memcpy(result,header_result,header_size);
        memcpy(result + header_size, end + 4, payload_size);
        *o_size = header_size + payload_size + 1;
        /* fprintf(stderr, "header_size: %lu payload_size: %lu\n",header_size,payload_size); */
        return result;
    }
    return NULL;
}
#if 0
int main()
{
    khash_t(header) * h = kh_init(header);
    /* char* sample ="Content-Length: 517\r\n""X-Build: kix_2017.08-Tue_RC04\r\n"; */
    store_headers(sample,h);
    free_header_hastable(h);
}
#endif
