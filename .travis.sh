if [ $ANALYZE = "true" ]; then
    if [ "$CC" = "clang" ]; then
        #scan-build -h
        scan-build --use-cc=`which clang` --use-c++=`which clang++` cmake -G "Unix Makefiles" ..
        scan-build -enable-checker security.FloatLoopCounter \
          -enable-checker security.insecureAPI.UncheckedReturn \
          --status-bugs -v \
          make
    else
        cd ..
        #cppcheck --help
        cppcheck --template "{file}({line}): {severity} ({id}): {message}" \
            --enable=style --force --std=c++11 \
            --inline-suppr \
            src/ 2> cppcheck.txt
        if [ -s cppcheck.txt ]; then
            cat cppcheck.txt
            exit 1
        fi
    fi
else
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
    make
fi
