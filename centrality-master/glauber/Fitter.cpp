#include "Fitter.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TMath.h"
#include "TRandom.h"
#include <map>

ClassImp(Glauber::Fitter)

void Glauber::Fitter::Init(std::unique_ptr<TTree> tree)
{

    mean_fit_proj = new TF1("mean_fit_proj", "[0]+[1]*TMath::Power(x,[2])", 0, fAProj+10);
    sigma_max_fit_proj = new TF1("sigma_max_fit_proj", "[0]+[1]*TMath::Power(x,[2])", 0, fAProj+10);
    mean_fit_targ = new TF1("mean_fit_targ", "[0]+[1]*TMath::Power(x,[2])", 0, fATarg+10);
    sigma_max_fit_targ = new TF1("sigma_max_fit_targ", "[0]+[1]*TMath::Power(x,[2])", 0, fATarg+10);
    //      NA61/SHINE Pb-Pb @ 13GeV/c 
    mean_fit_proj->SetParameters(-1.37869e+02,1.09759e+02,2.14734e-01);
    sigma_max_fit_proj->SetParameters(-4.34575e+01,2.64658e+01,4.21169e-01);
    mean_fit_targ->SetParameters(-1.05371e+02,8.01685e+01,2.57008e-01);
    sigma_max_fit_targ->SetParameters(-4.34575e+01,2.64658e+01,4.21169e-01);
        
    /*//      BM@N Xe-CsI @ 3.85GeV 
    mean_fit_proj->SetParameters(-6.66346e+01,5.17635e+01,2.77331e-01);
    sigma_max_fit_proj->SetParameters(-3.18237e+01,1.96394e+01,4.30432e-01);
    mean_fit_targ->SetParameters(-6.66346e+01,5.17635e+01,2.77331e-01);
    sigma_max_fit_targ->SetParameters(-3.18237e+01,1.96394e+01,4.30432e-01);
    */

    fSimTree = std::move(tree);
    
    if (!fSimTree) 
    {
        std::cout << "SetSimHistos: *** Error - " << std::endl;
        exit(EXIT_FAILURE);
    }
    
    auto it0=Glauber_Parameters.begin();
    for (int i=0; i<kGP; i++) 
    {
    	fSimTree->SetBranchAddress(it0->first,  &(it0->second)); 
	    it0++;
    }

    if ( fnEvents < 0 || fnEvents > fSimTree->GetEntries() )
    {
        std::cout << "Init: *** ERROR - number of entries < 0 or more than number of entries in input tree" << std::endl;
        std::cout << "Init: *** number of entries in input tree = " << fSimTree->GetEntries() << std::endl;        
        exit(EXIT_FAILURE);
    }

    it0=Glauber_Parameters.begin();
    for (int i=0; i<kGP; i++) 
    {
	    Glauber_ParametersMax.insert( std::pair<TString, const int> ((it0->first), int (fSimTree->GetMaximum(it0->first) + 1)) );
        Glauber_ParametersMin.insert( std::pair<TString, const int> ((it0->first), int (fSimTree->GetMinimum(it0->first))) );
	    it0++;
    }
    
    it0=Glauber_Parameters.begin();
    auto it1=Glauber_ParametersMin.begin();
    auto it2=Glauber_ParametersMax.begin();
    for (int j=0; j<kGP; j++) 
    {
    	for (const auto & gGlauberParameter : gGlauberParameters) if (gGlauberParameter.name == it2->first) Glauber_Parameters_Histos.insert( std::pair<TString, TH1F*> ((it2->first), new TH1F (Form("%s_Histo", (gGlauberParameter.name).Data()), Form("%s;%s;counts", (gGlauberParameter.title).Data(), (gGlauberParameter.axis_title).Data()), 1.3*((it2->second)-(it1->second))/gGlauberParameter.bin_value, 1.3*it1->second, 1.3*it2->second)) );
    	it1++;
	    it2++;
    }

    it0=Glauber_Parameters.begin();
    it1=Glauber_ParametersMin.begin();
    it2=Glauber_ParametersMax.begin();		
    auto it3=Glauber_Parameters_Histos.begin();
    for (int i=0; i<fnEvents; i++)
    {
       	fSimTree->GetEntry(i);
	    it0=Glauber_Parameters.begin();
	    it3=Glauber_Parameters_Histos.begin();
	    for (int j=0; j<kGP; j++)
	    {
		    (it3->second)->Fill(it0->second);
		    it0++;
		    it3++;
	    }
    }

    std::cout << "Entries in GlauberTree:" << fSimTree->GetEntries() << std::endl;

    if (fHistoMode == "1D") {
        fNbins[0] = fDataHisto.GetNbinsX();
        while (fDataHisto.GetBinContent(fNbins[0] - 1) == 0) fNbins[0]--;
        fNbins[0]++;
        const float min = fDataHisto.GetXaxis()->GetXmin();
        const float max = fDataHisto.GetXaxis()->GetXmax();
//        fMaxValue[0] = min + (max - min) * fNbins[0] / fDataHisto.GetNbinsX();
        fMaxValue[0] = 280;
        fNbins[0] = 280;

        it0=Glauber_Parameters.begin();
        it1=Glauber_ParametersMin.begin();
        it2=Glauber_ParametersMax.begin();
        it3=Glauber_Parameters_Histos.begin();
        for (int j=0; j<kGP; j++)
        {
            for (const auto & gGlauberParameter : gGlauberParameters) if (gGlauberParameter.name == it2->first) Glauber_Parameters_VS_Estimator_Histos.insert( std::pair<TString, TH2F*> ((it2->first), new TH2F (Form("%s_VS_%s_Histo", (gGlauberParameter.name).Data(), fMode.Data()), Form("%s VS %s;%s;%s", (gGlauberParameter.title).Data(), fMode.Data(), fMode.Data(), (gGlauberParameter.axis_title).Data()), 1.3*fNbins[0], 0, 1.3*fMaxValue[0], 1.3*((it2->second)-(it1->second))/gGlauberParameter.bin_value, 1.3*it1->second, 1.3*it2->second)) );
            it1++;
            it2++;
        }
        it0=Glauber_Parameters.begin();
        it1=Glauber_ParametersMin.begin();
        it2=Glauber_ParametersMax.begin();
        it3=Glauber_Parameters_Histos.begin();
        for (int j=0; j<kGP; j++)
        {
            for (const auto & gGlauberParameter : gGlauberParameters) if (gGlauberParameter.name == it2->first) Glauber_Parameters_VS_Estimator_BestHistos.insert( std::pair<TString, TH2F*> ((it2->first), new TH2F (Form("%s_VS_%s_BestHisto", (gGlauberParameter.name).Data(), fMode.Data()), Form("%s VS %s;%s;%s", (gGlauberParameter.title).Data(), fMode.Data(), fMode.Data(), (gGlauberParameter.axis_title).Data()), 1.3*fNbins[0], 0, 1.3*fMaxValue[0], 1.3*((it2->second)-(it1->second))/gGlauberParameter.bin_value, 1.3*it1->second, 1.3*it2->second)) );
            it1++;
            it2++;
        }
        std::cout << "fNbins = " << fNbins[0] << std::endl;
        std::cout << "fMaxValue = " << fMaxValue[0] << std::endl;
    }
    else if (fHistoMode == "2D") {
        fNbins[0] = fDataHisto2D.GetNbinsX();
        while (fDataHisto2D.GetBinContent(fNbins[0] - 1) == 0) fNbins[0]--;
        fNbins[0]++;
        const float min = fDataHisto2D.GetXaxis()->GetXmin();
        const float max = fDataHisto2D.GetXaxis()->GetXmax();
        fMaxValue[0] = min + (max - min) * fNbins[0] / fDataHisto2D.GetNbinsX();
        fNbins[1] = fDataHisto2D.GetNbinsY();
        fMaxValue[1] = fDataHisto2D.GetYaxis()->GetXmax();
        it0=Glauber_Parameters.begin();
        it1=Glauber_ParametersMin.begin();
        it2=Glauber_ParametersMax.begin();
        it3=Glauber_Parameters_Histos.begin();
        for (int j=0; j<kGP; j++)
        {
            for (const auto & gGlauberParameter : gGlauberParameters) if (gGlauberParameter.name == it2->first) Glauber_Parameters_VS_Estimator_Histos3D.insert( std::pair<TString, TH3F*> ((it2->first), new TH3F (Form("%s_VS_%s_Histo", (gGlauberParameter.name).Data(), fMode.Data()), Form("%s VS %s;%s;<|Y-Y_{beam}|>;Energy", (gGlauberParameter.title).Data(), fMode.Data(), (gGlauberParameter.axis_title).Data()), 1.3*fNbins[0], 0, 1.3*fMaxValue[0], 1.3*fNbins[1], 0, 1.3*fMaxValue[1], 1.3*((it2->second)-(it1->second))/gGlauberParameter.bin_value, 1.3*it1->second, 1.3*it2->second)) );
            it1++;
            it2++;
        }
        it0=Glauber_Parameters.begin();
        it1=Glauber_ParametersMin.begin();
        it2=Glauber_ParametersMax.begin();
        it3=Glauber_Parameters_Histos.begin();
        for (int j=0; j<kGP; j++)
        {
            for (const auto & gGlauberParameter : gGlauberParameters) if (gGlauberParameter.name == it2->first) Glauber_Parameters_VS_Estimator_BestHistos3D.insert( std::pair<TString, TH3F*> ((it2->first), new TH3F (Form("%s_VS_%s_BestHisto", (gGlauberParameter.name).Data(), fMode.Data()), Form("%s VS %s;%s;<|Y-Y_{beam}|>;Energy", (gGlauberParameter.title).Data(), fMode.Data(), (gGlauberParameter.axis_title).Data()), 1.3*fNbins[0], 0, 1.3*fMaxValue[0], 1.3*fNbins[1], 0, 1.3*fMaxValue[1], 1.3*((it2->second)-(it1->second))/gGlauberParameter.bin_value, 1.3*it1->second, 1.3*it2->second)) );
            it1++;
            it2++;
        }
        std::cout << "fNbinsX = " << fNbins[0] << std::endl;
        std::cout << "fMaxValueX = " << fMaxValue[0] << std::endl;
        std::cout << "fNbinsY = " << fNbins[1] << std::endl;
        std::cout << "fMaxValueY = " << fMaxValue[1] << std::endl;
    }
}

