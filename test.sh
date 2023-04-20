mkdir -p .report/test
./build/axmc/axmc ./test/Def.txt ./test
cd build
make -j axm-test && \
    cd test && \
    ctest
