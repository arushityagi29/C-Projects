#!/bin/bash

VERBOSE=0
EXACTERR=0
COLOR=1
test_folder=tests

for test in $(find $test_folder -name '*test'); do

    for script in $(find $test_folder -name 'test_*' ); do
        scriptname=$(basename $script .sh)
        err=$(sh $script 2> /dev/null)

        if [ $? -eq 0 ]; then
            if [ $VERBOSE -eq 1 ]; then
                if [ $COLOR -eq 1 ]; then
                    echo -e "\033[32mPASS\033[0m:\t$scriptname on $test"
                    if [ $EXACTERR -ne 0 ]; then
                        echo Message:
                        echo -e "\033[33m$err\033[0m"
                    fi
                else
                    echo -e "PASS:\t$scriptname on $test"
                    if [ $EXACTERR -ne 0 ]; then
                        echo Message:
                        echo $err
                    fi
                fi
            else
                echo -e "PASS\t$scriptname on $test"
            fi
        else
            if [ $COLOR -eq 1 ]; then
                echo -e "\033[31mFAIL\033[0m:\t$scriptname on $test"
                if [ $EXACTERR -ne 0 ]; then
                    echo Message:
                    echo -e "\033[33m$err\033[0m"
                fi
            else
                echo -e "FAIL\t$scriptname on $test"
                if [ $EXACTERR -ne 0 ]; then
                    echo Message:
                    echo $err
                fi
            fi
        fi
    done

done
