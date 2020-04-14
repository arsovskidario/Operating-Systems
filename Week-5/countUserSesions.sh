#!/bin/bash
read -p "Enter the username : " username

who | grep -w "${username}" | wc -l

