#!/bin/sh
##
## start.sh for Project in /home/simonrelet/SMA-Final
##
## Made by simonrelet
## Login   <simonrelet@epita.fr>
##
## Started on  Tue 22 Apr 2014 08:38:44 AM PDT simonrelet
## Last update Tue 22 Apr 2014 08:59:45 AM PDT simonrelet
##

#! /bin/sh

i=0
while [ $i -lt 50 ]
do
    ./src/clients/agents/clientTest 127.0.0.1 8088 test$i test > logs/log_client_$i &
    i=$((i + 1))
done
