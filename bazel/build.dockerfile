# Copyright 2019 JianKai Wang
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# stage 1: build
ARG IMAGE
FROM ${IMAGE} AS build

WORKDIR /usr/src

RUN apt-get update && \
    apt-get install -y \
      build-essential \
      openjdk-11-jdk \
      python3 \
      zip \
      unzip \
      wget

RUN ln -s /usr/bin/python3 /usr/bin/python && \
    ln -s /usr/lib/jvm/java-11-openjdk-armhf/include/linux/jni_md.h /usr/include/

ARG BAZEL_VERSION
ENV BAZEL_VERSION=${BAZEL_VERSION}

RUN wget https://github.com/bazelbuild/bazel/releases/download/$BAZEL_VERSION/bazel-$BAZEL_VERSION-dist.zip && \
    unzip bazel-$BAZEL_VERSION-dist.zip

RUN env EXTRA_BAZEL_ARGS="--host_javabase=@local_jdk//:jdk" bash ./compile.sh

# CMD ["./output/bazel"]

# stage 2: deployment
FROM ${IMAGE}

COPY --from=build /usr/src/output/bazel /usr/bin/bazel

RUN apt-get update && \
    apt-get install -y \
      build-essential \
      openjdk-11-jdk

RUN /usr/bin/bazel

CMD ["/bin/bash"]