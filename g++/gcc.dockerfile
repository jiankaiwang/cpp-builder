FROM ubuntu:latest

LABEL maintainer="Jiankai Wang (gljankai@gmail.com)"

RUN apt-get update && \
    apt-get install -y build-essential

CMD ["bash"]