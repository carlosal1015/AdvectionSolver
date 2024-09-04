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

clang-format -style=file:.clang-format -i *.cc
clang-format -style=file:.clang-format -i include/*.hh
clang-format -style=file:.clang-format -i src/*.cc