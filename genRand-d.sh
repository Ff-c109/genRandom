#!/bin/bash

cd /opt/genRandom
screen -d -m env LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH ./control-server
