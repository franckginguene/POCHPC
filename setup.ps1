# Copy application files
Copy-Item build/bin/* setup/packages/com.scalian.projettype/data/tmp -Recurse
Copy-Item build/sources/GUI/ProjectTemplate_fr.qm setup/packages/com.scalian.projettype/data/tmp

Push-Location "setup"

# Archive files
&"C:\Program Files\7-Zip\7z.exe" a "./packages/com.scalian.projettype/data/app.7z" "./packages/com.scalian.projettype/data/tmp/*"

# Delete temp files
Remove-Item -Recurse -Force packages/com.scalian.projettype/data/tmp

# Create setup
&"C:\Qt\Tools\QtInstallerFramework\4.1\bin\binarycreator.exe" -c config/config.xml -p packages Setup.exe

Pop-Location
