void AtotNspecFit(TString InFileName, TString OutFileName)
{
    TFile *file = new TFile(InFileName);    
    auto *in_histo = (TH2D*) file->Get("ATotProj_NSpecProj");
//    auto* ATotSampleHisto = (THnSparseD*)file->Get("B_ATotProj_NFragProj_NSpecProj");
//    ATotSampleHisto->GetAxis(0)->SetRange(0, 210);
//    ATotSampleHisto->GetAxis(2)->SetRange(0, 210);
//    auto* in_histo = (TH2D*)ATotSampleHisto->Projection(3, 1);
    
    std::vector <Float_t> mean_vec;
    std::vector <Float_t> sigma_vec;
    std::vector <Float_t> nspec_vec;
    std::vector <Float_t> nspec_error_vec;
    std::vector <Float_t> sigma_max;
    std::vector <Float_t> sigma_min;
    std::vector <Float_t> mean_error_vec;
    std::vector <Float_t> sigma_error_vec;
    std::vector <Float_t> sigma_error_max;
    std::vector <Float_t> sigma_error_min;
    Float_t mean, mean_error, sigma, sigma_error;
    
    for (Int_t i=0; i<208; i++)
    {
    	auto *histo_proj = (TH1D*) in_histo->ProjectionX("histo_proj", i, i+1);
//    	mean = histo_proj->GetMean();
	mean = histo_proj->GetMaximumBin();
//    	mean_error = histo_proj->GetMeanError();
	mean_error = 0.1;
    	sigma = histo_proj->GetRMS();
    	sigma_error = histo_proj->GetRMSError();
        mean_vec.push_back(mean);
        nspec_vec.push_back(i);
        sigma_vec.push_back(sigma);
        sigma_max.push_back(mean+sigma);
        sigma_min.push_back(mean-sigma);
        mean_error_vec.push_back(mean_error);
        nspec_error_vec.push_back(0);
        sigma_error_vec.push_back(sigma_error);
        sigma_error_max.push_back(mean_error+sigma_error);
        sigma_error_min.push_back(mean_error+sigma_error);
    }
    
    auto *graph_mean = new TGraphErrors(mean_vec.size(), &(mean_vec[0]), &(nspec_vec[0]), &(mean_error_vec[0]), &(nspec_error_vec[0]));
    graph_mean->SetName("<A_tot>_VS_N_spec");
    graph_mean->SetTitle("<A_{tot}> VS N_{spec};<A_{tot}>;N_{spec}");
    auto *graph_sigma = new TGraphErrors(sigma_vec.size(), &(sigma_vec[0]), &(nspec_vec[0]), &(sigma_error_vec[0]), &(nspec_error_vec[0]));
    graph_sigma->SetName("sigma_A_tot_VS_N_spec");
    graph_sigma->SetTitle("#sigma(A_{tot}) VS N_{spec};#sigma(A_{tot});N_{spec}");
    auto *graph_sigma_max = new TGraphErrors(sigma_max.size(), &(sigma_max[0]), &(nspec_vec[0]), &(sigma_error_max[0]), &(nspec_error_vec[0]));
    graph_sigma_max->SetName("sigma_Atot_max_VS_N_spec");
    graph_sigma_max->SetTitle("<A_{tot}>+#sigma(A_{tot}) VS N_{spec};#sigma(A_{tot});N_{spec}");
    auto *graph_sigma_min = new TGraphErrors(sigma_min.size(), &(sigma_min[0]), &(nspec_vec[0]), &(sigma_error_min[0]), &(nspec_error_vec[0]));
    graph_sigma_min->SetName("sigma_Atot_min_VS_N_spec");
    graph_sigma_min->SetTitle("<A_{tot}>-#sigma(A_{tot}) VS N_{spec};<A_{tot}>-#sigma(A_{tot});N_{spec}");
        

    auto* mean_fit = new TF1("mean_fit", "TMath::Power(208,1-[0])*TMath::Power(x,[0])", 0, nspec_vec.at(nspec_vec.size()-1));
    mean_fit->SetParameter(0, 0.3);
    auto* sigma_max_fit = new TF1("sigma_max_fit", "[0]+[1]*TMath::Power(x,[2])", 0, nspec_vec.at(nspec_vec.size()-1));
    sigma_max_fit->SetParameters(0,1,0.3);
    auto* sigma_min_fit = new TF1("sigma_min_fit", "[0]+[1]*TMath::Power(x,[2])", 0, nspec_vec.at(nspec_vec.size()-1));
    sigma_min_fit->SetParameters(0,1,0.3);
    
    graph_mean->Fit(mean_fit);
    graph_sigma_max->Fit(sigma_max_fit);
    graph_sigma_min->Fit(sigma_min_fit);
    
    auto* sigma_fit = new TF1("sigma_fit", "((sigma_max_fit-mean_fit)+(mean_fit-sigma_min_fit))/2", 0, nspec_vec.at(nspec_vec.size()-1));
    
    
    
    
    
    TFile *f1 = new TFile(OutFileName, "recreate");
    in_histo->Write();
    graph_mean->Write();
    graph_sigma->Write();
    graph_sigma_max->Write();
    graph_sigma_min->Write();
    mean_fit->Write();
    sigma_fit->Write();
    sigma_max_fit->Write();
    sigma_min_fit->Write();
    f1->Close();  
}
