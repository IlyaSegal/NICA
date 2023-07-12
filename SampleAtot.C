void SampleAtot(TString InFileName, TString OutFileName)
{
    TFile *file = new TFile(InFileName);    
    auto *in_tree = (TTree*) file->Get("nt_Pb_Pb");
    
    Int_t Nspec, Atot;
    Float_t Npart;
    Int_t Aproj=208;
    in_tree->SetBranchAddress("NpartA", &Npart);
    TH1F* hNpart = new TH1F ("hNpart", "N_{part};N_{part};counts", Aproj+2, 0, Aproj+2);
    TH1F* hNspec = new TH1F ("hNspec", "N_{spec};N_{spec};counts", Aproj+2, 0, Aproj+2);
    TH1F* hAtot = new TH1F ("hAtot", "A_{tot};A_{tot};counts", Aproj+2, 0, Aproj+2);
    TH2F* hNspecAtot = new TH2F ("hNspecAtot", "A_{tot} VS N_{spec};A_{tot};N_{spec}", Aproj+2, 0, Aproj+2, Aproj+2, 0, Aproj+2);
    
    float mu,k;
    auto* mean_fit = new TF1("mean_fit", "[0]+[1]*TMath::Power(x,[2])", 0, Aproj+2);
    mean_fit->SetParameters(-1.05371e+02,8.01685e+01,2.57008e-01);
    auto* sigma_max_fit = new TF1("sigma_max_fit", "[0]+[1]*TMath::Power(x,[2])", 0, Aproj+2);
    sigma_max_fit->SetParameters(-4.34575e+01,2.64658e+01,4.21169e-01);
    
    for (Int_t i=0; i<in_tree->GetEntries(); i++)
    {
    	Atot = -999;
    	in_tree->GetEntry(i);
    	Nspec = (int) (Aproj - Npart);
    	mu = mean_fit->GetX(Nspec, 0, Aproj+2);
    	k = sigma_max_fit->GetX(Nspec, 0, Aproj+2) - mu;
    	while((Atot<0) || (Atot>Aproj)) Atot = (int) gRandom->Gaus(mu, k);
//    	cout<<"Nspec="<<Nspec<<"   Atot="<<Atot<<"   mu="<<mu<<"   k="<<k<<endl;
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
