~/gem5/gem5 ~/gem5/orgb_configs/simulate.py run-benchmark -c ./Compiled/${1,};
grep -E "ipc|sim_seconds|sims_inst|numCycles|overall_miss_rate::total|branchPred.cond|(op_class_0::.* [1-9][0-9]* )" ./m5out/stats.txt;
grep -E "ipc|sim_seconds|sims_inst|numCycles|overall_miss_rate::total|branchPred.cond|(op_class_0::.* [1-9][0-9]* )" ./m5out/stats.txt > ${1}stats.txt

