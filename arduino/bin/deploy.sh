#!/usr/bin/env bash

PORT=$(cat bin/port)

pio run --target clean
pio run --target upload --upload-port $PORT
sleep 1
pio device monitor -p $PORT