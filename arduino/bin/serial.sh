#!/usr/bin/env bash

PORT=$(cat bin/port)

pio device monitor -p $PORT