float Glauber::Fitter::Nancestors(float f, const TString& Ancestor_Mode) const
{
    if       (Ancestor_Mode == "Default")    return f*Glauber_Parameters.at("Npart") + (1-f)*Glauber_Parameters.at("Ncoll");
    else if  (Ancestor_Mode == "Nspec")      return (fAProj+fATarg)-Glauber_Parameters.at("Npart");
    else if  (Ancestor_Mode == "NspecProj")  return fAProj-Glauber_Parameters.at("NpartA");
    else if  (Ancestor_Mode == "NspecTarg")  return fATarg-Glauber_Parameters.at("NpartB");
    else if  (Ancestor_Mode == "Atot")       return TMath::Power((fAProj+fATarg),1-f)*TMath::Power((fAProj+fATarg)-Glauber_Parameters.at("Npart"),f);
    else if  (Ancestor_Mode == "AtotProj")   return TMath::Power(fAProj,1-f)*TMath::Power(fAProj-Glauber_Parameters.at("NpartA"),f);
    else if  (Ancestor_Mode == "AtotTarg")   return TMath::Power(fATarg,1-f)*TMath::Power(fATarg-Glauber_Parameters.at("NpartB"),f);
    else if  (Ancestor_Mode == "AtotGraph")      
    {
    	auto Atot_proj = -999;
    	auto Atot_targ = -999;
    	auto Nspec_proj = (int) (fAProj-Glauber_Parameters.at("NpartA"));
    	auto Nspec_targ = (int) (fATarg-Glauber_Parameters.at("NpartB"));
    	auto mean = mean_fit_proj->GetX(Nspec_proj, 0, fAProj+10);
//    	auto width = sigma_max_fit_proj->GetX(Nspec_proj, 0, fAProj+10) - mean;
//    	while((Atot_proj<0) || (Atot_proj>fAProj)) Atot_proj = (int) gRandom->Gaus(mean, width);
	Atot_proj = (int) mean;
    	mean = mean_fit_targ->GetX(Nspec_targ, 0, fATarg+10);
//    	width = sigma_max_fit_targ->GetX(Nspec_targ, 0, fATarg+10) - mean;
//    	while((Atot_targ<0) || (Atot_targ>fATarg)) Atot_targ = (int) gRandom->Gaus(mean, width);
	Atot_targ = (int) mean;
    	return Atot_proj + Atot_targ;
    }
    else if  (Ancestor_Mode == "AtotProjGraph")
    {
    	auto Atot = -999;
    	auto Nspec = (int) (fAProj-Glauber_Parameters.at("NpartA"));
    	auto mean = mean_fit_proj->GetX(Nspec, 0, fAProj+10);
//    	auto width = sigma_max_fit_proj->GetX(Nspec, 0, fAProj+10) - mean;
//    	while((Atot<0) || (Atot>fAProj)) Atot = (int) gRandom->Gaus(mean, width);
	Atot = (int) mean;
    	return Atot;
    }
    else if  (Ancestor_Mode == "AtotTargGraph")
    {
    	auto Atot = -999;
    	auto Nspec = (int) (fATarg-Glauber_Parameters.at("NpartB"));
    	auto mean = mean_fit_targ->GetX(Nspec, 0, fATarg+10);
//    	auto width = sigma_max_fit_targ->GetX(Nspec, 0, fATarg+10) - mean;
//    	while((Atot<0) || (Atot>fATarg)) Atot = (int) gRandom->Gaus(mean, width);
    	Atot = (int) mean;
    	return Atot;
    }
    else if  (Ancestor_Mode == "AtotHisto") {
        auto Nspec_proj = (int) (fAProj-Glauber_Parameters.at("NpartA"));
    	auto Nspec_targ = (int) (fATarg-Glauber_Parameters.at("NpartB"));
        auto hAtot = (TH1D*)fAtotSampleHisto.ProjectionX("hAtot", Nspec_proj+Nspec_targ+1, Nspec_proj+Nspec_targ+1); 
        return (int) hAtot->GetRandom();
    }
    else if  (Ancestor_Mode == "AtotProjHisto") {
        auto Nspec = (int) (fAProj-Glauber_Parameters.at("NpartA"));
        auto hAtot = (TH1D*)fAtotSampleHisto.ProjectionX("hAtot", Nspec+1, Nspec+1); 
        return (int) hAtot->GetRandom();
    }   
    else if  (Ancestor_Mode == "AtotTargHisto") {
        auto Nspec = (int) (fATarg-Glauber_Parameters.at("NpartB"));
        auto hAtot = (TH1D*)fAtotSampleHisto.ProjectionX("hAtot", Nspec+1, Nspec+1); 
        return (int) hAtot->GetRandom();
    }       
    else if  (Ancestor_Mode == "Npart")      return TMath::Power(Glauber_Parameters.at("Npart"), f); 
    else if  (Ancestor_Mode == "Ncoll")      return TMath::Power(Glauber_Parameters.at("Ncoll"), f);
    
    return -1.;
}

