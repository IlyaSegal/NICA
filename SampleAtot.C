void SampleAtot(TString InFileName, TString OutFileName)
{
    TFile *file = new TFile(InFileName);    
    auto *in_tree = (TTree*) file->Get("nt_Pb_Pb");
    
    Int_t Nspec, Atot;
    Float_t Npart;
    Int_t Aproj=208;
    in_tree->SetBranchAddress("NpartA", &Npart);
    TH1F* hNpart = new TH1F ("hNpart", "N_{part};N_{part};counts", Aproj+10, 0, Aproj+10);
    TH1F* hNspec = new TH1F ("hNspec", "N_{spec};N_{spec};counts", Aproj+10, 0, Aproj+10);
    TH1F* hAtot = new TH1F ("hAtot", "A_{tot};A_{tot};counts", Aproj+10, 0, Aproj+10);
    TH2F* hNspecAtot = new TH2F ("hNspecAtot", "A_{tot} VS N_{spec};A_{tot};N_{spec}", Aproj+10, 0, Aproj+10, Aproj+10, 0, Aproj+10);
    
    float mu,k;
    
    //      NA61/SHINE Pb-Pb @ 13GeV/c 
    auto* mean_fit = new TF1("mean_fit_proj", "[0]+[1]*TMath::Power(x,[2])", 0, Aproj+10);
//    mean_fit->SetParameters(-1.05371e+02,8.01685e+01,2.57008e-01);     //mean
    mean_fit->SetParameters(-1.37869e+02,1.09759e+02,2.14734e-01);     //max
    auto* sigma_max_fit = new TF1("sigma_max_fit_proj", "[0]+[1]*TMath::Power(x,[2])", 0, Aproj+10);
    sigma_max_fit->SetParameters(-4.34575e+01,2.64658e+01,4.21169e-01);
    

 /*//      BM@N Xe-CsI @ 3.85GeV 
    auto* mean_fit = new TF1("mean_fit_proj", "[0]+[1]*TMath::Power(x,[2])", 0, Aproj+10);
    mean_fit->SetParameters(-6.66346e+01,5.17635e+01,2.77331e-01);
    auto* sigma_max_fit = new TF1("sigma_max_fit_proj", "[0]+[1]*TMath::Power(x,[2])", 0, Aproj+10);
    sigma_max_fit->SetParameters(-3.18237e+01,1.96394e+01,4.30432e-01);
    */
    
    for (Int_t i=0; i<in_tree->GetEntries(); i++)
    {
    	Atot = -999;
    	in_tree->GetEntry(i);
    	Nspec = (int) (Aproj - Npart);
    	mu = mean_fit->GetX(Nspec, 0, Aproj+10);
    	k = sigma_max_fit->GetX(Nspec, 0, Aproj+10) - mu;
//    	Atot = (int) mu;
    	while((Atot<0) || (Atot>Aproj)) Atot = (int) gRandom->Gaus(mu, k);
//    	cout<<"Nspec="<<Nspec<<"   Atot="<<Atot<<"   mu="<<mu<<"   k="<<k<<endl;
    	if (Nspec>199) Atot = Nspec;
    	hNpart->Fill(Npart);
   	hNspec->Fill(Nspec);
   	hAtot->Fill(Atot);
    	hNspecAtot->Fill(Atot,Nspec);
    }
    
    TFile *f1 = new TFile(OutFileName, "recreate");
    hNpart->Write();
    hNspec->Write();
    hAtot->Write();
    hNspecAtot->Write();
    mean_fit->Write();
    sigma_max_fit->Write();
    f1->Close();  
}
