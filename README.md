# Learning BehaviourTree.CPP
This is just a project of implementing the tutorials of [BehaviourTree.CPP](https://www.behaviortree.dev/tutorials_summary/) using Docker and CMake. Take note that this project is being tested on Ubuntu 20.04 environment only.

## RUNNING ON DOCKER CONTAINER

### To build this image
```
./builldDockerImage.sh
```

### To run the docker image
```
./runDockerFile.sh
```

### To run any executables
For example, executable of tutorial01
```
./learningBehaviourTree_tutorial01
```

### To exit the docker container
```
exit
```

## RUNNING ON LOCAL MACHINE (not tested yet)

### Install libwxgtk3.0-dev binaries
```
sudo apt-get update -y
sudo apt-get install -y libwxgtk3.0-gtk3-dev  (PS: for Ubuntu 20.04)
sudo apt-get install -y libwxgtk3.0-dev  (PS: for other versions of Ubuntu)
```

### Install the BehaviourTree.CPP into your local machine as instructed [here](https://github.com/BehaviorTree/BehaviorTree.CPP)
```
mkdir build; cd build
cmake ..
make
sudo make install
```

### CMake and build
In this directory
```
mkdir build
cd build
cmake ..
cmake --build .
```

### Run any of the exectubales 
For example, 
```
./learningBehaviourTree_tutorial01
```