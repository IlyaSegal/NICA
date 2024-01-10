#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Fitter.h"
#include "FitterHelper.h"

#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TLegend.h"
#include "TRandom.h"
#include "TH2.h"

#include <map>

using namespace Glauber;

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        std::cout << "Wrong number of parameters! Executable usage:" << std::endl;
        std::cout << "   ./glauber config.txt" << std::endl;
        return -1;
    }

    std::string str;
    std::string filename = std::string(argv[1]);
    std::ifstream configfile(filename.c_str());
    if (!configfile.is_open())
    {
        std::cerr << "Config file was not opened correctly!" << std::endl;
        return -2;
    }
    std::cout << "Config file: " << filename << std::endl;

    Fitter fitter;
    Int_t seed;
    Int_t EstimatorStepX, EstimatorStepY;
    Int_t MinEstimatorX, MinEstimatorY;
    Int_t MaxEstimatorX, MaxEstimatorY;
    Int_t MinFitRangeX, MinFitRangeY;
    Float_t kMin;
    Float_t kMax;
    Float_t kStep;
    Float_t fMin;
    Float_t fMax;
    Float_t fStep;
    TString Glauber_filename;
    TString Glauber_treename;
    TString DataHisto_filename;
    TString DataHisto_name;
    TString AtotSampleHisto_filename;
    TString AtotSampleHisto_name;
    TString OutDirName;
    TString OutFileIDName;
    TString Ancestor_Mode;
    TString Mode;
    TString HistoMode;
    TString Fit_Mode;
    Int_t nMuIter;
    Float_t AProj, ATarg, ZProj, ZTarg, EBeam;
    Int_t NEvents;

    configfile >> str >> seed;
    gRandom->SetSeed(seed);
    configfile >> str >> EstimatorStepX;
    fitter.SetEstimatorStepX (EstimatorStepX);
    configfile >> str >> MinEstimatorX;
    fitter.SetMinEstimatorX (MinEstimatorX);
    configfile >> str >> MaxEstimatorX;
    fitter.SetMaxEstimatorX (MaxEstimatorX);
    configfile >> str >> MinFitRangeX;
    fitter.SetMinFitRangeX (MinFitRangeX);
    configfile >> str >> EstimatorStepY;
    fitter.SetEstimatorStepY (EstimatorStepY);
    configfile >> str >> MinEstimatorY;
    fitter.SetMinEstimatorY (MinEstimatorY);
    configfile >> str >> MaxEstimatorY;
    fitter.SetMaxEstimatorY (MaxEstimatorY);
    configfile >> str >> MinFitRangeY;
    fitter.SetMinFitRangeY (MinFitRangeY);
    configfile >> str >> kMin;
    fitter.Set_kMin (kMin);
    configfile >> str >> kMax;
    fitter.Set_kMax (kMax);
    configfile >> str >> kStep;
    fitter.Set_kStep (kStep);
    configfile >> str >> fMin;
    fitter.Set_fMin (fMin);
    configfile >> str >> fMax;
    fitter.Set_fMax (fMax);
    configfile >> str >> fStep;
    fitter.Set_fStep (fStep);
    configfile >> str >> Glauber_filename;
    fitter.SetGlauber_filename (Glauber_filename);
    configfile >> str >> Glauber_treename;
    fitter.SetGlauber_treename (Glauber_treename);
    configfile >> str >> DataHisto_filename;
    fitter.SetDataHisto_filename (DataHisto_filename);
    configfile >> str >> DataHisto_name;
    fitter.SetDataHisto_name (DataHisto_name);
