#!/bin/bash 
    if [ $# -le 0 ]; then
        echo "Invalid input"
        exit 2
    fi

    if [[ "$1" =~ ^[a-zA-Z0-9]*$ ]]; then
        echo "Valid input" 
        exit 0
    else 
        echo "Invalid input"
    fi
