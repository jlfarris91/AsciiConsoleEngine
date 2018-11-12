echo sourcePath: %~f1
echo destinationPath: %~f2

copy "%~f1Game.exe" "%~f2Game.exe" /y
copy "%~f1AsciiEngine.lib" "%~f2AsciiEngine.lib" /y
copy "%~f1ConsoleGL.lib" "%~f2ConsoleGL.lib" /y
copy "%~f1Math.lib" "%~f2Math.lib" /y
copy "%~f1Shared.lib" "%~f2Shared.lib" /y