#!/bin/bash
echo "Checking : '$1'"
len="${#1}"
if test $len -ge 8 ; then
    echo "$1" | grep -q [0-9]
    if test $? -eq 0 ; then
        echo "$1" | grep -q [A-Z]
        if test $? -eq 0 ; then
            echo "$1" | grep -q [a-z]  
            if test $? -eq 0 ; then
                echo "$1" | grep -q "[@\#$%&\*-\=]"
                if test $? -eq 0 ; then
                    echo "Valid Password"
                else
                    echo "Requires a symbol (@, #, $, %, &, *, +, -, or =)"
                fi
            else
                echo "Requires a lower case letter"
            fi
        else
            echo "Requires a capital char" 
        fi
    else
        echo "Requires a number"   
    fi
else
    echo "Too Short.  Requires 8 Characters"
fi
