# 1. Build the project
cmake --build build
if ($LASTEXITCODE -ne 0) { Write-Error "Build failed"; exit }

# 2. Run the simulation
Write-Host "Running Unit Tests..." -ForegroundColor Cyan
.\build\Debug\SimulationTests.exe