FROM ubuntu:18.04

LABEL maintainer="JianKai Wang <gljankai@gmail.com>"

RUN apt-get update && \
    apt-get install -y build-essential && \
    apt-get install -y clang && \
    apt-get install -y llvm

CMD ["bash"]