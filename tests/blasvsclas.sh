#!/bin/bash
echo "BLAS vs CLAS benchmarking shell script"
echo "-----------------------------------------------------"
echo "-----------------------------------------------------"
echo "-----------------------------------------------------"
echo "bin/bvc_ewise 100 100 100 10 10"
bin/bvc_ewise 100 100 100 10 10
echo "bin/bvc_outer 100 100 10 10 10"
bin/bvc_outer 100 100 10 10 100
echo "bin/bvc_inner 100 100 100 100 10"
bin/bvc_inner 100 100 100 100 10
echo "bin/bvc_mmdot 30 784 1024 200"
bin/bvc_mmdot 30 784 1024 200

