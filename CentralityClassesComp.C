void CentralityClassesComp()
{
	TFile *fM = new TFile("/home/isegal/NA61/centrality/mult/FINAL.root");
	TFile *fE = new TFile("/home/isegal/NA61/centrality/psd_mult/FINAL.root");
	TFile *fdata = new TFile("/home/isegal/NA61/data/PbPb_pbeam_13AGeV/QA/qa13sel_16026.root");
	TTree *ResultM = (TTree*)fM->Get("Result");
	TTree *ResultE = (TTree*)fE->Get("Result");
	TH2D* hME = (TH2D*)fdata->Get("h2_MgoodMid_psdE");
	TH2D* hMEComp = new TH2D("Comp", "Comp", 20, 0, 100, 20, 0, 100);
		
	Int_t CentralityClasses = ResultM->GetEntries();

	TFile *fOut   = new TFile("/home/isegal/NA61/centrality/Comp.root", "recreate");

	Int_t MinBorderM, MaxBorderM, MinBorderE, MaxBorderE;
	Float_t MinPercentM, MaxPercentM, MinPercentE, MaxPercentE;

	ResultM->SetBranchAddress("MinBorder", &MinBorderM);
	ResultM->SetBranchAddress("MaxBorder", &MaxBorderM);
	ResultM->SetBranchAddress("MinPercent", &MinPercentM);
	ResultM->SetBranchAddress("MaxPercent", &MaxPercentM);
	
	ResultE->SetBranchAddress("MinBorder", &MinBorderE);
	ResultE->SetBranchAddress("MaxBorder", &MaxBorderE);
	ResultE->SetBranchAddress("MinPercent", &MinPercentE);
	ResultE->SetBranchAddress("MaxPercent", &MaxPercentE);

	std::vector <Float_t> CM;
    	std::vector <Float_t> CE;
    	std::vector <Float_t> N;
    	
    	Float_t sum=0;
    	
    	for (Int_t i=0; i<CentralityClasses; i++) {
    		ResultM->GetEntry(i);
    		for (Int_t j=0; j<CentralityClasses; j++) {
    			ResultE->GetEntry(j);
    			CM.push_back(MinPercentM+(MaxPercentM-MinPercentM)/2);
        		CE.push_back(MinPercentE+(MaxPercentE-MinPercentE)/2);
        		N.push_back(hME->Integral(hME->GetXaxis()->FindBin(MinBorderM), hME->GetXaxis()->FindBin(MaxBorderM), hME->GetXaxis()->FindBin(MinBorderE), hME->GetXaxis()->FindBin(MaxBorderE)));
        		sum = sum + hME->Integral(hME->GetXaxis()->FindBin(MinBorderM), hME->GetXaxis()->FindBin(MaxBorderM), hME->GetXaxis()->FindBin(MinBorderE), hME->GetXaxis()->FindBin(MaxBorderE));
        		for (Float_t CMbin=MinPercentM; CMbin<MaxPercentM; CMbin = CMbin + 5.0) for (Float_t CEbin=MinPercentE; CEbin<MaxPercentE; CEbin = CEbin + 5.0) hMEComp->SetBinContent((Int_t)(CMbin/5)+1, (Int_t)(CEbin/5)+1, 100*hME->Integral(hME->GetXaxis()->FindBin(MinBorderM), hME->GetXaxis()->FindBin(MaxBorderM), hME->GetYaxis()->FindBin(MinBorderE), hME->GetYaxis()->FindBin(MaxBorderE))/hME->GetEntries());
    		}
    	}

	cout<<sum<<endl;
	TGraph2D *g = new TGraph2D(CM.size(), &(CM[0]), &(CE[0]), &(N[0]));
    	g->SetName("graph");
    	g->SetTitle("graph");
    	g->Write();
    	hME->Write();
    	hMEComp->Write();

	fOut->Close();
}
