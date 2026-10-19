#!/bin/bash


echo "          array"
./structorium --file test.data --query 'MPUSH myarr apple'
./structorium --file test.data --query 'MPUSH myarr banana'
./structorium --file test.data --query 'MPUSH myarr 0 cherry'
./structorium --file test.data --query 'MGET myarr'
./structorium --file test.data --query 'MSIZE myarr'
./structorium --file test.data --query 'MSET myarr 0 date'
./structorium --file test.data --query 'MDEL myarr 1'
./structorium --file test.data --query 'MGET myarr'

echo "          stack"
./structorium --file test.data --query 'SPUSH mystack 100'
./structorium --file test.data --query 'SPUSH mystack 200'
./structorium --file test.data --query 'SPUSH mystack 300'
./structorium --file test.data --query 'SGET mystack'
./structorium --file test.data --query 'SPOP mystack'
./structorium --file test.data --query 'SGET mystack'

echo "          queue"
./structorium --file test.data --query 'QPUSH myqueue first'
./structorium --file test.data --query 'QPUSH myqueue second'
./structorium --file test.data --query 'QPUSH myqueue third'
./structorium --file test.data --query 'QGET myqueue'
./structorium --file test.data --query 'QPOP myqueue'
./structorium --file test.data --query 'QGET myqueue'

echo "          list"
./structorium --file test.data --query 'FPUSH mylist back A'
./structorium --file test.data --query 'FPUSH mylist back B'
./structorium --file test.data --query 'FPUSH mylist front C'
./structorium --file test.data --query 'FGET mylist'
./structorium --file test.data --query 'FPUSH mylist before B X'
./structorium --file test.data --query 'FPUSH mylist after A Y'
./structorium --file test.data --query 'FGET mylist'
./structorium --file test.data --query 'FDEL mylist X'
./structorium --file test.data --query 'FGET mylist'

echo "          double_list"
./structorium --file test.data --query 'LPUSH mydll back 1'
./structorium --file test.data --query 'LPUSH mydll back 2'
./structorium --file test.data --query 'LPUSH mydll front 0'
./structorium --file test.data --query 'LGET mydll'
./structorium --file test.data --query 'LPUSH mydll before 2 99'
./structorium --file test.data --query 'LGET mydll'
./structorium --file test.data --query 'LPOP mydll back'
./structorium --file test.data --query 'LGET mydll'

echo "          tree"
./structorium --file test.data --query 'TINSERT mytree 10'
./structorium --file test.data --query 'TINSERT mytree 5'
./structorium --file test.data --query 'TINSERT mytree 20'
./structorium --file test.data --query 'TINSERT mytree 3'
./structorium --file test.data --query 'TINSERT mytree 7'
./structorium --file test.data --query 'TGET mytree'
./structorium --file test.data --query 'ISMEMBER mytree 7'
./structorium --file test.data --query 'ISMEMBER mytree 99'
./structorium --file test.data --query 'TDEL mytree 10'
./structorium --file test.data --query 'TGET mytree'

echo "file"
cat test.data