float Glauber::Fitter::NancestorsMax(float f, const TString& Ancestor_Mode) const
{
    const int NpartMax = fSimTree->GetMaximum("Npart");  // some magic
    const int NcollMax = fSimTree->GetMaximum("Ncoll");
    
    if       (Ancestor_Mode == "Default")    return f*NpartMax + (1-f)*NcollMax;
    else if  (Ancestor_Mode == "Nspec" || Ancestor_Mode == "Atot" || Ancestor_Mode == "AtotGraph" ||Ancestor_Mode == "AtotHisto")      return fAProj + fATarg;
    else if  (Ancestor_Mode == "NspecProj" || Ancestor_Mode == "AtotProj" || Ancestor_Mode == "AtotProjGraph" ||Ancestor_Mode == "AtotProjHisto")  return fAProj;
    else if  (Ancestor_Mode == "NspecTarg" || Ancestor_Mode == "AtotTarg" || Ancestor_Mode == "AtotTargGraph" ||Ancestor_Mode == "AtotTargHisto")  return fATarg;
    else if  (Ancestor_Mode == "Npart")      return TMath::Power(NpartMax, f); 
    else if  (Ancestor_Mode == "Ncoll")      return TMath::Power(NcollMax, f);
    
    return -1.;
}

/*
 * take Glauber MC data from fSimTree
 * Populate fGlauberFitHisto with NBD x Na
 */

