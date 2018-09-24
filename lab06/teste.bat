@echo off
set exe=lab06
set testeFolder=testes\arq

for %%A in (01 02 03) DO (
echo *************************
echo *************************
echo **                     **
echo **       Teste %%A       **
echo **                     **
echo *************************
echo *************************
%exe% < testes\arq%%A.in > testes\arq%%A_saida.res
FC /N testes\arq%%A_saida.res testes\arq%%A.res
pause
cls
)