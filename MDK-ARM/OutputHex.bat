@echo off

@REM 可执行文件(Hex)文件名
set HEX_NAME=808_new-APP

@REM 可执行文件(Hex)文件路径
set HEX_PATH=.\808_new-APP

@REM 定制Hex输出路径
set OUTPUT_PATH=..\BIN

@REM 软件版本文本路径
set VERSION_FILE_PATH=..\Core\src\main.c

@REM 软件版本字符串的格式
set SOFTWRE_VERSION="#define SOFTWARE_VERSION"

@REM 获取系统日期和时间
set YEAR=%date:~0,4%
set MONTH=%date:~5,2%
set DAY=%date:~8,2%
set HOUR=%TIME:~0,2%
set MINUTE=%TIME:~3,2%
set SECOND=%TIME:~6,2%
set CURRENT_DATA=%YEAR%%MONTH%%DAY%_%HOUT%%MINUTE%%SECOND%

@REM 获取软件版本
for /f "tokens=3 delims= " %%i in ('findstr /C:%SOFTWRE_VERSION% %VERSION_FILE_PATH%') do set SW_Ver=%%i
set SW_Ver=%SW_Ver:~0%

@REM 定制Hex文件名
set output_file_name=%HEX_NAME%_V%SW_Ver%_%CURRENT_DATA%

@REM 显示并复制Hex文件
echo "Output hex file: %OUTPUT_PATH%\%output_file_name%.hex"
copy %HEX_PATH%\%HEX_NAME%.hex %OUTPUT_PATH%\%output_file_name%.hex

exit
