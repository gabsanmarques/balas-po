@echo off
setlocal enabledelayedexpansion

REM Definindo caminho pro executável
set MAIN_PATH=.\main

REM Verifique se o executável main existe, e se não existir, execute o make
if not exist "%MAIN_PATH%" make

REM Definindo pastas de entrada e saída
set INPUT_FOLDER=.\inputs
set OUTPUT_FOLDER=.\outputs

REM Verifique se a pasta de saída existe e crie-a se não existir
if not exist "%OUTPUT_FOLDER%" mkdir "%OUTPUT_FOLDER%"

REM Rodando main para as entradas
for %%i in ("%INPUT_FOLDER%\*.*") do (
    REM Obtendo o nome do arquivo
    set "INPUT_NAME=%%~ni"

    REM Executando a main e direcionando as saídas para a pasta output
    %MAIN_PATH% "%INPUT_FOLDER%\!INPUT_NAME!.txt" > "%OUTPUT_FOLDER%\output_!INPUT_NAME!.txt"
)

echo Execucao concluida.