FROM ubuntu:latest

RUN apt-get update && apt-get install clang cmake valgrind wget patch mercurial -y;

WORKDIR /app