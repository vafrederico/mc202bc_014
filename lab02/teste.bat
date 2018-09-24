@echo off
set exe=lab02
set testeFolder=testes\arq

for %%A in (01 02 03 04 05 06 07 08 09 10) DO (
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