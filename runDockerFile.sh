# REFERENCE: https://jerin-electronics.medium.com/docker-now-ep1-python-opencv-in-docker-1dda564672c3
# REFERENCE: https://developpaper.com/question/how-to-make-alsa-play-available-in-docker/

XSOCK=/tmp/.X11-unix
XAUTH=/tmp/.docker.xauth
xauth nlist $DISPLAY | sed -e 's/^..../ffff/' | xauth -f $XAUTH nmerge -
PULSE_SERVER=unix:${XDG_RUNTIME_DIR}/pulse/native

sudo docker run -it --rm -e DISPLAY=$DISPLAY -e PULSE_SERVER=$PULSE_SERVER -v $XSOCK:$XSOCK -v $XAUTH:$XAUTH \
                -v ${XDG_RUNTIME_DIR}/pulse/native:${XDG_RUNTIME_DIR}/pulse/native \
                -v ~/.config/pulse/cookie:/root/.config/pulse/cookie \
                -e XAUTHORITY=$XAUTH -t tka-andrew/learning_behaviour-tree:latest \
