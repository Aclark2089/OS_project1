cd /mnt/projects/project1/
mkdir -p ./logs/
cd /mnt/projects/project1/scripts/
# /bin/sh patch_copy.sh > ../logs/log_patch_copy.txt 2>&1
/bin/sh patch_copy.sh 2>&1 | tee ../logs/log_patch_copy.txt 
# /bin/sh rebuild_libraries.sh > ../logs/log_rebuild_libraries.txt 2>&1
/bin/sh rebuild_libraries.sh 2>&1 | tee ../logs/log_rebuild_libraries.txt 
# /bin/sh kernel_recompile.sh > ../logs/log_kernel_recompile.txt 2>&1
/bin/sh kernel_recompile.sh 2>&1 | tee ../logs/log_kernel_recompile.txt