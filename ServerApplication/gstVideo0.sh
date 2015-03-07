#!/bin/bash

gst-launch -e v4l2src device=/dev/video0 ! 'video/x-raw-yuv,width=1280,height=720,framerate=30/1' ! nv_omx_h264enc quality-level=2 ! h264parse ! mpegtsmux ! tcpserversink host=192.168.2.4 port=5000

exit 0
