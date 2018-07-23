#!/bin/bash
sudo docker stop e2
sudo docker rm e2
sleep 2
sudo docker build -t edge-server .
sudo docker run -i -m=4m -p 1234:1234 --name e2 edge-server
