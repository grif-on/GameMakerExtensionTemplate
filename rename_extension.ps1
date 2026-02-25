<#
MIT License

Copyright (c) 2026 Grif_on

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
#>

#region Arguments

param (
  [string] $Name # To skip interacive prompt
)

#endregion

#region Interactive prompt and arguments validation

if ($Name -eq "") {
  $prompt = "What name this extension will have? "
  $Name = Read-Host -Prompt $prompt
}

if ($Name -eq "") {
  Write-Error -Message "Canceled due to empty prompt result"
  exit
}

# Splitted in half to keep it safe from renaming
$original_name = "GameMakerExte" + "nsionTemplate"

# This line will be renamed by script as well
$current_name = "GameMakerExtensionTemplate"

if ($Name -eq $current_name) {
  Write-Error -Message "Extension already named like that."
  exit
}
else {
  if ($current_name -ne $original_name) {
    Write-Host -Message "Hey there."
    Write-Host -Message "It seems you are trying to rename already renamed extension."
    Write-Host -Message "This script should handle that, but you need to double check that it works correctly"
    Write-Host -Message "with changes to extension that you are presumably alreay done."
    Write-Host -Message "Use git or other version control tool before proceeding."
    $prompt = "Proceed? (y/N) "
    $proceed_answer = Read-Host -Prompt $prompt
    if ($proceed_answer -eq "y" -or $proceed_answer -eq "Y") {
      Write-Host -Message "Alright, proceeding."
    }
    else {
      Write-Host -Message "Canceled."
      exit
    }
  }
}

#endregion Interactive prompt and arguments validation

#region Main script work

function ultimateRenamer([string] $directory, [string] $rename_target, [string] $rename_result) {

  # Note that -Force here needed since i'm not sure how .gitignore is treated on linux and macos comparing to windows (dot in name begining)
  $all_items = Get-ChildItem -Path $directory -Force
  | Where-Object -Property Name -ne ".git"
  | Where-Object -Property Name -ne "out"
  | Where-Object -Property Name -ne "build"
  | Where-Object -Property Name -NotMatch "\.(?:dll|exp|lib|obj|exe|so|dylib)$"

  $directories = @()
  $files = @()
  
  foreach ($item in $all_items) {
    $dir = Where-Object -InputObject $item -Property Attributes -Match Directory
    $file = Where-Object -InputObject $item -Property Attributes -NotMatch Directory
    if ($dir) {
      $directories += $dir
    }
    if ($file) {
      $files += $file
    }
  }
  
  # Replace text inside files
  foreach ($f in $files) {
    $file_content = Get-Content -Path $f
    
    for ($i = 0; $i -lt $file_content.Count; $i++) {
      $file_content[$i] = $file_content[$i] -replace $rename_target, $rename_result
    }
    
    $file_content_string = $file_content -join "`n"
    Set-Content -NoNewline -Path $f -Value $file_content_string
  }
  
  # Replace file names
  foreach ($f in $files) {
    $name = Split-Path $f -Leaf
    $path = Split-Path $f -Parent
    $new_path_name = "$path/$($name -replace $rename_target, $rename_result)"
    Rename-Item -Path $f -NewName $new_path_name
  }
  
  # Replace directory names and go in to recursion
  foreach ($d in $directories) {
    $name = Split-Path $d -Leaf
    $path = Split-Path $d -Parent
    $new_name = $name -replace $rename_target, $rename_result
    $new_path_name = "$path/$($new_name)"
    if ($name -ne $new_name) {
      Rename-Item -Path $d -NewName $new_path_name
    }
  
    ultimateRenamer -directory $new_path_name -rename_target $rename_target -rename_result $rename_result
  }
  
}

ultimateRenamer -directory "./" -rename_target "GameMakerExtensionTemplate" -rename_result $Name

#endregion Main script work