void Glauber::Fitter::SetGlauberFitHisto (float f, float mu, float k, Bool_t Norm2Data)
{
    if (fHistoMode == "1D") {
        fGlauberFitHisto = TH1F("glaub", "", fNbins[0] * 1.3, 0, 1.3 * fMaxValue[0]);
        fGlauberFitHisto.SetName("glaub_fit_histo");
        auto it = Glauber_Parameters_VS_Estimator_Histos.begin();
        for (int q = 0; q < kGP; q++) {
            (it->second)->Reset();
            it++;
        }
        if (fMode == "Multiplicity" || fMode == "MultiplicityHADES") SetNBDhist(mu, k);
    }
    else if (fHistoMode == "2D") {
        fGlauberFitHisto2D = TH2F("glaub", "", fNbins[0] * 1.3, 0, 1.3 * fMaxValue[0], fNbins[1] * 1.3, 0, 1.3 * fMaxValue[1]);
        fGlauberFitHisto2D.SetName("glaub_fit_histo");
        auto it = Glauber_Parameters_VS_Estimator_Histos3D.begin();
        for (int q = 0; q < kGP; q++) {
            (it->second)->Reset();
            it++;
        }
    }
    
    if (fMode == "Multiplicity" || fMode == "MultiplicityHADES") SetNBDhist(mu,  k);
    else SetNBDhist(0.34,  88);
    std::unique_ptr<TH1F> htemp {(TH1F*)fSampleHisto.Clone("htemp")};

    TF1* Gamma = new TF1("gamma", Form("TMath::GammaDist(x,1,%f,%f)", mu, k), mu, mu*(fAProj + fATarg)+100);

    for (int i=0; i<fnEvents; i++)
    {
        fSimTree->GetEntry(i);
        const int Na = int(Nancestors(f, fAncestor_Mode));
        if (fMode == "MultiplicityHADES") int Na = int(Nancestors(0, fAncestor_Mode));
        float nEstimatorX {0.};
        float nEstimatorY {0.};

        if (fHistoMode == "1D") {
            if (fMode == "Multiplicity") {
            	for (int j = 0; j < Na; j++) nEstimatorX += int(htemp->GetRandom());
            }
            else if (fMode == "MultiplicityHADES") {
            	for (int j = 0; j < Na; j++) nEstimatorX += int((htemp->GetRandom())*(1-f*Glauber_Parameters.at("Npart")*Glauber_Parameters.at("Npart")));
            }
            else if (fMode == "Energy") {
            	for (int j = 0; j < Na; j++) {
			        float E = -1;
			        while (E < 0) E = gRandom->Gaus(mu, k);
			        nEstimatorX = nEstimatorX + E;
		        }
            }
            else if (fMode == "Energy+Multiplicity") {
            	for (int j = 0; j < Na; j++) {
			        float E = -1;
			        while (E < 0) E = gRandom->Gaus(mu, k);
			        nEstimatorX = nEstimatorX + E;
		        }
                int NaNBD = int(Nancestors(1, "Default"));
                int mult = 0;
                for (int j = 0; j < NaNBD; j++) mult += int(htemp->GetRandom());
                if (mult < 10) mult = int(gRandom->Gaus(1, 1));
                else if (mult >= 10 || mult < 50) mult = int(gRandom->Gaus(3, 1));
                else if (mult >= 50 || mult < 170) mult = int(gRandom->Gaus(6, 2.5));
                else if (mult >= 170) mult = int(gRandom->Gaus(7, 2.5));
                for (int ii = 0; ii < mult; ii++) {
                    float E = -1;
                    while (E < 0) E = gRandom->Landau(0.6, 0.75);
			        nEstimatorX = nEstimatorX + E;
                }
            }
            else if (fMode == "EnergyGamma") {
            	for (int j = 0; j < Na; j++) {
			        float E = -1;
			        while (E < 0) E = Gamma->GetRandom(gRandom);
			        nEstimatorX = nEstimatorX + E;
		        }
            }
            else if (fMode == "EnergyLandau") {
            	for (int j = 0; j < Na; j++) {
			        float E = -1;
			        while (E < 0) E = gRandom->Landau(mu, k);
			        nEstimatorX = nEstimatorX + E;
		        }
            }
            fGlauberFitHisto.Fill(nEstimatorX);
            auto it1 = Glauber_Parameters.begin();
            auto it2 = Glauber_Parameters_VS_Estimator_Histos.begin();
            for (int q = 0; q < kGP; q++) {
                (it2->second)->Fill(nEstimatorX, it1->second);
                it1++;
                it2++;
            }
        }
        else if (fHistoMode == "2D") {
            if (fMode == "MultiplicityVSEnergy") {
                float fE;
                for (int j = 0; j < Na; j++) {
                    fE = gRandom->Gaus(mu, k);
                    nEstimatorX += fE;
                    nEstimatorY += TMath::Abs(gRandom->Gaus(0, 1));
                }
            }
            fGlauberFitHisto2D.Fill(nEstimatorX, nEstimatorY);
            auto it1 = Glauber_Parameters.begin();
            auto it2 = Glauber_Parameters_VS_Estimator_Histos3D.begin();
            for (int q = 0; q < kGP; q++) {
                (it2->second)->Fill(nEstimatorX, nEstimatorY, it1->second);
                it1++;
                it2++;
            }
        }
    }

    if (Norm2Data)
        NormalizeGlauberFit();
}


void Glauber::Fitter::NormalizeGlauberFit ()
{
    
    int fGlauberFitHistoInt {0}; 
    int fDataHistoInt {0};
    float ScaleFactor;
    
    const int lowchibinX = fFitMinBin[0];
    const int highchibinX = fFitMaxBin[0]<fNbins[0] ? fFitMaxBin[0] : fNbins[0];

    if (fHistoMode == "1D") {
        for (int i = lowchibinX; i < highchibinX; i++) {
            fGlauberFitHistoInt += fGlauberFitHisto.GetBinContent(i + 1);
            fDataHistoInt += fDataHisto.GetBinContent(i + 1);
        }
        ScaleFactor = (float) fDataHistoInt / fGlauberFitHistoInt;
        fGlauberFitHisto.Scale(ScaleFactor);
    }
    else if (fHistoMode == "2D") {
        const int lowchibinY = fFitMinBin[1];
        const int highchibinY = fFitMaxBin[1]<fNbins[1] ? fFitMaxBin[1] : fNbins[1];
        for (int i = lowchibinX; i < highchibinX; i++)
            for (int j = lowchibinY; j < highchibinY; j++) {
                fGlauberFitHistoInt += fGlauberFitHisto2D.GetBinContent(i + 1, j + 1);
                fDataHistoInt += fDataHisto2D.GetBinContent(i + 1, j + 1);
            }
        ScaleFactor = (float) fDataHistoInt / fGlauberFitHistoInt;
        fGlauberFitHisto2D.Scale(ScaleFactor);
    }
}

/**
 *
 * @param mu mean value of negative binominal distribution (we are looking for it)
 * @param chi2 return value (indicates good match)
 * @param mu_min lower search edge for mean value NBD
 * @param mu_max upper search edge for mean value NBD
 * @param f parameter of Na
 * @param k NBD parameter
 */
