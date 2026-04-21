# 1. Build the project
cmake --build build
if ($LASTEXITCODE -ne 0) { Write-Error "Build failed"; exit }

# 2. Run the simulation
Write-Host "Running Simulation..." -ForegroundColor Cyan
.\build\Debug\SimulationApp.exe

# 3. Run the visualization (No need to manually activate/deactivate)
Write-Host "Starting Visualization..." -ForegroundColor Green
& ".\.venv\Scripts\python.exe" animate.py