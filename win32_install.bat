@rem spacegameengine is a portable easy to use game engine written in C++.
@rem Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)
@rem
@rem This program is free software; you can redistribute it and/or
@rem modify it under the terms of the GNU Lesser General Public License
@rem as published by the Free Software Foundation; either version 2
@rem of the License, or (at your option) any later version.
@rem
@rem This program is distributed in the hope that it will be useful,
@rem but WITHOUT ANY WARRANTY; without even the implied warranty of
@rem MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
@rem GNU Lesser General Public License for more details.
@rem
@rem You should have received a copy of the GNU Lesser General Public License
@rem along with this program; if not, write to the Free Software
@rem Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

@set target="null"

@if "%1" == "VC7" set target="Visual Studio 7 .NET 2003"
@if "%1" == "vc7" set target="Visual Studio 7 .NET 2003"
@if "%1" == "VC8" set target="Visual Studio 8 2005"
@if "%1" == "vc8" set target="Visual Studio 8 2005"

@if "%1" == "help" goto Help
@if "%1" == "-h" goto Help

@if %target% == "null" goto UsageFailure
@goto Config

:UsageFailure
@echo Usage failure: Type 'win32_install help' for more information.
@goto Exit

:Config
@call cmake -G %target% -D CMAKE_LIBRARYPATH=./project/win32/lib/ -D ENABLE_DEVIL:=1 -D ENABLE_TEST:=1 -D ENABLE_OPENGL:=1 -D ENABLE_DINPUT:=1 -D ENABLE_FREETYPE:=1 -D ENABLE_OPENAL:=1 -D ENABLE_VORBIS:=1 -D ENABLE_WAVE:=1 -D ENABLE_TRUETYPE:=1 -D ENABLE_ZLIB:=1 -D ENABLE_D3D9:=1 .

:Cleanup
@call rd /S /Q projects\windows\lib32

:Extract
@call projects\windows\lib32.exe
@goto Exit

:Help
@echo "win32_install [option]"
@echo Option can be:
@echo   vc7  - Visual Studio 7 (.NET 2003)
@echo   vc8  - Visual Studio 8 (.NET 2005)
@echo   help - Displays this help.

:Exit
