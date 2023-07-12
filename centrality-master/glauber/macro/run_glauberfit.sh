#!/bin/bash

k=(${SLURM_ARRAY_TASK_ID}*$kStep)+$kMin-1
export OutFileIDName=k${k}

filenum=${SLURM_ARRAY_TASK_ID}
jobDir=${log_dir}/${OutFileIDName}

mkdir -p ${jobDir}
cd ${jobDir}
echo "current dir:" $PWD

elapsed=$SECONDS

seed=$(perl -e 'print int rand 99999999, "\n";')
echo seed: ${seed}

source $root_config
rsync -v $CentralityFramework ${jobDir}

sed -i -- "s~gRandom->SetSeed(0);~gRandom->SetSeed(${seed});~g" ${jobDir}/centrality/glauber/main.cpp
sed -i -- "s~fitter.SetMultiplicityStep (0);~fitter.SetMultiplicityStep ($MultiplicityStep);~g"
sed -i -- "s~fitter.SetMinMultiplicity (0);~fitter.SetMinMultiplicity ($MinMultiplicity);~g"
sed -i -- "s~fitter.SetMaxMultiplicity (0);~fitter.SetMaxMultiplicity ($MaxMultiplicity);~g"
sed -i -- "s~fitter.SetMinFitRange (0);~fitter.SetMinFitRange ($MinFitRange);~g"
sed -i -- "s~fitter.Set_kMin (0.0);~fitter.Set_kMin ($k);~g"
sed -i -- "s~fitter.Set_kMax (0.0);~fitter.Set_kMax ($k);~g"
sed -i -- "s~fitter.Set_kStep (0.0);~fitter.Set_kStep (0.0);~g"
sed -i -- "s~fitter.Set_fMin (0.0);~fitter.Set_fMin ($fMin);~g"
sed -i -- "s~fitter.Set_fMax (0.0);~fitter.Set_fMax ($fMax);~g"
sed -i -- "s~fitter.Set_fStep (0.0);~fitter.Set_fStep ($fStep);~g"
sed -i -- "s~fitter.SetGlauber_filename ("");~fitter.SetGlauber_filename ("$Glauber_filename");~g"
sed -i -- "s~fitter.SetGlauber_treename ("");~fitter.SetGlauber_treename ("$Glauber_treename");~g"
sed -i -- "s~fitter.SetDataHisto_filename ("");~fitter.SetDataHisto_filename ("$DataHisto_filename");~g"
sed -i -- "s~fitter.SetDataHisto_name ("");~fitter.SetDataHisto_name ("$DataHisto_name");~g"
sed -i -- "s~fitter.SetOutDirName ("");~fitter.SetOutDirName ("$OutDirName");~g"
sed -i -- "s~fitter.SetOutFileIDName ("");~fitter.SetOutFileIDName ("_$OutFileIDName");~g"
sed -i -- "s~fitter.SetAncestor_Mode ("");~fitter.SetAncestor_Mode ("$Ancestor_Mode");~g"
sed -i -- "s~fitter.SetFitFunction_Mode ("");~fitter.SetFitFunction_Mode ("$FitFunction_Mode");~g"
sed -i -- "s~fitter.SetFit_Mode ("");~fitter.SetFit_Mode ("$Fit_Mode");~g"
sed -i -- "s~fitter.SetnMuIter (0);~fitter.SetnMuIter ($nMuIter);~g"
sed -i -- "s~fitter.SetMassNumber (0);~fitter.SetMassNumber ($MassNumber);~g"
sed -i -- "s~fitter.SetNEvents (0);~fitter.SetNEvents ($NEvents);~g"

cd centrality/build
make
./glauber &>$OutDirName/log_${OutFileIDName}.txt

cd ${jobDir}
rm -rf centrality

[ $remove_logs == 1 ] && rm -rf $log_dir/$filenum

elapsed=$(expr $SECONDS - $elapsed)
echo "Done!"
echo Elapsed time: $(expr $elapsed / 60) minutes

