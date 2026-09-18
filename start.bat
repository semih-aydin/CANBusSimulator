@echo off
setlocal enabledelayedexpansion

cd /d "%~dp0"

if not exist "bin" mkdir "bin"
if not exist "logs" mkdir "logs"

where gcc >nul 2>&1
if %errorlevel% equ 0 (
    set "CC=gcc"
) else if exist "C:\Program Files\CodeBlocks\MinGW\bin\gcc.exe" (
    set "CC=C:\Program Files\CodeBlocks\MinGW\bin\gcc.exe"
) else if exist "C:\MinGW\bin\gcc.exe" (
    set "CC=C:\MinGW\bin\gcc.exe"
) else (
    echo Hata: gcc derleyicisi bulunamadi!
    echo Lutfen MinGW veya CodeBlocks kurup gcc'yi PATH ortam degiskenine ekleyin.
    pause
    exit /b 1
)

echo Derleniyor (%CC%)...
"%CC%" -Wall -o bin\can_sim.exe src\main.c src\can_frame.c src\can_bus.c src\can_node.c src\ecu_motor.c src\ecu_abs.c src\ecu_dashboard.c src\ecu_airbag.c src\ecu_klima.c src\ecu_direksiyon.c src\ecu_kabin.c src\ecu_lastik.c src\can_json.c src\can_logger.c src\can_parser.c src\can_fuzzer.c src\can_detector.c

if %errorlevel% neq 0 (
    echo.
    echo Derleme hatasi!
    pause
    exit /b 1
)

if not exist "dashboard\node_modules" (
    echo Dashboard bagimliliklari eksik, npm install calistiriliyor...
    cd dashboard
    call npm install
    cd ..
)

echo Simulator baslatiliyor...
start "CAN Bus Simulator" bin\can_sim.exe

echo Dashboard baslatiliyor...
cd dashboard
start "CAN Dashboard" cmd /k "npm run dev"
cd ..

echo.
echo =========================================
echo   CAN Bus Simulator basariyla baslatildi!
echo   Simulator : Calisiyor
echo   Dashboard : http://localhost:5173
echo =========================================