//    configfile >> str >> AtotSampleHisto_filename;
//    fitter.SetAtotSampleHisto_filename (AtotSampleHisto_filename);
//    configfile >> str >> AtotSampleHisto_name;
//    fitter.SetAtotSampleHisto_name (AtotSampleHisto_name);
    configfile >> str >> OutDirName;
    fitter.SetOutDirName (OutDirName);
    configfile >> str >> OutFileIDName;
    fitter.SetOutFileIDName (OutFileIDName);
    configfile >> str >> Ancestor_Mode;
    fitter.SetAncestor_Mode (Ancestor_Mode);
    configfile >> str >> Mode;
    fitter.SetMode (Mode);
    configfile >> str >> HistoMode;
    fitter.SetHistoMode (HistoMode);
    configfile >> str >> Fit_Mode;
    fitter.SetFit_Mode (Fit_Mode);
    configfile >> str >> nMuIter;
    fitter.SetnMuIter (nMuIter);
    configfile >> str >> AProj;
    fitter.SetAProj (AProj);
    configfile >> str >> ZProj;
    fitter.SetZProj (ZProj);
    configfile >> str >> ATarg;
    fitter.SetATarg (ATarg);
    configfile >> str >> ZTarg;
    fitter.SetZTarg (ZTarg);
    configfile >> str >> EBeam;
    fitter.SetEBeam (EBeam);
    configfile >> str >> NEvents;
    fitter.SetNEvents (NEvents);

    std::cout << "Fitting mode: " << fitter.GetMode() << std::endl;
    std::cout << "Fitting function: " << fitter.GetFit_Mode() << std::endl;
    std::cout << "fmax=" << fitter.Get_fMax() << std::endl;
    std::cout << "fmin=" << fitter.Get_fMin() << std::endl;
    std::cout << "f_step=" << fitter.Get_fStep() << std::endl;
    std::cout << "kmin=" << fitter.Get_kMin() << std::endl;
    std::cout << "kmax=" << fitter.Get_kMax() << std::endl;
    std::cout << "k_step=" << fitter.Get_kStep() << std::endl;
    std::cout << "min_binX=" << fitter.GetMinEstimatorX() << std::endl;
    std::cout << "max_binX=" << fitter.GetMaxEstimatorX() << std::endl;
    std::cout << "bin_stepX=" << fitter.GetEstimatorStepX() << std::endl;
    if (fitter.GetHistoMode() == "2D") {
        std::cout << "min_binY=" << fitter.GetMinEstimatorY() << std::endl;
        std::cout << "max_binY=" << fitter.GetMaxEstimatorY() << std::endl;
        std::cout << "bin_stepY=" << fitter.GetEstimatorStepY() << std::endl;
    }

    std::unique_ptr<TFile> glauber_file{ TFile::Open(fitter.GetGlauber_filename(), "read") };
    std::unique_ptr<TTree> glauber_tree{ (TTree*) glauber_file->Get(fitter.GetGlauber_treename()) };
    std::unique_ptr<TFile> f{TFile::Open(fitter.GetDataHisto_filename())};
    std::unique_ptr<TFile> fAtot{TFile::Open(fitter.GetAtotSampleHisto_filename())};

    if (fitter.GetHistoMode() == "1D") {
        TH1F *hdata = (TH1F*)f->Get(fitter.GetDataHisto_name());
        fitter.SetInputHisto(*hdata);
    }
    else if (fitter.GetHistoMode() == "2D") {
        TH2F *hdata = (TH2F*)f->Get(fitter.GetDataHisto_name());
        fitter.SetInputHisto2D(*hdata);
    }
    else {
        std::cout << "ERROR: Invalid histo mode" << std::endl;
        return 0;
    }

    if (fitter.GetAncestor_Mode() == "AtotHisto" || fitter.GetAncestor_Mode() == "AtotProjHisto" || fitter.GetAncestor_Mode() == "AtotTargHisto") {
        if (!fAtot || fitter.GetAtotSampleHisto_name() == "") {
            std::cout << "ERROR: AtotSampleHisto is not provided" << std::endl;
            return 0;
        }
        else {
            TH2F *hAtotSampleHisto = (TH2F*)fAtot->Get(fitter.GetAtotSampleHisto_name());
            fitter.SetAtotSampleHisto(*hAtotSampleHisto);
        }
    }    

    fitter.Init(std::move(glauber_tree));

    float par[4];
	
    float chi2=1e10;
    chi2 = fitter.FitGlauber(par);
    
    std::cout << "f = " << par[0] << "    mu = " << par[1] << "    k = " << par[2] << "    chi2 = " << chi2 << "+-" << par[3] << std::endl;

    DrawHistos(fitter, par, chi2, true, true, true, true);
    
    std::cout << "END!" << std::endl;

    return 0;
}
