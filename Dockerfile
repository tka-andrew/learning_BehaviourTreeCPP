FROM ubuntu:20.04

# Needed for Ubuntu installation
ENV DEBIAN_FRONTEND=noninteractive 
ENV TZ=Etc/UTC

# Install CMake and some necessary packages
# REFERENCE: https://github.com/BehaviorTree/BehaviorTree.CPP/
# The libzmq3-dev libboost-dev are the recommended dependencies for BehaviourTreeCpp
# The libboost-all-dev is added to support coroutine of tutorial09
RUN apt-get update && apt-get install build-essential ca-certificates cmake git libzmq3-dev libboost-dev libboost-all-dev -y --no-install-recommends

RUN mkdir -p /src/LearningBehaviourTree/build
COPY . /src/LearningBehaviourTree/
RUN cd /src/LearningBehaviourTree/build && cmake .. && cmake --build .
WORKDIR /src/LearningBehaviourTree/build