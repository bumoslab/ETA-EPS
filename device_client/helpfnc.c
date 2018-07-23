/*
 * =====================================================================================
 *
 *       Filename:  helpfnc.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/25/2016 05:10:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#include "helpfnc.h"
#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
#include <string.h>
#include <assert.h>

int stringtoint2(char* start, size_t size);

char* search_character(char* data,size_t len)

{
    size_t i = 0;
    while(i < len - 1){
        if(data[i] == '\r' && data[i+1] =='\n'){
            return data + i;
        }
        i++;
    }
    return NULL;
}

char* chunked_decode(char* data,size_t len,size_t* o_size,int* wait_data)
{
    size_t pos_index;
    int flag;

    char* pos,*prev;

    char* size_str = malloc(sizeof(char) * 200);
    size_t size = 0;
    int total_size = 0;
    memset(size_str,'\0',200);
    char* result = malloc(sizeof(char) * 20000);
    memset(result,'\0',20000);

    prev = pos = data;

    pos_index = 0;
    flag = 0;

    int receive_all = 0;
    while(pos_index < len - 1){
        if((pos = search_character(prev,len - pos_index))){
            if(flag == 0){
                flag = 1;
                memcpy(size_str,prev,pos - prev);
                size = strtoul(size_str,NULL,16);
                prev = pos + 2;
                memset(size_str,'\0',200);
                pos_index = prev - data;
                /* fprintf(stderr,"post_index %lu decode size %lu\n",pos_index,size); */
                if(size > len - pos_index - 1){
                    receive_all = 0;
                    break;
                }
            }else{
                if(size == 0){
                    flag = 0;
                    pos_index += 2;
                    prev = pos + 2;

                    //assert( prev[0]== '\r' && prev[1] == '\n');
                    receive_all = 1;
                    //set ctx->receive_all = 1
                    break;
                }else{
//                    printf("data prev[0]:%02x ",(unsigned char)prev[0]);
                    memcpy(result + total_size, prev, size);
                    total_size += size;
                    prev = pos + 2;
                    pos_index += size + 2;
                    flag = 0;
//                    printf("pos_index %d total_size %d\n",pos_index,total_size);
                }
            }
        }
    }
    *o_size = total_size;
//    *wait_data = receive_all;
    free(size_str);
    return result;
}

char*
chunked_encode2(char* data, size_t len, size_t* o_size)
{
    char *encoded_result;
    encoded_result = malloc(4000);
    memset(encoded_result,'\0',4000);

//    char prefex_size[] = {48,48,48,48,48,48,48,49,13,10};
    char data_posfix[] = {13,10};
    char end_tail[] = {48,13,10,13,10};

    size_t i = 0;
    size_t input_index = 0;
    size_t pos_index = 0;

    /* for(i = 0; i < 12; ++i){
     *     memcpy(encoded_result + pos_index, prefex_size, sizeof prefex_size);
     *     pos_index += sizeof prefex_size;
     *     memcpy(encoded_result + pos_index, data + input_index,1);
     *     input_index += 1;
     *     pos_index += 1;
     *     memcpy(encoded_result + pos_index, data_posfix, 2);
     *     pos_index += 2;
     * } */

    unsigned int rest_data_size = len;
    char hex[5];
    memset(hex,'\0',5);
    sprintf(&hex[0],"%04x",rest_data_size);

    memcpy(encoded_result + pos_index, hex,4);
    pos_index += 4;
    memcpy(encoded_result + pos_index, data_posfix, 2);
    pos_index += 2;

    memcpy(encoded_result + pos_index, data + input_index, rest_data_size);
    pos_index += rest_data_size;
    input_index += rest_data_size;
    assert(input_index == len );
    memcpy(encoded_result + pos_index, data_posfix, sizeof data_posfix);
    pos_index += sizeof data_posfix;
    memcpy(encoded_result + pos_index, end_tail, sizeof end_tail);
    pos_index += sizeof end_tail;
    *o_size = pos_index ;
    return encoded_result;
}


