param(
    [int]$Jobs = 4,
    [switch]$Clean,
    [switch]$Reconfigure
)

$ErrorActionPreference = 'Stop'

$repoRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$sourceDir = $repoRoot
$buildDir = Join-Path $repoRoot 'build/Desktop_Qt_6_11_1_MinGW_64_bit_Debug'
$cmakeExe = 'E:/Qt/Tools/CMake_64/bin/cmake.exe'
$makeExe = 'E:/Qt/Tools/mingw1310_64/bin/mingw32-make.exe'
$prefixPath = 'E:/Qt/6.11.1/mingw_64'

if (-not (Test-Path $sourceDir)) {
    throw 'This script must be run from the BookManagementSystem repository.'
}

if (-not (Test-Path (Join-Path $sourceDir 'CMakeLists.txt'))) {
    throw 'CMakeLists.txt was not found. Run this script from the BookManagementSystem repository root.'
}

if (-not (Test-Path $cmakeExe)) {
    throw "CMake was not found at $cmakeExe"
}

if (-not (Test-Path $makeExe)) {
    throw "mingw32-make was not found at $makeExe"
}

if ($Clean -and (Test-Path $buildDir)) {
    Remove-Item -Recurse -Force $buildDir
}

New-Item -ItemType Directory -Force -Path $buildDir | Out-Null

$cacheFile = Join-Path $buildDir 'CMakeCache.txt'
if ($Reconfigure -or -not (Test-Path $cacheFile)) {
    & $cmakeExe `
        -S $sourceDir `
        -B $buildDir `
        -G 'MinGW Makefiles' `
        -DCMAKE_BUILD_TYPE=Debug `
        -DCMAKE_PREFIX_PATH=$prefixPath
}

& $makeExe -C $buildDir -j $Jobs