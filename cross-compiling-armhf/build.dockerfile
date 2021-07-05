FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y \
      build-essential \
      wget \
      vim \
      python3 \
      python3-pip \
      git && \
    ln -s /usr/bin/python3 /usr/bin/python

RUN apt-get update && \
    # apt-get install -y lib32z1 libc6-i386 lib32stdc++6
    apt-get install -y crossbuild-essential-armhf

WORKDIR /usr

RUN git clone https://github.com/raspberrypi/tools.git

WORKDIR /usr/tools

RUN echo "export PATH=/usr/tools/arm-bcm2708/arm-linux-gnueabihf/bin:$PATH" >> ~/.bashrc

CMD [ "/bin/bash" ]