char*
chunked_encode(char* data, size_t len, size_t* o_size)
{
    char *encoded_result;
    encoded_result = malloc(4000);
    memset(encoded_result,'\0',4000);

    char prefex_size[] = {48,48,48,48,48,48,48,49,13,10};
    char data_posfix[] = {13,10};
    char end_tail[] = {48,13,10,13,10};

    size_t i = 0;
    size_t input_index = 0;
    size_t pos_index = 0;

    for(i = 0; i < 12; ++i){
        memcpy(encoded_result + pos_index, prefex_size, sizeof prefex_size);
        pos_index += sizeof prefex_size;
        memcpy(encoded_result + pos_index, data + input_index,1);
        input_index += 1;
        pos_index += 1;
        memcpy(encoded_result + pos_index, data_posfix, 2);
        pos_index += 2;
    }

    unsigned int rest_data_size = len - input_index;
    char hex[5];
    memset(hex,'\0',5);
    sprintf(&hex[0],"%04x",rest_data_size);

    memcpy(encoded_result + pos_index, hex,4);
    pos_index += 4;
    memcpy(encoded_result + pos_index, data_posfix,2);
    pos_index += 2;

    memcpy(encoded_result + pos_index, data + input_index, rest_data_size);
    pos_index += rest_data_size;
    input_index += rest_data_size;
    assert(input_index == len );
    memcpy(encoded_result + pos_index, data_posfix, sizeof data_posfix);
    pos_index += sizeof data_posfix;
    memcpy(encoded_result + pos_index, end_tail, sizeof end_tail);
    pos_index += sizeof end_tail;
    *o_size = pos_index ;
    return encoded_result;
}


char*
gzip_compress(void* input_data, size_t i_size, size_t* o_size)
{
    char *b = malloc(100000);
    memset(b,'\0',100000);

    z_stream defstream;
    defstream.zalloc = Z_NULL;
    defstream.zfree = Z_NULL;
    defstream.opaque = Z_NULL;

    defstream.avail_in = (uInt)i_size;
    defstream.next_in = (Bytef* )input_data;
    defstream.avail_out = (uInt)190000;
    defstream.next_out = (Bytef *)b;
    if(deflateInit2(&defstream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 15 | 16, 8, Z_DEFAULT_STRATEGY)){

    }

    deflate(&defstream,Z_FINISH);
    deflateEnd(&defstream);


    *o_size = defstream.total_out;

    return b;
}

char*
gzip_uncompress(void* input_data, size_t i_size, size_t* o_size)
{
    int err;
    char* c = malloc(700000);
    memset(c,'\0',700000);
    z_stream infstream;
    infstream.zalloc = Z_NULL;
    infstream.zfree = Z_NULL;
    infstream.opaque = Z_NULL;
    // setup "b" as the input and "c" as the compressed output
    infstream.avail_in = (uInt)i_size;//(uInt)((char*)defstream.next_out - compressed_data); // size of input
    infstream.next_in = (Bytef *)input_data; // input char array
    infstream.avail_out = (uInt)700000; // size of output
    infstream.next_out = (Bytef *)c; // output char array

    // the actual DE-compression work.
    if(inflateInit2(&infstream,16+MAX_WBITS) == Z_OK){
//        printf("3 Uncompressed size is: %lu\n", infstream.total_out);
    }

    err = inflate(&infstream, Z_NO_FLUSH);
    if(err != Z_STREAM_END){
///        printf("4 Uncompressed size is: %d\n", err);
    }
    inflateEnd(&infstream);

    *o_size = infstream.total_out;
    return c;
}

char *
compress_and_chunkedEncoding(char* input_data, size_t i_size, size_t * o_size)
{
    char *compressed;
    char *result;
    size_t compressed_size;
    compressed = gzip_compress(input_data,i_size,&compressed_size);
    // change to another type of encoding method
    result = chunked_encode2(compressed,compressed_size,o_size);
    if(compressed != NULL)
        free(compressed);
    return result;
}

char*
decompress_and_chunkedDecoding(char* input_data,size_t i_size,size_t * o_size,int* wait_data)
{
    char *decode;
    char *result;
    size_t decode_size;

    decode = chunked_decode(input_data,i_size,&decode_size,wait_data);
    /* fprintf(stderr,"decode finished\n"); */
    /** if (*wait_data == 0) */
    result = gzip_uncompress(decode,decode_size,o_size);
    if(decode != NULL)
        free(decode);
    return result;

}


