@echo off
chcp 65001 > nul
title Git Auto Push - Data Structures

:: =============================================
::  자동 깃 커밋 + 푸쉬 스크립트
::  더블클릭 하면 자동으로 변경사항 저장됨
:: =============================================

:: 저장소 경로로 이동
cd /d "C:\Users\smoun\PycharmProjects\VScode_\data_structures_docker"

echo.
echo ========================================
echo   Git Auto Push - Data Structures
echo ========================================
echo.

:: 현재 상태 확인
echo [1/4] 변경사항 확인 중...
git status
echo.

:: 변경사항이 있는지 체크
git diff --quiet && git diff --staged --quiet
if %errorlevel% == 0 (
    echo ✓ 변경사항이 없습니다. 이미 최신 상태입니다.
    echo.
    pause
    exit /b 0
)

:: 모든 변경사항 스테이징
echo [2/4] 변경사항 스테이징 중...
git add -A
echo.

:: 커밋 메시지 자동 생성 (날짜+시간 포함)
set COMMIT_MSG=Auto commit: %date% %time:~0,8%

echo [3/4] 커밋 중...
echo 커밋 메시지: %COMMIT_MSG%
git commit -m "%COMMIT_MSG%"
echo.

:: 푸쉬
echo [4/4] GitHub에 푸쉬 중...
git push origin main
echo.

if %errorlevel% == 0 (
    echo ========================================
    echo   ✓ 푸쉬 완료! GitHub에 업로드됐어요.
    echo ========================================
) else (
    echo ========================================
    echo   ✗ 푸쉬 실패. 오류를 확인해주세요.
    echo ========================================
)

echo.
pause
