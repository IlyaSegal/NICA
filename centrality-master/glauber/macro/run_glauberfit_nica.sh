#!/bin/bash

#
#$ -wd /scratch1/isegal/centrality/AuAu9.2GeV/log
#$ -cwd
#$ -N mpdcent
#$ -q all.q
#$ -l h_rt=8:00:00
#$ -l s_rt=8:00:00
#$ -t 1
#
#$ -o /scratch1/isegal/centrality/AuAu9.2GeV/log
#$ -e /scratch1/isegal/centrality/AuAu9.2GeV/log
#

export JOB_ID=$JOB_ID
export TASK_ID=$SGE_TASK_ID

export CentralityFramework=/eos/nica/mpd/users/isegal/soft/CentralityFramework/centrality
export kMin=1.0
export kMax=1.0
export kStep=1.0
export OutDirName=/scratch1/isegal/centrality/AuAu9.2GeV/kMin${kMin}_kMax${kMax}_kStep${kStep}
export OutFileIDName=${TASK_ID}
export ConfigName=config_nica.txt

filenum=${TASK_ID}
jobDir=${OutDirName}/${OutFileIDName}

mkdir -p "$OutDirName"
mkdir -p ${jobDir}
cd ${jobDir}
echo "current dir:" $PWD

elapsed=$SECONDS

seed=$(perl -e 'print int rand 99999999, "\n";')
scp $CentralityFramework/glauber/macro/${ConfigName} ${jobDir}
sed -i -- "s~Seed: 0~Seed: ${seed}~g" ${jobDir}/${ConfigName}
sed -i -- "s~OutDirName: ""~OutDirName: "/scratch1/isegal/centrality/AuAu9.2GeV/kMin${kMin}_kMax${kMax}_kStep${kStep}"~g" ${jobDir}/${ConfigName}
sed -i -- "s~OutFileIDName: ""~OutFileIDName: "${TASK_ID}"~g" ${jobDir}/${ConfigName}

./${CentralityFramework}/build/glauber ${jobDir}/${ConfigName} &> $OutDirName/log_${OutFileIDName}.txt

remove_logs=0
[ $remove_logs == 1 ] && rm /scratch1/isegal/centrality/AuAu9.2GeV/log/*${JOB_ID}*

elapsed=$(expr $SECONDS - $elapsed)
echo "Done!"
echo Elapsed time: $(expr $elapsed / 60) minutes

