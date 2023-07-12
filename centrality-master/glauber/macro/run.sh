#!/bin/bash

export MultiplicityStep=1
export MinMultiplicity=380
export MaxMultiplicity=500
export MinFitRange=120
export kMin=1.0
export kMax=100.0
export kStep=10.0
export fMin=0.0
export fMax=1.0
export fStep=0.1
export Glauber_filename=/home/isegal/glauber/glauber_AuAu_12AGeV.root
export Glauber_treename=nt_Au_Au
export DataHisto_filename=/home/isegal/CBM/qa/qa_REC020.root
export DataHisto_name=reco_info/hMreco
export OutDirName=/eos/eosnica.jinr.ru/nica/mpd/users/isegal/centrality/AuAu9.2GeV/
export Ancestor_Mode=Default
export FitFunction_Mode=NBD
export Fit_Mode=GoldenSection
export nMuIter=10
export MassNumber=197
export NEvents=99999

partition=cpu
time=1-00:00:00

export remove_logs=0 #"yes"

export root_config=/eos/eosnica.jinr.ru/nica/mpd/users/isegal/soft/root_v6-22-04/bin/thisroot.sh
export CentralityFramework=/eos/eosnica.jinr.ru/nica/mpd/users/isegal/soft/CentralityFramework/centrality
source_dir=$OutDirName/src
log_dir=$OutDirName/log

mkdir -p "$OutDirName"
mkdir -p $source_dir
mkdir -p $log_dir

script_path=$(dirname ${0})
run_glauberfit=${script_path}/run_glauberfit.sh
rsync -vp $0 $source_dir
rsync -vp ${run_glauberfit} $source_dir
run_glauberfit=${source_dir}/$(basename ${run_glauberfit})

currentDir=`pwd`
echo "current dir:" $currentDir

jobMax=($kMax-$kMin+1)/$kStep
export jobRange=1-$jobMax

sbatch -J mpdcent -p $partition -t $time -a $jobRange -o ${log_dir}/%a_%A.log -D $OutDirName -- ${run_glauberfit}

echo "========================================================"
echo "Output will be written to: $OutDirName"
echo ""
echo "source code: $source_dir"
echo "Temporary dir (do not forget to clean up after the jobs are finished) $log_dir"
echo ""
echo "data QA files: $DataHisto_filename"
echo "glauber files: $Glauber_filename"
echo "========================================================"


