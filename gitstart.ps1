param (
    [string]$mode = "private"
)

$currentDirectory = Get-Location
$directoryName = $currentDirectory.Name

echo "Current directory: $currentDirectory"
echo "Directory name: $directoryName"
git init
echo "Git init"

if ($mode -eq "public") {
    gh repo create $directoryName --public --source=. --remote=origin
    echo "Create public repository"
}
elseif ($mode -eq "private") {
    gh repo create $directoryName --private --source=. --remote=origin
    echo "Create private repository"
}
else {
    Write-Host "Invalid mode: $mode. Please use 'public' or 'private'."
    exit 1
}

if (Test-Path -Path "Klib\.git") {
    Remove-Item -Path "Klib\.git" -Recurse -Force
    echo "Remove Klib\.git"
}

git add .
echo "Add all files"

git commit -m "frist commit"
echo "Commit"

git branch -m main
echo "Rename branch to main"

git push -u origin main
echo "Push to origin"