void Glauber::Fitter::FindMuGoldenSection (TTree *tree, float *mu, float *chi2, float*chi2_error, int *n, float *sigma, float mu_min, float mu_max, float f, float k )
{
    double phi {(1+TMath::Sqrt(5))/2};

    /* left */
    float mu_1 = mu_max - (mu_max-mu_min)/phi;

    /* right */
    float mu_2 = mu_min + (mu_max-mu_min)/phi;

    float chi2_mu1, chi2_mu2;
    float chi2_mu1_error, chi2_mu2_error;
    
    SetGlauberFitHisto (f, mu_1, k);
    *sigma = ( (mu_1)/k + 1 ) * (mu_1);
    for (int fRangeX = fMinFitRange[0]; fRangeX <= (fMaxEstimator[0]-fMinEstimator[0]); fRangeX = fRangeX + fEstimatorStep[0])
        for (int fRangeCenterX = 2*fMinEstimator[0]+fRangeX; fRangeCenterX <= (2*fMaxEstimator[0]-fRangeX); fRangeCenterX = fRangeCenterX + 2*fEstimatorStep[0]) {
            fFitMinBin[0] = (fRangeCenterX - fRangeX)/2;
            fFitMaxBin[0] = (fRangeCenterX + fRangeX)/2;
            if (fHistoMode != "2D") {
                fMinFitRange[1] = 0;
                fMaxEstimator[1] = 0;
                fMinEstimator[1] = 0;
                fEstimatorStep[1]= 1;
            }
            for (int fRangeY = fMinFitRange[1]; fRangeY <= (fMaxEstimator[1]-fMinEstimator[1]); fRangeY = fRangeY + fEstimatorStep[1])
                for (int fRangeCenterY = 2*fMinEstimator[1]+fRangeY; fRangeCenterY <= (2*fMaxEstimator[1]-fRangeY); fRangeCenterY = fRangeCenterY + 2*fEstimatorStep[1]) {
                    fFitMinBin[1] = (fRangeCenterY - fRangeY) / 2;
                    fFitMaxBin[1] = (fRangeCenterY + fRangeY) / 2;
                    NormalizeGlauberFit();
                    chi2_mu1 = GetChi2();
                    chi2_mu1_error = GetChi2Error();
                    *mu = mu_1;
                    *chi2 = chi2_mu1;
                    *chi2_error = chi2_mu1_error;
                    tree->Fill();
                    if (fHistoMode == "1D") std::cout << "n = " << (*n) << " f = " << f << " k = " << k << " mu = " << (*mu)
                                            << " FitMinBinX = " << fFitMinBin[0] << " FitMaxBinX = " << fFitMaxBin[0]
                                            << " chi2 = " << (*chi2) << " chi2_error = " << (*chi2_error) << std::endl;
                    else if (fHistoMode == "2D") std::cout << "n = " << (*n) << " f = " << f << " k = " << k << " mu = " << (*mu)
                                            << " FitMinBinX = " << fFitMinBin[0] << " FitMaxBinX = " << fFitMaxBin[0]
                                            << " FitMinBinY = " << fFitMinBin[1] << " FitMaxBinY = " << fFitMaxBin[1]
                                            << " chi2 = " << (*chi2) << " chi2_error = " << (*chi2_error) << std::endl;
                    *n = *n + 1;
                }
        }

    SetGlauberFitHisto (f, mu_2, k);
    *sigma = ( (mu_2)/k + 1 ) * (mu_2);
    for (int fRangeX = fMinFitRange[0]; fRangeX <= (fMaxEstimator[0]-fMinEstimator[0]); fRangeX = fRangeX + fEstimatorStep[0])
        for (int fRangeCenterX = 2*fMinEstimator[0]+fRangeX; fRangeCenterX <= (2*fMaxEstimator[0]-fRangeX); fRangeCenterX = fRangeCenterX + 2*fEstimatorStep[0]) {
            fFitMinBin[0] = (fRangeCenterX - fRangeX)/2;
            fFitMaxBin[0] = (fRangeCenterX + fRangeX)/2;
            if (fHistoMode != "2D") {
                fMinFitRange[1] = 0;
                fMaxEstimator[1] = 0;
                fMinEstimator[1] = 0;
                fEstimatorStep[1]= 1;
            }
            for (int fRangeY = fMinFitRange[1]; fRangeY <= (fMaxEstimator[1]-fMinEstimator[1]); fRangeY = fRangeY + fEstimatorStep[1])
                for (int fRangeCenterY = 2*fMinEstimator[1]+fRangeY; fRangeCenterY <= (2*fMaxEstimator[1]-fRangeY); fRangeCenterY = fRangeCenterY + 2*fEstimatorStep[1]) {
                    fFitMinBin[1] = (fRangeCenterY - fRangeY) / 2;
                    fFitMaxBin[1] = (fRangeCenterY + fRangeY) / 2;
                    NormalizeGlauberFit();
                    chi2_mu2 = GetChi2();
                    chi2_mu2_error = GetChi2Error();
                    *mu = mu_2;
                    *chi2 = chi2_mu2;
                    *chi2_error = chi2_mu2_error;
                    tree->Fill();
                    if (fHistoMode == "1D") std::cout << "n = " << (*n) << " f = " << f << " k = " << k << " mu = " << (*mu)
                                                      << " FitMinBinX = " << fFitMinBin[0] << " FitMaxBinX = " << fFitMaxBin[0]
                                                      << " chi2 = " << (*chi2) << " chi2_error = " << (*chi2_error) << std::endl;
                    else if (fHistoMode == "2D") std::cout << "n = " << (*n) << " f = " << f << " k = " << k << " mu = " << (*mu)
                                                           << " FitMinBinX = " << fFitMinBin[0] << " FitMaxBinX = " << fFitMaxBin[0]
                                                           << " FitMinBinY = " << fFitMinBin[1] << " FitMaxBinY = " << fFitMaxBin[1]
                                                           << " chi2 = " << (*chi2) << " chi2_error = " << (*chi2_error) << std::endl;
                    *n = *n + 1;
                }
        }
    
    for (int j=0; j<fnMuIter; j++)
    {        
        if (chi2_mu1 > chi2_mu2)
        {
            mu_min = mu_1;
            mu_1 = mu_2;
            mu_2 = mu_min + (mu_max-mu_min)/phi;
            chi2_mu1 = chi2_mu2;
            SetGlauberFitHisto (f, mu_2, k);
            *sigma = ( (mu_2)/k + 1 ) * (mu_2);
            for (int fRangeX = fMinFitRange[0]; fRangeX <= (fMaxEstimator[0]-fMinEstimator[0]); fRangeX = fRangeX + fEstimatorStep[0])
                for (int fRangeCenterX = 2*fMinEstimator[0]+fRangeX; fRangeCenterX <= (2*fMaxEstimator[0]-fRangeX); fRangeCenterX = fRangeCenterX + 2*fEstimatorStep[0]) {
                    fFitMinBin[0] = (fRangeCenterX - fRangeX)/2;
                    fFitMaxBin[0] = (fRangeCenterX + fRangeX)/2;
                    if (fHistoMode != "2D") {
                        fMinFitRange[1] = 0;
                        fMaxEstimator[1] = 0;
                        fMinEstimator[1] = 0;
                        fEstimatorStep[1]= 1;
                    }
                    for (int fRangeY = fMinFitRange[1]; fRangeY <= (fMaxEstimator[1]-fMinEstimator[1]); fRangeY = fRangeY + fEstimatorStep[1])
                        for (int fRangeCenterY = 2*fMinEstimator[1]+fRangeY; fRangeCenterY <= (2*fMaxEstimator[1]-fRangeY); fRangeCenterY = fRangeCenterY + 2*fEstimatorStep[1]) {
                            fFitMinBin[1] = (fRangeCenterY - fRangeY) / 2;
                            fFitMaxBin[1] = (fRangeCenterY + fRangeY) / 2;
                            NormalizeGlauberFit();
                            chi2_mu2 = GetChi2();
                            chi2_mu2_error = GetChi2Error();
                            *mu = mu_2;
                            *chi2 = chi2_mu2;
                            *chi2_error = chi2_mu2_error;
                            tree->Fill();
                            if (fHistoMode == "1D") std::cout << "n = " << (*n) << " f = " << f << " k = " << k << " mu = " << (*mu)
                                                              << " FitMinBinX = " << fFitMinBin[0] << " FitMaxBinX = " << fFitMaxBin[0]
                                                              << " chi2 = " << (*chi2) << " chi2_error = " << (*chi2_error) << std::endl;
                            else if (fHistoMode == "2D") std::cout << "n = " << (*n) << " f = " << f << " k = " << k << " mu = " << (*mu)
                                                                   << " FitMinBinX = " << fFitMinBin[0] << " FitMaxBinX = " << fFitMaxBin[0]
                                                                   << " FitMinBinY = " << fFitMinBin[1] << " FitMaxBinY = " << fFitMaxBin[1]
                                                                   << " chi2 = " << (*chi2) << " chi2_error = " << (*chi2_error) << std::endl;
                            *n = *n + 1;
                        }
                }

        }
        else
        {
            mu_max = mu_2;
            mu_2 = mu_1;
            mu_1 = mu_max - (mu_max-mu_min)/phi; 
            chi2_mu2 = chi2_mu1;
            SetGlauberFitHisto (f, mu_1, k);
            *sigma = ( (mu_1)/k + 1 ) * (mu_1);
            for (int fRangeX = fMinFitRange[0]; fRangeX <= (fMaxEstimator[0]-fMinEstimator[0]); fRangeX = fRangeX + fEstimatorStep[0])
                for (int fRangeCenterX = 2*fMinEstimator[0]+fRangeX; fRangeCenterX <= (2*fMaxEstimator[0]-fRangeX); fRangeCenterX = fRangeCenterX + 2*fEstimatorStep[0]) {
                    fFitMinBin[0] = (fRangeCenterX - fRangeX)/2;
                    fFitMaxBin[0] = (fRangeCenterX + fRangeX)/2;
                    if (fHistoMode != "2D") {
                        fMinFitRange[1] = 0;
                        fMaxEstimator[1] = 0;
                        fMinEstimator[1] = 0;
                        fEstimatorStep[1]= 1;
                    }
                    for (int fRangeY = fMinFitRange[1]; fRangeY <= (fMaxEstimator[1]-fMinEstimator[1]); fRangeY = fRangeY + fEstimatorStep[1])
                        for (int fRangeCenterY = 2*fMinEstimator[1]+fRangeY; fRangeCenterY <= (2*fMaxEstimator[1]-fRangeY); fRangeCenterY = fRangeCenterY + 2*fEstimatorStep[1]) {
                            fFitMinBin[1] = (fRangeCenterY - fRangeY)/2;
                            fFitMaxBin[1] = (fRangeCenterY + fRangeY)/2;
                            NormalizeGlauberFit();
                            chi2_mu1 = GetChi2();
                            chi2_mu1_error = GetChi2Error();
                            *mu = mu_1;
                            *chi2 = chi2_mu1;
                            *chi2_error = chi2_mu1_error;
                            tree->Fill();
                            if (fHistoMode == "1D") std::cout << "n = " << (*n) << " f = " << f << " k = " << k << " mu = " << (*mu)
                                                              << " FitMinBinX = " << fFitMinBin[0] << " FitMaxBinX = " << fFitMaxBin[0]
                                                              << " chi2 = " << (*chi2) << " chi2_error = " << (*chi2_error) << std::endl;
                            else if (fHistoMode == "2D") std::cout << "n = " << (*n) << " f = " << f << " k = " << k << " mu = " << (*mu)
                                                                   << " FitMinBinX = " << fFitMinBin[0] << " FitMaxBinX = " << fFitMaxBin[0]
                                                                   << " FitMinBinY = " << fFitMinBin[1] << " FitMaxBinY = " << fFitMaxBin[1]
                                                                   << " chi2 = " << (*chi2) << " chi2_error = " << (*chi2_error) << std::endl;
                            *n = *n + 1;
                        }
                }
        }
    }

    /* take min(mu) */
    *mu = (chi2_mu1 < chi2_mu2) ? mu_1 : mu_2;
    /* take min(chi2) */
    *chi2 = (chi2_mu1 < chi2_mu2) ? chi2_mu1 : chi2_mu2;
    /* take min(chi2_error) */
    *chi2_error = (chi2_mu1 < chi2_mu2) ? chi2_mu1_error : chi2_mu2_error;
}

