#!/bin/bash
for f in $2/*.in 
do
    testname=${f#$2/}
    testname=${testname%.in}
    echo -e "\e[39mTesting $testname \t \c"

    #Checking memory leaks
    valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./$1 <$f >$2/tmp.out 2>/dev/null
    
    if [ $? -eq 15 ] 
    then 
        echo -e "\e[31mfailed (memory leak)"
        continue
    fi
    
    ./$1 <$f >$2/tmp.out 2>$2/tmp.err
    
    #Checking stdout correctness
    if ! diff $2/tmp.out ${f%in}out >/dev/null 
        then
        echo -e "\e[31mfailed (stdout)"
        continue
    fi
    
    #Checking stderr corectness
    if ! diff $2/tmp.err ${f%in}err >/dev/null 
        then
            echo -e "\e[31mfailed (stderr)"
            continue
    fi
    echo -e "\e[32mpassed"
done

#Clearing temporary files   
rm $2/tmp.out
rm $2/tmp.err
