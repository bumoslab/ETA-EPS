/*
 * =====================================================================================
 *
 *       Filename:  processChunkedProtocal.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  05/08/2017 05:13:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

int size; // not include terminated NULL
int size1; // not include terminated NULL


char* data[] ={
"HTTP/1.1 200 OK\r\n"
"Content-Type: application/json; charset=utf-8\r\n"
"X-Robots-Tag: noindex, nofollow, nosnippet\r\n"
"X-Content-Type-Options: nosniff\r\n"
"Cache-Control: no-cache, no-store, max-age=0, must-revalidate\r\n"
"Pragma: no-cache\r\n"
"Expires: Mon, 01 Jan 1990 00:00:00 GMT\r\n"
"Date: Mon, 08 May 2017 20:59:21 GMT\r\n"
"Content-Disposition: attachment; filename=\"json.txt\"; filename*=UTF-8''json.txt\r\n"
"Content-Encoding: gzip\r\n"
"X-Frame-Options: SAMEORIGIN\r\n"
"X-XSS-Protection: 1; mode=block\r\n"
"Server: GSE\r\n"
"Alt-Svc: quic=\":443\"; ma=2592000; v=\"37,36,35\"\r\n"
"Transfer-Encoding: chunked\r\n\r\n"
"4\r\n"
"Wiki\r\n"
,
"5\r\n"
"pedia\r\n"
,
"E\r\n"
" in\r\n"
"\r\n"
"chunks.\r\n"
,
"0\r\n"
"\r\n"
};



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
        result = (result << 4) | hextable[(unsigned int)(start[i++])];
    }

    fprintf(stderr, "stringtoint result %zu\n", result);
    return result;
}
int get_size(char* start, int *number_size){
    size_t i = 0;
    while(start[i] !='\r'){
        i++;
    }
    assert(start[i] == '\r');
    *number_size = i;
    fprintf(stderr, "get_size i %zu\n",i);
    return  stringtoint(start,i);
}

enum proc_state{
    NEXTCHUNK = -2,
    MOREDATA = -1,
    FINISHED = 0
};

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
        fprintf(stderr, "data_size %d\n", data_size);
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
    return 0;
}

/* int main(){
 *     if (strstr(data[0],"Transfer-Encoding: chunked")) {
 *         char* header_end = strstr(data[0],"\r\n\r\n") + 4;
 *         size_t length = strlen(data[0]) - (header_end - data[0]);
 *         int state = NEXTCHUNK;
 *         int prev_data_size = 0;
 *         int i = 0;
 *         char* tmp = header_end;
 *         while(state != FINISHED){
 *             fprintf(stderr,"state %d\n",state);
 *             state = process_chunkedResponse(tmp,length,state,&prev_data_size);
 *             i++;
 *             tmp = data[i];
 *             length = strlen(data[i]);
 *         }
 *         fprintf(stderr,"state %d\n",state);
 *     }
 * } */