/**
 *
 * @param mu mean value of negative binominal distribution (we are looking for it)
 * @param chi2 return value (indicates good match)
 * @param mu_min lower search edge for mean value NBD
 * @param mu_max upper search edge for mean value NBD
 * @param f parameter of Na
 * @param k NBD parameter
 */
void Glauber::Fitter::FindMuIteration (TTree *tree, float mu, float *chi2, float *chi2_error, int *n, float *sigma, float f, float k)
{
    float chi2_best=1e10, chi2_error_best=1e10;
    SetGlauberFitHisto (f, mu, k);
    *sigma = ( mu/k + 1 ) * mu;
    for (int fRangeX = fMinFitRange[0]; fRangeX <= (fMaxEstimator[0]-fMinEstimator[0]); fRangeX = fRangeX + fEstimatorStep[0])
        for (int fRangeCenterX = 2*fMinEstimator[0]+fRangeX; fRangeCenterX <= (2*fMaxEstimator[0]-fRangeX); fRangeCenterX = fRangeCenterX + 2*fEstimatorStep[0]) {
            fFitMinBin[0] = (fRangeCenterX - fRangeX)/2;
            fFitMaxBin[0] = (fRangeCenterX + fRangeX)/2;
            if (fHistoMode != "2D") {
                fMinFitRange[1] = 0;
                fMaxEstimator[1] = 0;
                fMinEstimator[1] = 0;
                fEstimatorStep[1]= 1;
            }
            for (int fRangeY = fMinFitRange[1]; fRangeY <= (fMaxEstimator[1]-fMinEstimator[1]); fRangeY = fRangeY + fEstimatorStep[1])
                for (int fRangeCenterY = 2*fMinEstimator[1]+fRangeY; fRangeCenterY <= (2*fMaxEstimator[1]-fRangeY); fRangeCenterY = fRangeCenterY + 2*fEstimatorStep[1]) {
                    fFitMinBin[1] = (fRangeCenterY - fRangeY) / 2;
                    fFitMaxBin[1] = (fRangeCenterY + fRangeY) / 2;
                    NormalizeGlauberFit();
                    *chi2 = GetChi2();
                    *chi2_error = GetChi2Error();
                    tree->Fill();
                    if (fHistoMode == "1D") std::cout << "n = " << (*n) << " f = " << f << " k = " << k << " mu = " << mu
                                                      << " FitMinBinX = " << fFitMinBin[0] << " FitMaxBinX = " << fFitMaxBin[0]
                                                      << " chi2 = " << (*chi2) << " chi2_error = " << (*chi2_error) << std::endl;
                    else if (fHistoMode == "2D") std::cout << "n = " << (*n) << " f = " << f << " k = " << k << " mu = " << mu
                                                           << " FitMinBinX = " << fFitMinBin[0] << " FitMaxBinX = " << fFitMaxBin[0]
                                                           << " FitMinBinY = " << fFitMinBin[1] << " FitMaxBinY = " << fFitMaxBin[1]
                                                           << " chi2 = " << (*chi2) << " chi2_error = " << (*chi2_error) << std::endl;
                    *n = *n + 1;
                    if ((*chi2) < chi2_best) { chi2_best=(*chi2); chi2_error_best=(*chi2_error); }
                }
        }
    
    /* take min(chi2) */
    *chi2 = chi2_best;
    /* take min(chi2_error) */
    *chi2_error = chi2_error_best;
}

