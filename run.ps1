cls
# https://devblogs.microsoft.com/powershell-community/determine-if-a-folder-exists
$Folder = '.venv'
if (Test-Path -Path $Folder) {
    Write-Host "$Folder exists!"
    conda activate .\.venv\
    mdformat README
    ruff check plotting.py
} else {
    Write-Host "$Folder doesn't exist."
    conda env create -f environment.yml --prefix .venv
}

# clang-format -style=file:.clang-format -i *.cc src/*.cc include/*.hh
Remove-Item -LiteralPath "$pwd\build" -Force -Recurse
cmd.exe "/K" '"C:\Program Files (x86)\Intel\oneAPI\setvars.bat" && powershell'
cmake -S . -B build -GNinja -DCMAKE_BUILD_TYPE=Release
cmake --build build --target all
