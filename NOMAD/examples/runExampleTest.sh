#!/bin/bash

    executable=$1
    param_file="empty" 
    if [ $# == 2 ]
    then
        param_file =$2  
    fi
    echo "Running Example test $executable"
    set -o pipefail 
    $executable $param_file | tee runTestLog.txt
    set -o pipefail
    if [ $? != 0 ]
    then
        exit 1
    else
        test_passed=`grep termination runTestLog.txt`
        test_failed=`grep -e exception -e Exception -e Error -e abort -e terminate runTestLog.txt`
        if [ "$test_passed" != "" ] && [ "$test_failed" == "" ]
        then
            exit 0
        else
            exit 1
        fi
    fi
    
