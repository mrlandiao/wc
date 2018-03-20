@echo off
wc.exe -c file.c
wc.exe -w file.c
wc.exe -l file.c
wc.exe -c -w -l file.c
wc.exe -a file.c
wc.exe -a -c -w -l file.c
wc.exe -c -l -a file.c
wc.exe -e stopList.txt
wc.exe -c -l -e stopList.txt -o result.txt
wc.exe -c -l file.c -s
wc.exe -l -a file.c -s -o result.txt