char*
get_method(const char* s)
{
    char * method;
    method = malloc(8);
    memset(method,'\0',8);
    size_t i = 0;
    while(s[i] != ' '){
        method[i] = s[i];

        ++i;
    }
//    printf("%zu\n",i);
    return method;
#if 0
    if(strstr(s,"GET")){
        memcpy(method,"GET",3);
    }else if(strstr(s,"PUT")){
        memcpy(method,"GET",3);
    }
#endif
}

int
get_id_type(const char* s,char **id, char **type)
{
    char *p;
    if((p = strstr(s,"42a638c59aa1eaa8."))){
        p += strlen("42a638c59aa1eaa8.");

        size_t i = 0;
        while(p[i] != '/' && p[i] != '\0'){
            ++i;
        }

        *id = malloc(i + 1);
        memset(*id, '\0', i + 1);
        memcpy(*id, p, i);

        p = p + i + 1;

        i = 0;
        while(p[i] != '?' && p[i] != ' ') i++;

        *type = malloc(i + 1);
        memset(*type, '\0', i + 1);
        memcpy(*type, p, i);

        return 0;
    }
    return -1;
}

char*
get_query(const char* s)
{
    size_t i = 0;
    size_t j = 0;
    size_t size;
    char* query;

    while(s[i] != '?' && s[i] != '\0')
        ++i;

    j = i;
    while(s[i] != ' ' && s[i] != '\0')
        ++i;

    if(i == j)  return NULL;

    size = i - j - 1;

    query = malloc(size + 1);
    memset(query,'\0',size + 1);
    memcpy(query,s + j + 1, size);

    return query;
}


int parse_request(char * request, char** method, char** id, char** query, char** type)
{
    *method = get_method(request);
    *query = get_query(request);

    int rv = get_id_type(request, id, type);
    //fprintf(stderr, "method %s, type %s\n",*method,*type);
    if(strcmp(*method, "GET") == 0 && strcmp(*type,"files") == 0)
        return 0;
    else if(strcmp(*method, "GET") == 0 && strcmp(*type,"content") == 0)
        return 1;
    return -1;
}

int multi_free(int num, ...)
{
    va_list args;
    int i;
    va_start(args, num);
    for(i = 0; i < num; i++){
        int *tmp = va_arg(args,void*);
        free(tmp);
    }
    va_end(args);
    return 0;
}
int max(size_t a, size_t b)
{
    return a >= b ? a: b;
}

int min(size_t a, size_t b)
{
    return a >= b ? b: a;
}

#define MYREQUEST 1
#define MYRESPONSE 2
int check_method(const char* data, size_t length,int *record)
{
    char method[9];
    memset(method,'\0',9);
    /* fprintf(stderr,"check_method\n"); */
    if(strncmp(data,"GET",3) == 0 || strncmp(data,"POST",4) == 0 || strncmp(data,"PUT",3) == 0)
    {
        return MYREQUEST;
    }else if(length >= 8 && strncmp(data, "HTTP/1.1",8) == 0){
        return MYRESPONSE;
    }else{
        return 0;
    }
    /* if(strncmp(data,"00000001",strlen("00000001")) ==0){
     *     fprintf(stderr,"do not need to record1\n");
     *     return -1;
     * }
     * if( sscanf(data,"%[^ ] %*[^ ] %*[^ ]",method) == 1){
     *     //request
     *     fprintf(stderr,"Method %s\n", method);
     *     if(strcmp(method,"POST") == 0){
     *         fprintf(stderr,"Request\n");
     *         *record = 1;
     *         return MYREQUEST;
     *     }else if(strcmp(method,"GET") == 0 &&strcmp(method,"PUT") == 0){
     *         fprintf(stderr,"do not need to record\n");
     *         *record = 0;
     *         return -1;
     *     }else if(strcmp(method,"HTTP/1.1") == 0){
     *         fprintf(stderr,"Response\n");
     *         return MYRESPONSE;
     *     }
     * }else if(sizeof("HTTP/1.1") >= length && strncmp(data,"HTTP/1.1",sizeof("HTTP/1.1")) == 0){
     *     fprintf(stderr,"Response\n");
     *     return MYRESPONSE;
     * }
     * return 0; */
}

