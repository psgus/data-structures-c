# =============================================
#  자동 깃 커밋 + 푸쉬 PowerShell 스크립트
#  실행 방법: 우클릭 → "PowerShell로 실행"
# =============================================

$repoPath = "C:\Users\smoun\PycharmProjects\VScode_\data_structures_docker"

Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "   Git Auto Push - Data Structures" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# 저장소 경로로 이동
Set-Location $repoPath

# 현재 상태 확인
Write-Host "[1/4] 변경사항 확인 중..." -ForegroundColor Yellow
git status
Write-Host ""

# 변경사항 체크
$changes = git status --porcelain
if (-not $changes) {
    Write-Host "✓ 변경사항이 없습니다. 이미 최신 상태입니다." -ForegroundColor Green
    Write-Host ""
    Read-Host "엔터를 눌러 종료..."
    exit 0
}

# 모든 변경사항 스테이징
Write-Host "[2/4] 변경사항 스테이징 중..." -ForegroundColor Yellow
git add -A
Write-Host ""

# 커밋 메시지 자동 생성
$timestamp = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
$commitMsg = "Auto commit: $timestamp"

Write-Host "[3/4] 커밋 중..." -ForegroundColor Yellow
Write-Host "커밋 메시지: $commitMsg"
git commit -m $commitMsg
Write-Host ""

# 푸쉬
Write-Host "[4/4] GitHub에 푸쉬 중..." -ForegroundColor Yellow
git push origin main
Write-Host ""

if ($LASTEXITCODE -eq 0) {
    Write-Host "========================================" -ForegroundColor Green
    Write-Host "   ✓ 푸쉬 완료! GitHub에 업로드됐어요." -ForegroundColor Green
    Write-Host "========================================" -ForegroundColor Green
} else {
    Write-Host "========================================" -ForegroundColor Red
    Write-Host "   ✗ 푸쉬 실패. 오류를 확인해주세요." -ForegroundColor Red
    Write-Host "========================================" -ForegroundColor Red
}

Write-Host ""
Read-Host "엔터를 눌러 종료..."