/**
 * Find the best match
 *
 * @param return value of best fit parameters
 */
float Glauber::Fitter::FitGlauber (float *par)
{
    float f_fit{-1};
    float mu_fit{-1}; 
    float k_fit{-1};
    float Chi2Min {1e10};
    float Chi2Min_error {0};

    const TString filename = Form ( "%s/fit%s.root", fOutDirName.Data(), fOutFileIDName.Data() );

    TFile* file {TFile::Open(filename, "recreate")};    
    TTree* tree {new TTree("test_tree", "tree" )};
           
    float f, mu, k, chi2, chi2_error, sigma;
    int n=1;
    
    tree->Branch("n",    &n, "n/I");
    tree->Branch("MinBin",    &fFitMinBin, "fFitMinBin/I");
    tree->Branch("MaxBin",    &fFitMaxBin, "fFitMaxBin/I");
    tree->Branch("f",    &f, "f/F");
    tree->Branch("mu",   &mu, "mu/F");
    tree->Branch("k",    &k, "k/F");
    tree->Branch("chi2", &chi2, "chi2/F");
    tree->Branch("chi2_error", &chi2_error, "chi2_error/F");
    tree->Branch("sigma",&sigma, "sigma/F");

    fFitMinBin[0] = fMinEstimator[0];
    fFitMaxBin[0] = fMaxEstimator[0];
    fFitMinBin[1] = fMinEstimator[1];
    fFitMaxBin[1] = fMaxEstimator[1];

    for (float i=f_fMin; i<=f_fMax; i=i+f_fStep)
    {
	    f = i;
	    for (float j=f_kMin; j<=f_kMax; j=j+f_kStep)
	    {
            if (fMode == "Multiplicity") mu = fMaxValue[0] / NancestorsMax(f, fAncestor_Mode);
            else if (fMode == "MultiplicityHADES") mu = fMaxValue[0] / NancestorsMax(0, fAncestor_Mode);
            else if (fMode == "Energy" || fMode == "MultiplicityVSEnergy" || fMode == "EnergyGamma" || fMode == "EnergyLandau" || fMode == "Energy+Multiplicity") mu = fEBeam;
		    k = j;
		    const float mu_min = f_MuMinPercentage*mu;
		    const float mu_max = f_MuMaxPercentage*mu;
		    f_muStep = (mu_max-mu_min)/fnMuIter;

		    if (fFit_Mode == "GoldenSection")  FindMuGoldenSection (tree, &mu, &chi2, &chi2_error, &n, &sigma, mu_min, mu_max, f, k);
            else if (fFit_Mode == "Iteration") for (mu=mu_min; mu<=mu_max; mu=mu+f_muStep) FindMuIteration (tree, mu, &chi2, &chi2_error, &n, &sigma, f, k);
            else std::cout << "ERROR: ILLIGAL MU FINDING MODE" << std::endl;
		
		    if (chi2 < Chi2Min)
		    {
		        f_fit = f;
		        mu_fit = mu;
		        k_fit = k;
		        Chi2Min = chi2;
		        Chi2Min_error = chi2_error;

                if (fHistoMode == "1D") {
                    fBestFitHisto = fGlauberFitHisto;
                    auto it1=Glauber_Parameters_VS_Estimator_BestHistos.begin();
                    auto it2=Glauber_Parameters_VS_Estimator_Histos.begin();
                    for (int q=0; q<kGP; q++)
                    {
                        (it1->second)=(it2->second);
                        it1++;
                        it2++;
                    }
                }
                else if (fHistoMode == "2D") {
                    fBestFitHisto2D = fGlauberFitHisto2D;
                    auto it1=Glauber_Parameters_VS_Estimator_BestHistos3D.begin();
                    auto it2=Glauber_Parameters_VS_Estimator_Histos3D.begin();
                    for (int q=0; q<kGP; q++)
                    {
                        (it1->second)=(it2->second);
                        it1++;
                        it2++;
                    }
                }
		    }

	    } 
    }

    tree->Write();
    file->Write();
    file->Close();

    par[0] = f_fit;
    par[1] = mu_fit;
    par[2] = k_fit;
    par[3] = Chi2Min_error;
    
    return Chi2Min;
}

/**
 * Compare fGlauberFitHisto with fDataHisto
 * @return chi2 value
 */
