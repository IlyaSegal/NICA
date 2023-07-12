#!/bin/bash

#
#SBATCH -D /eos/eosnica.jinr.ru/nica/mpd/users/isegal/centrality/
#SBATCH -J mpdcent
#SBATCH -p mephi
#SBATCH --time=1-00:00:00
#SBATCH -a 1-100
#
#SBATCH -o /eos/eosnica.jinr.ru/nica/mpd/users/isegal/centrality/log/%A_%a.o
#SBATCH -e /eos/eosnica.jinr.ru/nica/mpd/users/isegal/centrality/log/%A_%a.e
#

export JOB_ID=$SLURM_ARRAY_JOB_ID
export TASK_ID=$SLURM_ARRAY_TASK_ID

export CentralityFramework=/eos/eosnica.jinr.ru/nica/mpd/users/isegal/soft/CentralityFramework/centrality
export kMin=1
export kMax=100
export kStep=1
export OutDirName=/eos/eosnica.jinr.ru/nica/mpd/users/isegal/centrality/AgAg4.0GeV/dcacut_new
export OutFileIDName=${TASK_ID}
export ConfigName=config_hydra.txt

filenum=${TASK_ID}
jobDir=${OutDirName}/${OutFileIDName}
pdf_dir=${OutDirName}/pdf
qa_dir=${OutDirName}/qa
txt_dir=${OutDirName}/txt
fit_dir=${OutDirName}/fit

mkdir -p "$OutDirName"
mkdir -p ${jobDir}
mkdir -p ${pdf_dir}
mkdir -p ${qa_dir}
mkdir -p ${txt_dir}
mkdir -p ${fit_dir}
cd ${jobDir}
echo "current dir:" $PWD

elapsed=$SECONDS

seed=$(perl -e 'print int rand 99999999, "\n";')
scp $CentralityFramework/glauber/macro/${ConfigName} ${jobDir}
scp $CentralityFramework/build/glauber ${jobDir}
sed -i -- "s~Seed: 0~Seed: ${seed}~g" ${jobDir}/${ConfigName}
sed -i -- "s~kMin: 0.0~kMin: ${TASK_ID}~g" ${jobDir}/${ConfigName}
sed -i -- "s~kMax: 0.0~kMax: ${TASK_ID}~g" ${jobDir}/${ConfigName}
sed -i -- "s~kStep: 0.0~kStep: ${kStep}~g" ${jobDir}/${ConfigName}
sed -i -- "s~OutDirName: ~OutDirName: ${OutDirName}~g" ${jobDir}/${ConfigName}
sed -i -- "s~OutFileIDName: ~OutFileIDName: ${TASK_ID}~g" ${jobDir}/${ConfigName}

./glauber ${ConfigName} &> ${jobDir}/log_${OutFileIDName}.txt

mv ${jobDir}/glauber${TASK_ID}.pdf ${pdf_dir}/glauber${TASK_ID}.pdf
mv ${jobDir}/glauber_qa${TASK_ID}.root ${qa_dir}/glauber_qa${TASK_ID}.root
mv ${jobDir}/log_${TASK_ID}.txt ${txt_dir}/log_${TASK_ID}.txt
mv ${OutDirName}/fit${TASK_ID}.root ${fit_dir}/fit${TASK_ID}.root

remove_logs=1
[ $remove_logs == 1 ] && rm /eos/eosnica.jinr.ru/nica/mpd/users/isegal/centrality/log/${JOB_ID}*
[ $remove_logs == 1 ] && rm -r ${jobDir}

elapsed=$(expr $SECONDS - $elapsed)
echo "Done!"
echo Elapsed time: $(expr $elapsed / 60) minutes