#define ERROR 0
#define HEADER 0x0001
#define BODY  0x0002
#define COMPRESSED 0x0004
#define CHUNKED 0x0008
#define REQUEST 0x0010
#define RESPONSE 0x0020
#define REUQEST_HEADER REQUEST | HEADER
#define REQUEST_BODY   REQUEST | BODY
#define RESPONSE_HEADER RESPONSE | HEADER
#define RESPONSE_BODY RESPONSE | BODY
//#define GZIP_MAGIC "\037\213\010\000\000\000"
#define GZIP_MAGIC "\037\213"
int check_body_encoding(const char* data, size_t length)
{
    const char* p = NULL;
    int ret = 0;
    if((p = strstr(data,GZIP_MAGIC))){
        return p == data ? COMPRESSED : COMPRESSED | CHUNKED;
    }
    return 0;
}

void store_data( char* data,size_t total_size,size_t length,FILE* f,int mod,double start_time, double end_time)
{
    if(f == NULL){
        fprintf(stderr,"FILE is not opened, can not save data\n");
    }
    switch (mod){
        case REUQEST_HEADER:
            fprintf(f,"\n---------- delimited request header %zu %zu start_time %f end_time %f ----------\n", total_size,length,start_time,end_time);
            break;
        case  RESPONSE_HEADER:
            fprintf(f,"\n---------- delimited reponse header %zu %zu start_time %f end_time %f  ----------\n",total_size,length,start_time,end_time);
            break;
        case REQUEST_BODY:
            fprintf(f,"\n---------- delimited request body %zu start_time %f end_time %f ---------- \n",length,start_time, end_time);
            break;
        case RESPONSE_BODY:
            fprintf(f,"\n---------- delimited reponse body %zu start_time %f end_time %f ----------\n",length,start_time,end_time);
            break;
        default:
            fprintf(f,"\n---------- delimited  body %zu start_time %f end_time %f ----------\n",length,start_time,end_time);
            break;

    }
    if((mod & BODY) && (mod & REQUEST)) {
        // do not need to record payload right now
        //check whether body is compressed or not

        int ret = check_body_encoding(data, length);
        fprintf(stderr,"check_body_encoding %d\n",ret);
        if(ret & (COMPRESSED | CHUNKED)){
           //should be this one for google docs
            fprintf(stderr,"check_body_encoding compressed and encoding\n");
           size_t o_size;
           int wait_data = 0;
           /* char * decode_data = decompress_and_chunkedDecoding(data,length,&o_size,&wait_data);
            * fprintf(f,"\n---------- delimited decode data %lu ----------\n",o_size);
            * fwrite(decode_data,o_size,1,f);
            * fprintf(f,"\n");
            * free(decode_data); */
            /* fprintf(f,"---------- delimited body %lu ----------\n",length); */
            size_t writted_size = fwrite(data, length, 1, f);
           return;
        }else if(ret & COMPRESSED){
            size_t o_size;
            /* char* uncompressed = gzip_uncompress(data, length, &o_size);
             * fprintf(f,"---------- delimited compressed data %lu ----------\n",o_size);
             * fwrite(uncompressed,o_size,1,f);
             * free(uncompressed); */
            /* fprintf(f,"---------- delimited body %lu ----------\n",length); */
            size_t writted_size = fwrite(data, length, 1, f);
        }else{
            /* fprintf(f,"---------- delimited body %lu ----------\n",length); */
            size_t writted_size = fwrite(data, length, 1, f);
        }
    }else{
//        fprintf(stderr,
        size_t writted_size = fwrite(data, length, 1, f);
        fwrite("\n",1,1,f);
        fprintf(stderr,"writted_size %lu, to write %lu \n",writted_size, length);
    }
    fflush(f);
}

int check_body_empty( char *data,size_t length)
{
    const char* END = "\r\n\r\n";
    char* end = strstr(data, END);
    return end - data + 4 == length;
}

