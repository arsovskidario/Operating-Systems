#!/bin/bash

[ $# -gt 0 ] || exit 2

read -p "Enter your username:" username
read -p "Enter your password:" password

if [ "${username}" != "$1" ] ; then
	echo " Wrong username"
	exit 2
fi
shift 1

if [ "${password}" != "$1" ]; then
	echo "Wrong password"
	exit 2
fi

echo " Log in succesful "
exit 0
