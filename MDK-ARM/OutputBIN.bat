@echo off

@REM 可执行文件(Bin)文件名
set BIN_NAME=980_APP

@REM 可执行文件(Bin)文件路径
set BIN_PATH=..\BIN

@REM 定制Bin输出路径
set OUTPUT_PATH=..\BIN

@REM 软件版本文本路径
set VERSION_FILE_PATH=..\User\Configure.h

@REM 硬件版本字符串的格式
set HAREWARE_VERSION="#define BSP_HARDWARE_VERSION"

@REM 软件版本字符串的格式
set SOFTWARE_VERSION="#define BSP_SOFTWARE_VERSION"

@REM 获取系统日期和时间
set YEAR=%date:~0,4%
set MONTH=%date:~5,2%
set DAY=%date:~8,2%
set HOUR=%TIME:~0,2%
set MINUTE=%TIME:~3,2%
set SECOND=%TIME:~6,2%
set CURRENT_DATA=%YEAR%%MONTH%%DAY%_%HOUT%%MINUTE%%SECOND%

@REM 获取硬件版本
for /f "tokens=3 delims= " %%i in ('findstr /C:%HAREWARE_VERSION% %VERSION_FILE_PATH%') do set HW_Ver=%%i
set HW_Ver=%HW_Ver:~0%

@REM 获取软件版本
for /f "tokens=3 delims= " %%i in ('findstr /C:%SOFTWARE_VERSION% %VERSION_FILE_PATH%') do set SW_Ver=%%i
set SW_Ver=%SW_Ver:~0%

@REM 定制Bin文件名
set output_file_name=%BIN_NAME%_V%SW_Ver%_V%HW_Ver%_%CURRENT_DATA%

@REM 显示并复制Bin文件
echo "Output Bin file: %OUTPUT_PATH%\%output_file_name%.bin"
copy %BIN_PATH%\%BIN_NAME%.bin %OUTPUT_PATH%\%output_file_name%.bin

exit
