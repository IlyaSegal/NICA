void CentralityClassesE(TString InFileName)
{
	TFile *f1 = new TFile(Form("%s/HistoCutResult.root", InFileName.Data()));
	TFile *f5 = new TFile(Form("%s/glauber_qa.root", InFileName.Data()));
	TTree *Borders=(TTree*)f1->Get("Borders");
		
	Int_t CentralityClasses = 14;
	int range_cent[15] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 80, 90, 100};

	TFile *fOut   = new TFile(Form("%s/FINAL.root", InFileName.Data()), "recreate");
	TTree *Result = new TTree("Result", "Result");
	TH2D *B_VS_Multiplicity = (TH2D *)f5->Get("B_VS_Energy_Histo");
	TH2D *Npart_VS_Multiplicity = (TH2D *)f5->Get("Npart_VS_Energy_Histo");
	TH2D *Ncoll_VS_Multiplicity = (TH2D *)f5->Get("Ncoll_VS_Energy_Histo");

	B_VS_Multiplicity->SetBit(TH1::kNoStats);
	Npart_VS_Multiplicity->SetBit(TH1::kNoStats);
	Ncoll_VS_Multiplicity->SetBit(TH1::kNoStats);

	Int_t Ncc, MinBorder, MaxBorder, MinBorder_R, MaxBorder_R;
	Float_t MinPercent, MaxPercent, B, Npart, Ncoll, NprotonsA;
	double B_av, Npart_av, Ncoll_av;
	double RMS_B_av, RMS_Npart_av, RMS_Ncoll_av;
	float mu, f, k, chi2, chi2_error;

	Borders->SetBranchAddress("MinBorder", &MinBorder);
	Borders->SetBranchAddress("MaxBorder", &MaxBorder);
	Int_t entries = (Int_t)Borders->GetEntries();

	Result->Branch("Ncc", &Ncc);
	Result->Branch("MinPercent", &MinPercent);
	Result->Branch("MaxPercent", &MaxPercent);
	Result->Branch("MinBorder", &MinBorder_R);
	Result->Branch("MaxBorder", &MaxBorder_R);
	Result->Branch("BAverage", &B_av);
	Result->Branch("BWidth", &RMS_B_av);
	Result->Branch("NpartAverage", &Npart_av);
	Result->Branch("NpartWidth", &RMS_Npart_av);
	Result->Branch("NcollAverage", &Ncoll_av);
	Result->Branch("NcollWidth", &RMS_Ncoll_av);

	TH1D *B_VS_CentralityHisto[CentralityClasses + 1];
	for (int i = 0; i < CentralityClasses + 1; i++)
		B_VS_CentralityHisto[i] = new TH1D(Form("B_VS_CentralityClass %1.1d%%-%1.1d%%", range_cent[i], range_cent[i + 1]), ";B, fm;counts", 200, 0, 20);
	for (int i = 0; i < CentralityClasses + 1; i++)
		B_VS_CentralityHisto[i]->SetBit(TH1::kNoStats);

	TH1D *Npart_VS_CentralityHisto[CentralityClasses + 1];
	for (int i = 0; i < CentralityClasses + 1; i++)
		Npart_VS_CentralityHisto[i] = new TH1D(Form("Npart_VS_CentralityClass %1.1d%%-%1.1d%%", range_cent[i], range_cent[i + 1]), ";N_{part};counts", 400, 0, 400);
	for (int i = 0; i < CentralityClasses + 1; i++)
		Npart_VS_CentralityHisto[i]->SetBit(TH1::kNoStats);

	TH1D *Ncoll_VS_CentralityHisto[CentralityClasses + 1];
	for (int i = 0; i < CentralityClasses + 1; i++)
		Ncoll_VS_CentralityHisto[i] = new TH1D(Form("Ncoll_VS_CentralityClass %1.1d%%-%1.1d%%", range_cent[i], range_cent[i + 1]), ";Ncoll;counts", 1000, 0, 1000);
	for (int i = 0; i < CentralityClasses + 1; i++)
		Ncoll_VS_CentralityHisto[i]->SetBit(TH1::kNoStats);
		
	double B_av_ar[CentralityClasses], Npart_av_ar[CentralityClasses], Ncoll_av_ar[CentralityClasses], centbin[CentralityClasses];
	double RMS_B_av_ar[CentralityClasses], RMS_Npart_av_ar[CentralityClasses], RMS_Ncoll_av_ar[CentralityClasses], centEr[CentralityClasses];

	B_VS_CentralityHisto[CentralityClasses] = B_VS_Multiplicity->ProjectionY("B_VS_CentralityClass 0%-100%", 0, 10000);
	Npart_VS_CentralityHisto[CentralityClasses] = Npart_VS_Multiplicity->ProjectionY("Npart_VS_CentralityClass 0%-100%", 0, 10000);
	Ncoll_VS_CentralityHisto[CentralityClasses] = Ncoll_VS_Multiplicity->ProjectionY("Ncoll_VS_CentralityClass 0%-100%", 0, 10000);
	for (int i = 0; i < entries; i++)
	{
		Borders->GetEntry(i);
		B_VS_CentralityHisto[i] = B_VS_Multiplicity->ProjectionY(Form("B_VS_CentralityClass %1.1d%%-%1.1d%%", range_cent[i], range_cent[i + 1]), MinBorder/5, MaxBorder/5);
		Npart_VS_CentralityHisto[i] = Npart_VS_Multiplicity->ProjectionY(Form("Npart_VS_CentralityClass %1.1d%%-%1.1d%%", range_cent[i], range_cent[i + 1]), MinBorder/5, MaxBorder/5);
		Ncoll_VS_CentralityHisto[i] = Ncoll_VS_Multiplicity->ProjectionY(Form("Ncoll_VS_CentralityClass %1.1d%%-%1.1d%%", range_cent[i], range_cent[i + 1]), MinBorder/5, MaxBorder/5);
	}

	int j = 1;
	for (int i = 0; i < CentralityClasses + 1; i++)
	{
		B_VS_CentralityHisto[i]->SetLineColor(j);
		j++;
		if (j == 9)
			j = 1;
	}
	for (int i = 0; i < CentralityClasses + 1; i++)
		B_VS_CentralityHisto[i]->SetLineWidth(2);
	for (int i = 0; i < CentralityClasses + 1; i++)
	{
		B_VS_CentralityHisto[i]->SetXTitle("B, fm");
		B_VS_CentralityHisto[i]->SetYTitle("counts");
	}

	j = 1;
	for (int i = 0; i < CentralityClasses + 1; i++)
	{
		Npart_VS_CentralityHisto[i]->SetLineColor(j);
		j++;
		if (j == 9)
			j = 1;
	}
	for (int i = 0; i < CentralityClasses + 1; i++)
		Npart_VS_CentralityHisto[i]->SetLineWidth(2);
	for (int i = 0; i < CentralityClasses + 1; i++)
	{
		Npart_VS_CentralityHisto[i]->SetXTitle("N_{part}");
		Npart_VS_CentralityHisto[i]->SetYTitle("counts");
	}

	j = 1;
	for (int i = 0; i < CentralityClasses + 1; i++)
	{
		Ncoll_VS_CentralityHisto[i]->SetLineColor(j);
		j++;
		if (j == 9)
			j = 1;
	}
	for (int i = 0; i < CentralityClasses + 1; i++)
		Ncoll_VS_CentralityHisto[i]->SetLineWidth(2);
	for (int i = 0; i < CentralityClasses + 1; i++)
	{
		Ncoll_VS_CentralityHisto[i]->SetXTitle("N_{coll}");
		Ncoll_VS_CentralityHisto[i]->SetYTitle("counts");
	}

	for (int i = 0; i < CentralityClasses; i++)
	{
		cout << i << endl;
		Ncc = i + 1;
		MinPercent = range_cent[i];
		MaxPercent = range_cent[i + 1];
		centbin[i] = range_cent[i] + (range_cent[i+1]-range_cent[i])/2;
        	centEr[i] = 0;

		Borders->GetEntry(i);

		MinBorder_R = MinBorder;
		MaxBorder_R = MaxBorder;

		B_av = B_VS_CentralityHisto[i]->GetMean();
		Npart_av = Npart_VS_CentralityHisto[i]->GetMean();
		Ncoll_av = Ncoll_VS_CentralityHisto[i]->GetMean();
		
		B_av_ar[i] = B_av;
		Npart_av_ar[i] = Npart_av;
		Ncoll_av_ar[i] = Ncoll_av;

		RMS_B_av = B_VS_CentralityHisto[i]->GetRMS();
		RMS_Npart_av = Npart_VS_CentralityHisto[i]->GetRMS();
		RMS_Ncoll_av = Ncoll_VS_CentralityHisto[i]->GetRMS();
		
		RMS_B_av_ar[i] = RMS_B_av;
		RMS_Npart_av_ar[i] = RMS_Npart_av;
		RMS_Ncoll_av_ar[i] = RMS_Ncoll_av;

		Result->Fill();
	}
	
	TGraphErrors *B_average_VS_Centrality = new TGraphErrors(14, centbin, B_av_ar, centEr, RMS_B_av_ar);
	TGraphErrors *Npart_average_VS_Centrality = new TGraphErrors(14, centbin, Npart_av_ar, centEr, RMS_Npart_av_ar);
	TGraphErrors *Ncoll_average_VS_Centrality = new TGraphErrors(14, centbin, Ncoll_av_ar, centEr, RMS_Ncoll_av_ar);

	for (int i = 0; i <= CentralityClasses; i++)
		B_VS_CentralityHisto[i]->Write();

	for (int i = 0; i <= CentralityClasses; i++)
		Npart_VS_CentralityHisto[i]->Write();

	for (int i = 0; i <= CentralityClasses; i++)
		Ncoll_VS_CentralityHisto[i]->Write();

	B_average_VS_Centrality->Write();
	Npart_average_VS_Centrality->Write();
	Ncoll_average_VS_Centrality->Write();

	Result->Write();

	fOut->Close();
}
