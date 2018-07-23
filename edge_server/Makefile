#all:main

# main: edge_server.c helpfnc.o
#     gcc -Wall -g -o main helpfnc.o edge_server.c -lssl -lcrypto -levent_openssl -levent -pthread -lz

# helpfnc: helpfnc.h helpfnc.c
#     gcc -Wall -g helpfnc.c
#
#
#
TARGET=main
all:$(TARGET)


# CC=gcc
SRCS:= $(wildcard *.c)
OBJS:= $(SRCS:.c=.o) #subustitue refereces
LIBS:= -lssl -lcrypto -levent_openssl -levent -pthread -lz
CFLAGS:=  -Wall -g -Os -I./libevent/build/include -I./libressl/build/include # -ffunction-sections -fdata-sections
# CFLAGS:= -g -Wall -Os -I/home/moslab/Desktop/unikernel/rumprun-packages/libevent/build/include -I/home/moslab/Desktop/unikernel/rumprun-packages/libressl/build/include # -ffunction-sections -fdata-sections
LDFLAGS:= -L/home/moslab/Desktop/unikernel/rumprun-packages/libevent/build/.libs -L/home/moslab/Desktop/unikernel/rumprun-packages/libressl/build/ssl/.libs -L/home/moslab/Desktop/unikernel/rumprun-packages/libressl/build/crypto/.libs
# LDFLAGS:= -L./libevent/build/.libs -L./libressl/build/ssl/.libs -L./libressl/build/crypto/.libs #-L/home/moslab/Desktop/unikernel/rumprun-packages/openssl/build/crypto/.libs

# $@:The file name of the target of the rule
# $^:The names of all the prerequisites, with spaces between them.
# $<:The name of first prerequisite

$(TARGET): $(OBJS)
	$(CC) -Os -o  $@ $^ $(LDFLAGS) $(LIBS)
%.o : %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

docker: $(OBJS)
	$(CC) -Os -o main-docker $^ $(LIBS)

client: sslclient.c
	$(CC) $(CFLAGS) -o sslclient sslclient.c $(LDFLAGS) $(LIBS)

.PHONY: install
install:docker-main
	cp main-docker ./docker/main
.PHONY: clean
clean:
	rm -rf *.o $(TARGET)
