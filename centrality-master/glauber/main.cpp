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
#include "TH2.h"
#include "TStopwatch.h"

using namespace Glauber;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Wrong number of parameters! Executable usage:" << std::endl;
        std::cout << "   ./glauber configfile" << std::endl;
        return -1;
    }

		Float_t f0, f1, f_step;
    Int_t   k0, k1, n_iter, k_step;
    Int_t   min_bin, max_bin;
    std::string input_glauber_file;
    std::string input_glauber_treename;
    std::string input_refmult_file;
    std::string input_refmult_histname;
    std::vector<std::string> str_name;
    std::string str;

    std::string filename = std::string(argv[1]);
    std::ifstream configfile(filename.c_str());
    if (!configfile.is_open())
    {
				std::cerr << "Config file was not opened correctly!" << std::endl;
        return -2;
    }

    std::cout << "Config file: " << filename << std::endl;

    configfile >> str >> input_glauber_file;
    str_name.push_back(str);
    configfile >> str >> input_glauber_treename;
    str_name.push_back(str);
    configfile >> str >> input_refmult_file;
    str_name.push_back(str);
    configfile >> str >> input_refmult_histname;
    str_name.push_back(str);
		configfile >> str >> n_iter;
    str_name.push_back(str);
		configfile >> str >> f0;
    str_name.push_back(str);
		configfile >> str >> f1;
    str_name.push_back(str);
		configfile >> str >> f_step;
    str_name.push_back(str);
		configfile >> str >> k0;
    str_name.push_back(str);
		configfile >> str >> k1;
    str_name.push_back(str);
		configfile >> str >> k_step;
    str_name.push_back(str);
		configfile >> str >> min_bin;
    str_name.push_back(str);
		configfile >> str >> max_bin;
    str_name.push_back(str);

    configfile.close();

    std::cout << std::endl;
		std::cout << "Input parameters from config:" << std::endl;
    int i_param=0;
    std::cout << str_name.at(i_param++) << " " << input_glauber_file << std::endl;
    std::cout << str_name.at(i_param++) << " " << input_glauber_treename << std::endl;
    std::cout << str_name.at(i_param++) << " " << input_refmult_file << std::endl;
    std::cout << str_name.at(i_param++) << " " << input_refmult_histname << std::endl;
    std::cout << str_name.at(i_param++) << " " << n_iter << std::endl;
    std::cout << str_name.at(i_param++) << " " << f0 << std::endl;
    std::cout << str_name.at(i_param++) << " " << f1 << std::endl;
    std::cout << str_name.at(i_param++) << " " << f_step << std::endl;
    std::cout << str_name.at(i_param++) << " " << k0 << std::endl;
    std::cout << str_name.at(i_param++) << " " << k1 << std::endl;
    std::cout << str_name.at(i_param++) << " " << k_step << std::endl;
    std::cout << str_name.at(i_param++) << " " << min_bin << std::endl;
    std::cout << str_name.at(i_param++) << " " << max_bin << std::endl;
    std::cout << std::endl;

    str_name.clear();

    // const Float_t f0 = atof( argv[1]);
    // std::cout << "f=" << f0 << std::endl;
    // const Float_t f1 = atof( argv[2]);
    // std::cout << "f=" << f1 << std::endl;
    // const Int_t k0 = atoi( argv[3] );
    // std::cout << "k0=" << k0 << std::endl;
    // const Int_t k1 = atoi( argv[4] );
    // std::cout << "k1=" << k1 << std::endl;

	  TStopwatch timer;
    timer.Start();
    
    // *****************************************
    // Modify this part according to your needs
    // *****************************************

    ///  |   mode    |   function for Na      |
    ///  |  Default  | f*Npart + (1-f)*Ncoll  |
    ///  |    PSD    |       f-Npart          |
    ///  |   Npart   |       Npart^f          |
    ///  |   Ncoll   |       Ncoll^f          |
    const TString mode = "Default";
    

    const TString glauber_filename    = TString(input_glauber_file.c_str());   // path to file with glauber tree
    TString glauber_treename    = TString(input_glauber_treename.c_str());     // name of glauber tree
    const TString in_filename =   TString(input_refmult_file.c_str());         // path to file with data histo
    const TString histoname = TString(input_refmult_histname.c_str());         // name of data histo

    // const Int_t min_bin = 50;      // not fitting low multiplicity region due to trigger bias, etc
    // const Int_t max_bin = 430;     // very large number to fit the whole histo

    //std::cout << "min_bin=" << min_bin << "   max_bin=" << max_bin << std::endl;

    const TString outdir = ".";
    // *****************************************
    // *****************************************

    std::unique_ptr<TFile> glauber_file{ TFile::Open(glauber_filename, "read") };
    std::unique_ptr<TTree> glauber_tree{ (TTree*) glauber_file->Get(glauber_treename) };
    
    std::unique_ptr<TFile> f{TFile::Open(in_filename)};    
    TH1F *hdata = (TH1F*)f->Get(histoname);
    const Int_t nevents = 10*(int(hdata->Integral(min_bin,max_bin)));
//    const Int_t nevents = 999999;

    Fitter fitter ( std::move(glauber_tree));

    fitter.SetMode(mode);
    fitter.SetMassNumber(f0/2);
    fitter.SetInputHisto(*hdata);
    fitter.SetBinSize(1);
    fitter.Init(nevents, mode);
    
    fitter.SetFitMinBin(min_bin);
    fitter.SetFitMaxBin(max_bin);
    fitter.SetOutDirName(outdir);
    fitter.SetNiter(n_iter);
    fitter.SetFstepSize(f_step);
    fitter.SetKstepSize(k_step);

    float par[4];
//    const float chi2 = fitter.FitGlauber(par, f0, f1, k0, k1, nevents);
	
    float chi2=1e10;
    chi2 = fitter.FitGlauber(par, f0, f1, k0, k1, nevents);

    std::cout << "f = " << par[0] << "    mu = " << par[1] << "    k = " << par[2] << "    chi2 = " << chi2 << "    chi2_error = " << par[3] << std::endl; 
    
//    Glauber::DrawHistos(fitter, true, true, true, true);

    DrawHistos(fitter, par, chi2, true, true, true, true);

    const float range[2] = {300, 350.};
    std::unique_ptr<TH1F> hB(fitter.GetModelHisto (range, "B", par, 100000));
    hB->SaveAs( "b_test.root" );
    
    std::cout << "END!" << std::endl;

    timer.Stop();
    timer.Print();

    return 0;
}