void record_data( char* data, size_t length,FILE* f,int mod,double start_time,double end_time)
{
    int ret = 1;
    if(!(mod & BODY)){
        ret = check_body_empty(data,length);
    }
    //store data,
    if(ret != 1){
        /* fprintf(stderr,"length %lu\n",length); */
        const char* END = "\r\n\r\n";
        char* end = strstr(data,END);
        assert(end != NULL);
        end += strlen(END);
        size_t size_to_write = end - data;

        store_data(data,length, size_to_write,f, mod | HEADER,start_time,end_time);
        if(length - size_to_write > 1){
            store_data(end,length,length - size_to_write,f,mod |BODY,start_time,end_time);
        }
    }else if(!(mod & BODY)){// not body
        store_data(data,length,length,f,mod | HEADER,start_time,end_time);
        char* p = NULL;
        int body_size = length;
        if((p = strstr(data,"Content-Length: "))){
            char* end = strstr(p,"\r\n");
            p += strlen("Content-Length: ");
            body_size = stringtoint2(p, end - p);
            store_data(data,length,body_size,f,mod|BODY,start_time,end_time);
        }

    }else {//body
        store_data(data,length,length,f,mod|BODY,start_time,end_time);
    }
}

void record_response( char* data, size_t length,FILE* f)
{

}

int record( char* data, size_t length,FILE* f,double start_time, double end_time)
{
    fprintf(stderr,"start recording data...\n");
    int flag = 0;
    int ret = check_method(data,length,&flag);
    /* fprintf(stderr,"check method return value %d\n",ret); */
    if(ret == MYREQUEST){
       record_data(data,length,f, REQUEST,start_time,end_time);
    }else if(ret == MYRESPONSE){
       record_data(data,length,f,RESPONSE,start_time,end_time);
    }else{
       record_data(data,length,f,BODY,start_time,end_time);
    }
    fprintf(stderr,"Finish!\n");
    return 1;
}
int record2( char* data, size_t length,FILE* f,int mod,double start_time, double end_time)
{
    fprintf(stderr,"start recording data...\n");
    /* int flag = 0;
     * int ret = check_method(data,length,&flag);
     * fprintf(stderr,"check method return value %d\n",ret); */
    record_data(data,length,f, mod,start_time,end_time);
    fprintf(stderr,"Finish!\n");
    return 1;
}


static const long hextable[] = {
	[0 ... 255] = -1,
	['0'] = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	['A'] = 10, 11, 12, 13, 14, 15,
	['a'] = 10, 11, 12, 13, 14, 15
};


//positive hexidecimal
int stringtoint(char* start, size_t size){
    size_t result = 0;
    size_t i = 0;
    while( i < size ){
        result = (result << 4) | hextable[start[i++]];
    }

    fprintf(stderr, "stringtoint result %lu\n", result);
    return result;
}
int stringtoint2(char* start, size_t size){
    size_t result = 0;
    size_t i = 0;
    while( i < size ){
        result = 10 * result + (start[i++] - '0');
    }

    fprintf(stderr, "stringtoint result2 %lu\n", result);
    return result;
}
int get_size(char* start, int *number_size){
    size_t i = 0;
    while(start[i] !='\r'){
        i++;
    }
    assert(start[i] == '\r');
    *number_size = i;
    fprintf(stderr, "get_size i %lu\n",i);
    return  stringtoint(start,i);
}


int process_chunkedResponse(char* data, size_t length,int state,int* more_data) // length not include NULL Terminated, more_data include \r\n
{
    if(length == 0){
        return NEXTCHUNK;// wait for more data
    }

	//if more_data larger than length?
	if(length < *more_data){
		*more_data = *more_data - length;
		return MOREDATA;
	}

    /* skip more_data part */
    char* tmp = *more_data != 0 ? data + *more_data : data;
    int rest_length = length - *more_data;

    int num_size = 0;
    int data_size = 0;

    do{
        rest_length -= data_size;
        tmp += data_size;
        data_size = get_size(tmp, &num_size) + 2;// 2 for \r\n
        /* fprintf(stderr, "data_size %d\n", data_size); */
        rest_length -= (num_size + 2);// assume \r\n in the same packet
        tmp += num_size + 2;
    }while(rest_length - data_size > 0);


    if(data_size == 2){
        return FINISHED;
    }

    if(rest_length - data_size == 0){
        return NEXTCHUNK;
    }

    if(rest_length - data_size < 0){
        *more_data = data_size - rest_length;
        return MOREDATA;
    }
}
