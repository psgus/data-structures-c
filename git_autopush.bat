@echo off
chcp 65001 > nul
title Git Auto Push - Data Structures

cd /d "C:\Users\smoun\PycharmProjects\VScode_\data_structures_docker"

echo.
echo ========================================
echo   Git Auto Push - Data Structures
echo ========================================
echo.

echo [1/4] 변경사항 확인 중...
git status
echo.

git status --porcelain > temp_status.txt 2>&1
for %%i in (temp_status.txt) do set SIZE=%%~zi
del temp_status.txt

if "%SIZE%"=="0" (
    echo 변경사항이 없습니다. 이미 최신 상태입니다.
    echo.
    pause
    exit /b 0
)

echo [2/4] 변경사항 스테이징 중...
git add -A
echo.

echo [3/4] 커밋 중...
for /f "tokens=1-3 delims=/ " %%a in ("%date%") do (
    set YY=%%a
    set MM=%%b
    set DD=%%c
)
if "%MM%"=="01" set MON=Jan
if "%MM%"=="02" set MON=Feb
if "%MM%"=="03" set MON=Mar
if "%MM%"=="04" set MON=Apr
if "%MM%"=="05" set MON=May
if "%MM%"=="06" set MON=Jun
if "%MM%"=="07" set MON=Jul
if "%MM%"=="08" set MON=Aug
if "%MM%"=="09" set MON=Sep
if "%MM%"=="10" set MON=Oct
if "%MM%"=="11" set MON=Nov
if "%MM%"=="12" set MON=Dec
git commit -m "Update: %MON% %DD% %YY%"
echo.

echo [4/4] GitHub에 푸시 중...
git push origin main
echo.

if %errorlevel% == 0 (
    echo ========================================
    echo   푸시 완료! GitHub에 업로드됐어요.
    echo ========================================
) else (
    echo ========================================
    echo   푸시 실패. 오류를 확인해주세요.
    echo ========================================
)

echo.
pause
