echo "Render started at $(date +"%I:%M:%S")"
./Build/RayTracer && xdg-open Images/
echo "Render finished at $(date +"%I:%M:%S")"
