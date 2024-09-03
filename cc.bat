@echo off
set "execute_dir=bin"
set "output=main"
echo compiling...
g++ -o %execute_dir%\%output% %1
echo save the output to %execute_dir%\%output%.exe
echo Program %execute_dir%\%output%.exe:
%execute_dir%\%output%.exe