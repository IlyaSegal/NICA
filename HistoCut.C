void HistoCut(TString InFileName)
{
	TFile *f1 = new TFile(Form("%s/glauber_qa.root", InFileName.Data()));
	TH1F *FitHisto = (TH1F *)f1->Get("glaub_fit_histo");
	TH1F *DataHisto = (TH1F *)f1->Get("h1_track_multiplicity");
	
	Int_t CentralityClasses = 14;
	int range_cent[15] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 80, 90, 100};

	Int_t bins = FitHisto->GetNbinsX();
	Int_t binsN = FitHisto->FindLastBinAbove();
	cout << "bins=" << bins << endl;
	Double_t max = FitHisto->GetXaxis()->GetBinCenter(bins);
	cout << "max=" << max << endl;
	Double_t min = FitHisto->GetYaxis()->GetXmin();
	cout << "min=" << min << endl;
	Double_t integral = FitHisto->Integral(2, bins);
	cout << "integral=" << integral << endl;

	TFile *f = new TFile(Form("%s/HistoCutResult.root", InFileName.Data()), "recreate");
	TH1F *ResultHisto[CentralityClasses];
	for (int i = 0; i < CentralityClasses; i++)
		ResultHisto[i] = new TH1F(Form("CentralityClass_Fit %1.1d%%-%1.1d%%", range_cent[i], range_cent[i + 1]), ";tracks;counts", bins, min, max);
	Int_t j = 1;
	for (int i = 0; i < CentralityClasses; i++)
	{
		ResultHisto[i]->SetLineColor(j);
		j++;
		if (j == 9)
			j = 1;
	}
	for (int i = 0; i < CentralityClasses; i++)
		ResultHisto[i]->SetLineWidth(4);

	TH1F *CentralityHisto[CentralityClasses];
	for (int i = 0; i < CentralityClasses; i++)
		CentralityHisto[i] = new TH1F(Form("CentralityClass %1.1d%%-%1.1d%%", range_cent[i], range_cent[i + 1]), ";tracks;counts", bins, min, max);
	j = 1;
	for (int i = 0; i < CentralityClasses; i++)
	{
		CentralityHisto[i]->SetLineColor(j);
		j++;
		if (j == 9)
			j = 1;
	}
	for (int i = 0; i < CentralityClasses; i++)
		CentralityHisto[i]->SetLineWidth(4);

	TH1F *Centrality_vs_Multiplisity = new TH1F("Centrality_vs_Multiplisity", ";tracks;CentralityPercent", bins, min, max);
	Centrality_vs_Multiplisity->SetLineColor(1);
	Centrality_vs_Multiplisity->SetLineWidth(4);

	j = 0;
	Double_t sum = 0.0;
	Double_t IntegrSc = 0;

	for (Int_t i = binsN - 1; i >= 1; i--)
	{
		IntegrSc = FitHisto->Integral(i, binsN);// / integral;
		if (IntegrSc <= integral*range_cent[j + 1] * 0.01 && j < CentralityClasses)
		{
			ResultHisto[j]->SetBinContent(i, FitHisto->GetBinContent(i));
//			cout << "j=" << j << "  i=" << i << " Int=" << IntegrSc << endl;
		}
		// if (IntegrSc >= ((j + 1.) / CentralityClasses))
		else
		{
			j++;
			if (j < CentralityClasses)
			{
				ResultHisto[j]->SetBinContent(i, FitHisto->GetBinContent(i));
//				cout << "j=" << j << "  i=" << i << " Int=" << IntegrSc << endl;
			}
		}
	}

//	cout << "---------------------------------------------------" << endl;
	for (int j = 0; j < CentralityClasses; j++)
	{
		for (Int_t i = 1; i < binsN; i++)
		{
			if ((ResultHisto[j]->GetBinContent(i)) > 0)
			{
				CentralityHisto[j]->SetBinContent(i, DataHisto->GetBinContent(i));
				Centrality_vs_Multiplisity->SetBinContent(i, range_cent[j + 1]);
			}
		}
	}

	TTree *Borders = new TTree("Borders", "Borders");
	Int_t Ncc, BIN, MinBorder, MaxBorder;
	Float_t MinPercent, MaxPercent;
	Borders->Branch("Ncc", &Ncc);
	Borders->Branch("MinPercent", &MinPercent);
	Borders->Branch("MaxPercent", &MaxPercent);
	Borders->Branch("MinBorder", &MinBorder);
	Borders->Branch("MaxBorder", &MaxBorder);

	j = 0;
	for (Int_t i = 1; i <= CentralityClasses; i++)
	{

		Ncc = i;
		Int_t l = 2;
		while ((ResultHisto[j]->GetBinContent(l)) <= 0 && l < bins)
			l++;
		MinPercent = range_cent[j];
		MinBorder = ResultHisto[j]->GetBinCenter(l);
		BIN = l;
		for (Int_t q = BIN; q <= bins; q++)
		{
			if ((ResultHisto[j]->GetBinContent(q)) <= 0)
			{
				MaxPercent = range_cent[j + 1];
				MaxBorder = ResultHisto[j]->GetBinCenter(q);
				break;
			};
			if (q == bins)
			{
				MaxPercent = (j + 1) * 100 / CentralityClasses;
				MaxBorder = ResultHisto[j]->GetBinCenter(q);
			};
		}
		Borders->Fill();
		j++;
	}

	
	TLegend legend1(0.1, 0.2, 0.3, 0.4, "HistoCutResult");
	for (int i = 0; i < CentralityClasses; i++)
		legend1.AddEntry(ResultHisto[i], Form("CentralityClass %1.1d%%-%1.1d%%", range_cent[i], range_cent[i + 1]));
	THStack *ResultHistos = new THStack("HistoCutResult", "HistoCutResult");
	for (int i = 0; i < CentralityClasses; i++)
		ResultHistos->Add(ResultHisto[i]);

	for (int i = 0; i < CentralityClasses; i++)
		ResultHisto[i]->Write();

	
	TLegend legend2(0.1, 0.2, 0.3, 0.4, "CentraliryClasses");
	for (int i = 0; i < CentralityClasses; i++)
		legend2.AddEntry(CentralityHisto[i], Form("CentralityClass %1.1d%%-%1.1d%%", range_cent[i], range_cent[i + 1]));
	THStack *CentralityHistos = new THStack("HistoCutResult", "HistoCutResult");
	for (int i = 0; i < CentralityClasses; i++)
		CentralityHistos->Add(CentralityHisto[i]);
	
	
	for (int i = 0; i < CentralityClasses; i++)
		CentralityHisto[i]->Write();
	Centrality_vs_Multiplisity->Write();

	Borders->Write();

	f->Close();
}
