# Centrality Framework

The purpose of the Centrality Framework is to fit distributions of the multiplicity of produced particles and the energy of spectators using output of the MC-Glauber model.
Also it is possible to define centrality classes and to reconstruct initial geometry parameters using this package.
This package allows you to fit 1D and 2D histograms using various methods for multiplicity and spectators energy (see below).

## Installation

    cd centrality-master
    mkdir build
    cd build
    source /path-to-root/thisroot.sh
    cmake ../
    make


## Examples and short description

To run fit of the histogram use:

    ./glauber config.txt
  
The template of the config.txt file can be found in the centrality-master directory.

Description of the config file fields can be found below:

Seed: seed for the gRandom
EstimatorStepX: step of the bins for Chi2 calculation for the X dimension
MinEstimatorX: minimum bin for Chi2 calculation for the X dimension
MaxEstimatorX: maximum bin for Chi2 calculation for the X dimension
MinFitRangeX: minimum possible range for Chi2 calculation for the X dimension (usually use MaxEstimatorX-MinEstimatorX)
EstimatorStepY: step of the bins for Chi2 calculation for the Y dimension
MinEstimatorY: minimum bin for Chi2 calculation for the Y dimension
MaxEstimatorY: maximum bin for Chi2 calculation for the Y dimension
MinFitRangeY: minimum possible range for Chi2 calculation for the Y dimension (usually use MaxEstimatorY-MinEstimatorY)
kMin: minimum k parameter
kMax: maximum k parameter
kStep: step for k parameter
fMin: minimum f parameter
fMax: maximum f parameter
fStep: step for f parameter
Glauber_filename: name of the file with output from MC-Glauber model
Glauber_treename: name of the tree in the file with output from MC-Glauber model
DataHisto_filename: name of the file with histograme from data
DataHisto_name: name of the histograme from data
OutDirName: name of the derictory for the output file
OutFileIDName: suffix for the output files
Ancestor_Mode: mode for the calculations of the number of ancestors
Mode: mode for the building of the model histogram (Multiplicity, Energy etc.)
HistoMode: 1D/2D histogram
Fit_Mode: GoldenSection/Iteration mode for the mu parameter searching
nMuIter: number of iterations for the mu parameter searching
AProj: mass of the projectile nuclei
ZProj: charge of the projectile nuclei
ATarg: mass of the target nuclei
ZTarg: charge of the target nuclei
EBeam: energy of the beam
NEvents: number of MC-Glauber events using for fitting

### Centrality classes determination

After fitting the data histogram it is possible to determine centrality classes using HistoCut.C macro and reconstruct initial geometry parameters in these classes usind CentralityClasses.C macro.

### Doxygen documentation

    doxygen Doxyfile

File Doxygen/html/index.html with documentation will be created
