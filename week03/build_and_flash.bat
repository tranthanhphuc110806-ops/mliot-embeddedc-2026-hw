@echo off
echo =====================================
echo    STM32 Build and Flash Script
echo =====================================

:: -------------------------------------
:: 5.1 Clean
:: -------------------------------------
echo.
echo [1/4] Cleaning old build folder...

if exist build (
    echo Cleaning build directory...
    rmdir /s /q build
)

:: -------------------------------------
:: 5.2 Configure
:: -------------------------------------
echo.
echo [2/4] Configuring project...

cmake -B build -G Ninja

if %ERRORLEVEL% neq 0 (
    echo.
    echo Configure FAILED!
    pause
    exit /b 1
)

:: -------------------------------------
:: 5.3 Build
:: -------------------------------------
echo.
echo [3/4] Building project...

cmake --build build

if %ERRORLEVEL% neq 0 (
    echo.
    echo Build FAILED!
    pause
    exit /b 1
)

:: -------------------------------------
:: Đổi tên file .bin theo yêu cầu đề
:: -------------------------------------
if not exist build\app_firmware.bin (
    echo [ERROR] app_firmware.bin not found in build directory!
    pause
    exit /b 1
)

:: -------------------------------------
:: 5.4 Flash
:: -------------------------------------
echo.
echo [4/4] Flashing firmware...

STM32_Programmer_CLI ^
-c port=SWD ^
-w build\app_firmware.bin 0x08000000 ^
-v ^
-rst

if %ERRORLEVEL% neq 0 (
    echo.
    echo Flash FAILED!
    pause
    exit /b 1
)

echo.
echo =====================================
echo Build and Flash SUCCESS!
echo =====================================

pause