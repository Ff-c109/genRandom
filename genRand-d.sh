#!/bin/bash

cd /opt/genRandom
env LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH ./convert-cfg
screen -d -m env LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH ./control-server
