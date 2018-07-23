FROM ubuntu
MAINTAINER Pengzhan Hao <haopengzhan@gmail.com>
RUN apt-get update && apt-get install -y libevent-2.0-5 libevent-openssl-2.0.5 libssl-dev


COPY main /bin/

EXPOSE 10200
CMD main 0 10200
