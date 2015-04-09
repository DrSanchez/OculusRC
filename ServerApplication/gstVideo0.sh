#!/bin/bash

gst-launch -e v4l2src device=/dev/video0 ! 'video/x-raw-yuv,width=640,height=480,framerate=30/1' ! nv_omx_h264enc quality-level=2 ! h264parse ! mpegtsmux ! tcpserversink host=10.103.3.205 port=5000

exit 0
