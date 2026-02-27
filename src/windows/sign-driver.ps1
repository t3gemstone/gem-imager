# sign-driver.ps1 — Run ONCE as Administrator, then commit the output files.
# No WDK required. Uses only Windows 10/11 built-in PowerShell cmdlets.
#
# Usage (elevated PowerShell):
#   cd <repo>\src\windows
#   .\sign-driver.ps1
#
# Output (commit both to git):
#   gem-imager-dfu.cat
#   t3-dfu.cer

#Requires -RunAsAdministrator

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
$InfPath   = Join-Path $ScriptDir "gem-imager-dfu.inf"
$CatPath   = Join-Path $ScriptDir "gem-imager-dfu.cat"
$CerPath   = Join-Path $ScriptDir "t3-dfu.cer"

# ── 1. Create self-signed code-signing cert (reuse if already exists) ─────────
$Subject = "CN=T3Foundation-DFU"
$Cert = Get-ChildItem "Cert:\LocalMachine\My" |
    Where-Object { $_.Subject -eq $Subject -and $_.NotAfter -gt (Get-Date) } |
    Sort-Object NotAfter -Descending | Select-Object -First 1

if (-not $Cert) {
    Write-Host "Creating self-signed certificate..."
    $Cert = New-SelfSignedCertificate `
        -Subject $Subject `
        -Type CodeSigning `
        -KeySpec Signature `
        -HashAlgorithm sha256 `
        -CertStoreLocation "Cert:\LocalMachine\My" `
        -NotAfter (Get-Date).AddYears(10)
}
Write-Host "Thumbprint: $($Cert.Thumbprint)"

# ── 2. Create catalog from INF ────────────────────────────────────────────────
Write-Host "Creating catalog..."
New-FileCatalog -Path $InfPath -CatalogFilePath $CatPath -CatalogVersion 2 | Out-Null

# ── 3. Sign the catalog ───────────────────────────────────────────────────────
Write-Host "Signing catalog..."
$sig = Set-AuthenticodeSignature -FilePath $CatPath -Certificate $Cert `
    -TimestampServer "http://timestamp.digicert.com" -HashAlgorithm sha256
if ($sig.Status -ne "Valid") {
    Write-Error "Signing failed: $($sig.StatusMessage)"
    exit 1
}

# ── 4. Add cert to Root store (required for Set-AuthenticodeSignature) ────────
$store = New-Object System.Security.Cryptography.X509Certificates.X509Store("Root","LocalMachine")
$store.Open("ReadWrite")
$store.Add($Cert)
$store.Close()
Write-Host "Certificate added to Root store."

# ── 5. Export public cert for shipping with installer ─────────────────────────
Write-Host "Exporting certificate..."
Export-Certificate -Cert $Cert -FilePath $CerPath -Force | Out-Null

Write-Host ""
Write-Host "Done. Commit these files to git:"
Write-Host "  $CatPath"
Write-Host "  $CerPath"
