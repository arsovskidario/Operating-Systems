#!/bin/bash

FAKE=$PATH
echo $FAKE | tr ":" " " | awk '{ print NF }'