float Glauber::Fitter::GetChi2 () const
{
    float chi2 {0.0};

    const int lowchibinX = fFitMinBin[0];
    const int highchibinX = fFitMaxBin[0]<fNbins[0] ? fFitMaxBin[0] : fNbins[0];

    if (fHistoMode == "1D") {
        for (int i = lowchibinX; i <= highchibinX; ++i) {
            if (fDataHisto.GetBinContent(i) < 1.0) continue;
            const float error2 = TMath::Power(fDataHisto.GetBinError(i), 2) + TMath::Power(fGlauberFitHisto.GetBinError(i), 2);
            const float diff2 = TMath::Power((fGlauberFitHisto.GetBinContent(i) - fDataHisto.GetBinContent(i)), 2) / error2;
            chi2 += diff2;
        }
        chi2 = chi2 / (highchibinX - lowchibinX + 1);
    }
    else if (fHistoMode == "2D") {
        const int lowchibinY = fFitMinBin[1];
        const int highchibinY = fFitMaxBin[1]<fNbins[1] ? fFitMaxBin[1] : fNbins[1];
        for (int i = lowchibinX; i <= highchibinX; ++i)
            for (int j = lowchibinY; j <= highchibinY; ++j) {
                if (fDataHisto2D.GetBinContent(i, j) < 1.0) continue;
                const float error2 = TMath::Power(fDataHisto2D.GetBinError(i, j), 2) + TMath::Power(fGlauberFitHisto2D.GetBinError(i, j), 2);
                const float diff2 = TMath::Power((fGlauberFitHisto2D.GetBinContent(i, j) - fDataHisto2D.GetBinContent(i, j)), 2) / error2;
                chi2 += diff2;
            }        
        chi2 = chi2 / ((highchibinX - lowchibinX + 1) * (highchibinY - lowchibinY + 1));
    }
    return chi2;
}

/**
 * Compare fGlauberFitHisto with fDataHisto
 * @return chi2 error value
 */
float Glauber::Fitter::GetChi2Error () const
{
    float chi2_error {0.0};
    const int lowchibinX = fFitMinBin[0];
    const int highchibinX = fFitMaxBin[0] < fNbins[0] ? fFitMaxBin[0] : fNbins[0];

    if (fHistoMode == "1D") {
        for (int i = lowchibinX; i <= highchibinX; ++i) {
            if (fDataHisto.GetBinContent(i) < 1.0) continue;
            const float error2 = TMath::Power(fDataHisto.GetBinError(i), 2) + TMath::Power(fGlauberFitHisto.GetBinError(i), 2);
            const float diff = (fGlauberFitHisto.GetBinContent(i) - fDataHisto.GetBinContent(i));
            const float error_diff = (fGlauberFitHisto.GetBinError(i) - fDataHisto.GetBinError(i));
            chi2_error += TMath::Power(diff * error_diff / error2, 2);
        }
        chi2_error = 2 * TMath::Power(chi2_error, 0.5) / (highchibinX - lowchibinX + 1);
    }
    else if (fHistoMode == "2D") {
        const int lowchibinY = fFitMinBin[1];
        const int highchibinY = fFitMaxBin[1]<fNbins[1] ? fFitMaxBin[1] : fNbins[1];
        for (int i = lowchibinX; i <= highchibinX; ++i)
            for (int j = lowchibinY; j <= highchibinY; ++j) {
                if (fDataHisto2D.GetBinContent(i, j) < 1.0) continue;
                const float error2 = TMath::Power(fDataHisto2D.GetBinError(i, j), 2) + TMath::Power(fGlauberFitHisto2D.GetBinError(i, j), 2);
                const float diff = (fGlauberFitHisto2D.GetBinContent(i, j) - fDataHisto2D.GetBinContent(i, j));
                const float error_diff = (fGlauberFitHisto2D.GetBinError(i, j) - fDataHisto2D.GetBinError(i, j));
                chi2_error += TMath::Power(diff * error_diff / error2, 2);
            }
        chi2_error = 2 * TMath::Power(chi2_error, 0.5) / ((highchibinX - lowchibinX + 1) * (highchibinY - lowchibinY + 1));
    }

    return chi2_error;
}

/**
 * Populates histogram nbd_<mean>_<k> with values of NBD
 * @param mu
 * @param k
 */
void Glauber::Fitter::SetNBDhist(float mu, float k)
{
    // Interface for TH1F.
    const int nBins = (mu+1.)*3 < 10 ? 10 : (mu+1.)*3;
    
    fSampleHisto = TH1F ("fNbdHisto", "", nBins, 0, nBins);
    fSampleHisto.SetName("nbd");
    
    for (int i=0; i<nBins; ++i) 
    {
        const float val = NBD(i, mu, k);
        if (val>1e-10) fSampleHisto.SetBinContent(i+1, val);
//         std::cout << "val " << val << std::endl;
    }
}

/**
 * Negative Binomial Distribution (by definition)
 * @param n argument
 * @param mu mean
 * @param k argument
 * @return NBD for a given parameters
 */
float Glauber::Fitter::NBD(float n, float mu, float k) const
{
    // Compute NBD.
    float F;
    float f;

    if (n+k > 100.0) 
    {
        // log method for handling large numbers
        F  = TMath::LnGamma(n + k)- TMath::LnGamma(n + 1.)- TMath::LnGamma(k);
        f  = n * TMath::Log(mu/k) - (n + k) * TMath::Log(1.0 + mu/k);
        F += f;
        F = TMath::Exp(F);
    } 
    else 
    {
        F  = TMath::Gamma(n + k) / ( TMath::Gamma(n + 1.) * TMath::Gamma(k) );
        f  = n * TMath::Log(mu/k) - (n + k) * TMath::Log(1.0 + mu/k);
        f  = TMath::Exp(f);
        F *= f;
    }

    return F;
}
/**
 * Creates histo with a given model parameter distribution
 * @param range observable range
 * @param name name of the MC-Glauber model parameter 
 * @param par array with fit parameters
 * @return pointer to the histogram 
 */
std::unique_ptr<TH1F> Glauber::Fitter::GetModelHisto (const float range[2], const TString& name, const float par[3])
{    
    const float f =  par[0];
    const float mu = par[1];
    const float k = par[2];
    
    float modelpar{-999.};
    fSimTree->SetBranchAddress(name, &modelpar);
        
    SetNBDhist(mu, k);
  
//     TRandom random;  
//     random.SetSeed(mu*k);

    std::unique_ptr<TH1F> hModel(new TH1F ("hModel", "name", 100, fSimTree->GetMinimum(name),  fSimTree->GetMaximum(name)) );    

    for (int i=0; i<fnEvents; i++)
    {
        fSimTree->GetEntry(i);
        const int Na = int(Nancestors(f, fAncestor_Mode));
        float nHits{0.};
        for (int j=0; j<Na; ++j) nHits += (int)fSampleHisto.GetRandom();
        
        if ( nHits > range[0] && nHits < range[1] ){
            hModel->Fill(modelpar);
        }
            
    }
    
    return hModel;
    
}
