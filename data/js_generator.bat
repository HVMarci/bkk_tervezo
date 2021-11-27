@echo off
for %%f in (*.txt) do echo %%~nf && csvtojsarray %%f %%~nf "," > %%~nf.js
