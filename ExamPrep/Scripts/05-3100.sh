#!/bin/bash

read -p "Enter your username " NAME

echo "$(users | egrep -c "${NAME}")"

#echo "$(who | egrep -c "${NAME}")"
